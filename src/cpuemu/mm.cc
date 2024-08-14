#define ETL_NO_SMALL_CHAR_SUPPORT 0
// See LICENSE for license details.

#include "mm.h"
#include <etl/vector.h>
#include <am.h>
#include <klib.h>

mm_magic_t::mm_magic_t(size_t size, size_t word_size):
  data(new char[size]),
  size(size),
  word_size(word_size), 
  store_inflight(false)
{
  dummy_data.resize(word_size);
}

mm_magic_t::~mm_magic_t()
{
  delete [] data;
}

void mm_magic_t::write(uint64_t addr, char *data) {
  addr %= this->size;

  char* base = this->data + addr;
  memcpy(base, data, word_size);
}

void mm_magic_t::write(uint64_t addr, char *data, uint64_t strb, uint64_t size)
{
  strb &= ((1L << size) - 1) << (addr % word_size);
  addr %= this->size;

  char *base = this->data + addr;
  for (uint64_t i = 0; i < word_size; i++) {
    if (strb & 1) base[i] = data[i];
    strb >>= 1;
  }
}

etl::vector<char, 256> mm_magic_t::read(uint64_t addr)
{
  addr %= this->size;

  char *base = this->data + addr;
  return etl::vector<char, 256>(base, base + word_size);
}

void mm_magic_t::tick(
  bool reset,
  bool ar_valid,
  uint64_t ar_addr,
  uint64_t ar_id,
  uint64_t ar_size,
  uint64_t ar_len,

  bool aw_valid,
  uint64_t aw_addr,
  uint64_t aw_id,
  uint64_t aw_size,
  uint64_t aw_len,

  bool w_valid,
  uint64_t w_strb,
  void *w_data,
  bool w_last,

  bool r_ready,
  bool b_ready)
{
  bool ar_fire = !reset && ar_valid && ar_ready();
  bool aw_fire = !reset && aw_valid && aw_ready();
  bool w_fire = !reset && w_valid && w_ready();
  bool r_fire = !reset && r_valid() && r_ready;
  bool b_fire = !reset && b_valid() && b_ready;

  if (ar_fire) {
    uint64_t start_addr = (ar_addr / word_size) * word_size;
    for (size_t i = 0; i <= ar_len; i++) {
      auto dat = read(start_addr + i * word_size);
      rresp.push(mm_rresp_t(ar_id, dat, i == ar_len));
    }
  }

  if (aw_fire) {
    store_addr = aw_addr;
    store_id = aw_id;
    store_count = aw_len + 1;
    store_size = 1 << aw_size;
    store_inflight = true;
  }

  if (w_fire) {
    write(store_addr, (char*)w_data, w_strb, store_size);
    store_addr += store_size;
    store_count--;

    if (store_count == 0) {
      store_inflight = false;
      bresp.push(store_id);
    }
  }

  if (b_fire)
    bresp.pop();

  if (r_fire)
    rresp.pop();

  cycle++;

  if (reset) {
    while (!bresp.empty()) bresp.pop();
    while (!rresp.empty()) rresp.pop();
    cycle = 0;
  }
}

extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;

#define MAX_PROGRAM_SIZE ((&ramdisk_start) - (&ramdisk_end))

void load_mem(char* mem)
{
  // print mem address
  printf("mem address: %p\n", &mem);
  memset(&mem, 0, MAX_PROGRAM_SIZE);
  memcpy(&mem, &ramdisk_start, &ramdisk_end - &ramdisk_start);

  return;
}
