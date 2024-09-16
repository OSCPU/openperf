#include <cpuemu.h>
#include "uint.h"
#include "Tile.h"
#include "mm.h"

#include <etl/vector.h>
#include <etl/queue.h>

// static uint64_t trace_count = 0;
static uint64_t main_time = 0;
Tile top;
mm_magic_t mem = mm_magic_t(8);

void tick(bool verbose, bool done_reset) {
  main_time++;
  
  top.io_nasti_aw_ready = UInt<1>(mem.aw_ready());
  top.io_nasti_ar_ready = UInt<1>(mem.ar_ready());
  top.io_nasti_w_ready = UInt<1>(mem.w_ready());
  top.io_nasti_b_valid = UInt<1>(mem.b_valid());
  top.io_nasti_b_bits_id = UInt<5>(mem.b_id());
  top.io_nasti_b_bits_resp = UInt<2>(mem.b_resp());
  top.io_nasti_r_valid = UInt<1>(mem.r_valid());
  top.io_nasti_r_bits_id = UInt<5>(mem.r_id());
  top.io_nasti_r_bits_resp = UInt<2>(mem.r_resp());
  top.io_nasti_r_bits_last = UInt<1>(mem.r_last());
  // check address because memcpy is not working
  // printf("mem.r_data() %p, &top.io_nasti_r_bits_data %p\n", mem.r_data(), &top.io_nasti_r_bits_data);
  memcpy(&top.io_nasti_r_bits_data, mem.r_data(), 8);

  top.eval(true, verbose, done_reset);
  mem.tick(
    top.reset, 
    top.io_nasti_ar_valid, 
    top.io_nasti_ar_bits_addr.as_single_word(), 
    top.io_nasti_ar_bits_id.as_single_word(), 
    top.io_nasti_ar_bits_size.as_single_word(), 
    top.io_nasti_ar_bits_len.as_single_word(), 
    top.io_nasti_aw_valid, 
    top.io_nasti_aw_bits_addr.as_single_word(), 
    top.io_nasti_aw_bits_id.as_single_word(), 
    top.io_nasti_aw_bits_size.as_single_word(), 
    top.io_nasti_aw_bits_len.as_single_word(), 
    top.io_nasti_w_valid, 
    top.io_nasti_w_bits_strb.as_single_word(), 
    &top.io_nasti_w_bits_data, 
    top.io_nasti_w_bits_last, 
    top.io_nasti_r_ready, 
    top.io_nasti_b_ready 
  );
  main_time++;

}

void rvmini() {
  etl::vector<char, 256> dummy_data(256);
  etl::queue<uint64_t, 256> bresp;
  etl::queue<mm_rresp_t, 256> rresp;
  // printf("dummy_data: %p, bresp: %p, rresp: %p\n", &dummy_data[0], &bresp.front(), &rresp.front());

  uint64_t timeout = 1000L;
  // cout << "Enabling waves..." << endl;
  mem = mm_magic_t(8);
  mem.init(0x8000, &dummy_data, &bresp, &rresp);
  load_mem(mem.get_data()); 
  top.reset = UInt<1>(1);
  // cout << "Starting simulation!" << endl;
  for (size_t i = 0; i < 5 ; i++) {
    tick(true, false); 
  }

  top.reset = UInt<1>(0);
  top.io_host_fromhost_bits = UInt<32>(0);
  top.io_host_fromhost_valid = UInt<1>(0);
  // cout << "while" <<endl;

  // currently the simulation looks like stuck in same
  // pc in client program. To turn on the info output,
  // uncomment "Tile.h" : 6294 line.
  //
  // The reset pc value override in "Tile.h" : 6312 line.
  do {
    tick(true,true);
  } while(!top.io_host_tohost.as_single_word() && main_time < timeout);

  for (size_t i = 0 ; i < 10 ; i++) {
    tick(true, true); 
  }

  return;

}
