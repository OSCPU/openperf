#define ETL_NO_SMALL_CHAR_SUPPORT 0
#include "uint.h"
#include "Tile.h"
#include "mm.h"
 
using namespace etl;

// static uint64_t trace_count = 0;
static uint64_t main_time = 0;
Tile top;
mm_magic_t mem = mm_magic_t(1L << 16, 8);;

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

int main(int argc, char** argv) {
  uint64_t timeout = 1000L;
  // cout << "Enabling waves..." << endl;
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
  do {
    tick(true,true);
  } while(!top.io_host_tohost.as_single_word() && main_time < timeout);

  for (size_t i = 0 ; i < 10 ; i++) {
    tick(true, true); 
  }

  return 0;

}
