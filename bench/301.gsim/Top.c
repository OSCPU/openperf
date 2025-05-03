#include "Top.h"

static uint64_t cycles;
static uint64_t LOG_START, LOG_END;
static uint8_t activeFlags[8];
static uint8_t reset;                                                                       // width = 1, lineno = 2974
static uint8_t npc_DOT_xbar2_DOT_arSel_s1_0;                                                // width = 1, lineno = 2285
static uint8_t npc_DOT_xbar2_DOT_arSel_s1_1;                                                // width = 1, lineno = 2285
static uint8_t npc_DOT_lsu_DOT__T_24;                                                       // width = 1, lineno = 1622
static uint32_t npc_DOT_ifu_DOT_PC;                                                         // width = 32, lineno = 645
static uint8_t npc_DOT_lsu_DOT_state;                                                       // width = 2, lineno = 1170
static uint8_t npc_DOT_lsu_DOT_sbufState;                                                   // width = 2, lineno = 1285
static uint32_t npc_DOT_lsu_DOT_mstatus;                                                    // width = 32, lineno = 1384
static uint32_t npc_DOT_lsu_DOT_mcycle;                                                     // width = 32, lineno = 1386
static uint32_t npc_DOT_lsu_DOT_mvendorid;                                                  // width = 32, lineno = 1390
static uint32_t npc_DOT_lsu_DOT_marchid;                                                    // width = 32, lineno = 1391
static uint8_t npc_DOT_deq_q_DOT_maybe_full;                                                // width = 1, lineno = 1721
static uint8_t npc_DOT_idu_io_in_valid_REG;                                                 // width = 1, lineno = 2489
static uint8_t npc_DOT_exu_io_in_valid_REG;                                                 // width = 1, lineno = 2530
static uint8_t npc_DOT_lsu_io_in_valid_REG;                                                 // width = 1, lineno = 2571
static uint8_t npc_DOT_wbu_io_in_valid_REG;                                                 // width = 1, lineno = 2595
static uint8_t npc_DOT_icache_DOT_valid;                                                    // width = 4, lineno = 1769
static uint8_t npc_DOT_icache_DOT_s1_in_valid_REG;                                          // width = 1, lineno = 1839
static uint8_t npc_DOT_icache_DOT_beatCnt_value;                                            // width = 2, lineno = 1885
static uint8_t npc_DOT_icache_DOT_state;                                                    // width = 3, lineno = 1891
static uint8_t npc_DOT_icache_DOT_flushReg;                                                 // width = 1, lineno = 1892
static uint8_t npc_DOT_xbar_DOT_stateRead;                                                  // width = 2, lineno = 2151
static uint8_t npc_DOT_xbar_DOT_chosenReadIdxReg_s1;                                        // width = 1, lineno = 2178
static uint8_t npc_DOT_xbar_DOT_stateWrite;                                                 // width = 2, lineno = 2210
static uint8_t npc_DOT_xbar_DOT_chosenWrite;                                                // width = 1, lineno = 2232
static uint8_t npc_DOT_xbar2_DOT_stateRead;                                                 // width = 2, lineno = 2279
static uint64_t npc_DOT_clint_DOT_cnt;                                                      // width = 64, lineno = 2375
static uint8_t npc_DOT_clint_DOT_incCond_c_value;                                           // width = 7, lineno = 2376
static uint8_t npc_DOT_clint_DOT_state;                                                     // width = 1, lineno = 2394
static uint8_t mem_DOT_axi4memctrl_DOT_state_r;                                             // width = 1, lineno = 2834
static uint8_t mem_DOT_axi4memctrl_DOT_state_w;                                             // width = 2, lineno = 2891
static uint16_t npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr;                              // width = 16, lineno = 2321
static uint8_t npc_DOT_clint_DOT_state_DOT_NEXT;                                            // width = 1, lineno = 2394
static uint8_t npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT;                                      // width = 1, lineno = 2418
static uint8_t npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT;                                       // width = 1, lineno = 2415
static uint8_t npc_DOT_lsu_DOT__io_mem_b_ready_T;                                           // width = 1, lineno = 1380
static uint8_t npc_DOT_deq_q_DOT__empty_T;                                                  // width = 1, lineno = 1723
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen;                    // width = 1, lineno = 2535
static uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen;                                       // width = 1, lineno = 2576
static uint8_t npc_DOT_icache_DOT__io_mem_r_ready_T;                                        // width = 1, lineno = 1976
static uint8_t npc_DOT_xbar_DOT_acceptWrite;                                                // width = 1, lineno = 2229
static uint8_t npc_DOT_npctrap_io_valid_REG_DOT_NEXT;                                       // width = 1, lineno = 2805
static uint8_t mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T;                                   // width = 1, lineno = 2861
static uint8_t mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T;                                   // width = 1, lineno = 2928
static uint8_t mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T;                                   // width = 1, lineno = 2937
static uint8_t npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_valid[2];              // width = 1, lineno = 2260
static uint8_t npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[2];             // width = 1, lineno = 2260
static uint64_t npc_DOT_clint_DOT_cnt_DOT_NEXT;                                             // width = 64, lineno = 2375
static uint8_t npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T;                              // width = 1, lineno = 2238
static uint8_t npc_DOT_wbu_DOT__io_wb_wen_T;                                                // width = 1, lineno = 1706
static uint8_t npc_DOT_lsu_DOT__T_3;                                                        // width = 1, lineno = 1400
static uint32_t npc_DOT_lsu_DOT_mcycle_DOT_NEXT;                                            // width = 32, lineno = 1386
static uint8_t npc_DOT_lsu_DOT_memFinish;                                                   // width = 1, lineno = 1203
static uint32_t npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1;                                  // width = 32, lineno = 656
static uint8_t npc_DOT_icache_DOT__idx_s0_T_2;                                              // width = 2, lineno = 1789
static uint32_t npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT;                               // width = 26, lineno = 1797
static uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_res;                                      // width = 32, lineno = 2576
static uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd;                                        // width = 4, lineno = 2576
static uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;                      // width = 32, lineno = 2576
static uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;                     // width = 1, lineno = 2576
static uint8_t npc_DOT_xbar2_DOT_arSelIdx_s1;                                               // width = 1, lineno = 2288
static uint8_t npc_DOT_xbar2_DOT__io_in_r_valid_T_1;                                        // width = 1, lineno = 2340
static uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[2];                // width = 1, lineno = 2147
static uint8_t npc_DOT_icache_DOT__resFromMem_T;                                            // width = 1, lineno = 2005
static uint8_t npc_DOT_xbar2_DOT__io_in_ar_ready_T_4;                                       // width = 1, lineno = 2336
static uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT;                               // width = 1, lineno = 2788
static uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT;                                // width = 32, lineno = 2788
static uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc;                    // width = 32, lineno = 2576
static uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;                 // width = 1, lineno = 2576
static uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;                    // width = 32, lineno = 2576
static uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO;                   // width = 1, lineno = 2576
static uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr;                 // width = 32, lineno = 2576
static uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_pc;                                         // width = 32, lineno = 2788
static uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_dnpc;                                       // width = 32, lineno = 2788
static uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak;                                    // width = 1, lineno = 2788
static uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_code;                                       // width = 32, lineno = 2788
static uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO;                                      // width = 1, lineno = 2788
static uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_memAddr;                                    // width = 32, lineno = 2788
static uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_skip;                                        // width = 1, lineno = 2788
static uint8_t npc_DOT_npctrap_io_valid_REG;                                                // width = 1, lineno = 2805
static uint8_t npc_DOT_npctrap_DOT_valid;                                                   // width = 1, lineno = 2441
static uint8_t npc_DOT_npctrap_DOT_skip;                                                    // width = 1, lineno = 2448
static uint32_t npc_DOT_npctrap_DOT_memAddr;                                                // width = 32, lineno = 2447
static uint8_t npc_DOT_npctrap_DOT_isMMIO;                                                  // width = 1, lineno = 2446
static uint32_t npc_DOT_npctrap_DOT_code;                                                   // width = 32, lineno = 2445
static uint8_t npc_DOT_npctrap_DOT_isEbreak;                                                // width = 1, lineno = 2444
static uint32_t npc_DOT_npctrap_DOT_dnpc;                                                   // width = 32, lineno = 2443
static uint32_t npc_DOT_npctrap_DOT_pc;                                                     // width = 32, lineno = 2442
static uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT;                           // width = 32, lineno = 2788
static uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT;                             // width = 1, lineno = 2788
static uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT;                              // width = 32, lineno = 2788
static uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT;                           // width = 1, lineno = 2788
static uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT;                              // width = 32, lineno = 2788
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen;                                       // width = 1, lineno = 2535
static uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2;                                     // width = 32, lineno = 2535
static uint16_t npc_DOT_lsu_DOT__csrAddr_T;                                                 // width = 12, lineno = 1393
static uint8_t npc_DOT_lsu_DOT__T_4;                                                        // width = 1, lineno = 1402
static uint8_t npc_DOT_lsu_DOT__T_6;                                                        // width = 1, lineno = 1412
static uint8_t npc_DOT_lsu_DOT__T_7;                                                        // width = 1, lineno = 1430
static uint8_t npc_DOT_lsu_DOT__io_fw_wen_T;                                                // width = 1, lineno = 1673
static uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_res;                                      // width = 32, lineno = 2535
static uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_1;                                          // width = 2, lineno = 1301
static uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_2;                                          // width = 1, lineno = 1305
static uint32_t npc_DOT_lsu_DOT_mtvec_DOT_NEXT;                                             // width = 32, lineno = 1382
static uint32_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr;                                       // width = 32, lineno = 1346
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd;                                        // width = 4, lineno = 2535
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore;                   // width = 1, lineno = 2535
static uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_b_DOT__DOT_ready[2];                // width = 1, lineno = 2147
static uint8_t npc_DOT_lsu_DOT_isValidStore;                                                // width = 1, lineno = 1169
static uint8_t npc_DOT_lsu_DOT_sbufWen;                                                     // width = 1, lineno = 1345
static uint32_t npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr;                                         // width = 32, lineno = 1286
static uint8_t npc_DOT_lsu_DOT__io_mem_aw_valid_T_1;                                        // width = 1, lineno = 1373
static uint8_t mem_DOT_dmem_DOT_wen;                                                        // width = 1, lineno = 2949
static uint8_t mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT;                                    // width = 2, lineno = 2891
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad;                    // width = 1, lineno = 2535
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall;                   // width = 1, lineno = 2535
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret;                    // width = 1, lineno = 2535
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal;                   // width = 1, lineno = 2535
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect;                                  // width = 1, lineno = 2535
static uint8_t npc_DOT_lsu_DOT_raiseException;                                              // width = 1, lineno = 1392
static uint8_t npc_DOT_lsu_DOT__io_redirect_valid_T_2;                                      // width = 1, lineno = 1671
static uint32_t npc_DOT_lsu_DOT_mcause_DOT_NEXT;                                            // width = 32, lineno = 1383
static uint32_t npc_DOT_lsu_DOT_mepc_DOT_NEXT;                                              // width = 32, lineno = 1385
static uint8_t npc_DOT_lsu_DOT_isValidLoad;                                                 // width = 1, lineno = 1168
static uint8_t npc_DOT_lsu_DOT__io_out_valid_T_2;                                           // width = 1, lineno = 1695
static uint8_t npc_DOT_lsu_DOT__io_in_ready_T_1;                                            // width = 1, lineno = 1690
static uint8_t npc_DOT__lsu_io_in_valid_T;                                                  // width = 1, lineno = 2566
static uint8_t npc_DOT_lsu_DOT__io_mem_ar_valid_T_1;                                        // width = 1, lineno = 1193
static uint8_t npc_DOT_xbar_DOT_chosenReadIdx;                                              // width = 1, lineno = 2149
static uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[4];                                    // width = 4, lineno = 1296
static uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_3[2];                                    // width = 4, lineno = 1302
static uint8_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size;                                        // width = 2, lineno = 1346
static uint8_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask;                                       // width = 4, lineno = 1346
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3;                    // width = 3, lineno = 2535
static uint8_t npc_DOT_icache_DOT_reqValid;                                                 // width = 1, lineno = 1908
static uint8_t npc_DOT_icache_DOT_flushReg_DOT_NEXT;                                        // width = 1, lineno = 1892
static uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T;                                            // width = 2, lineno = 1291
static uint8_t npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size;     // width = 3, lineno = 1166
static uint8_t mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT;                                  // width = 3, lineno = 2868
static uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_10;                                         // width = 4, lineno = 1315
static uint8_t mem_DOT_dmem_DOT_wmask;                                                      // width = 4, lineno = 2952
static uint32_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata;                                      // width = 32, lineno = 1346
static uint32_t npc_DOT_lsu_DOT_mtvec;                                                      // width = 32, lineno = 1382
static uint32_t npc_DOT_lsu_DOT_mstatus_DOT_NEXT;                                           // width = 32, lineno = 1384
static uint32_t npc_DOT_lsu_DOT_mepc;                                                       // width = 32, lineno = 1385
static uint32_t npc_DOT_lsu_DOT_mvendorid_DOT_NEXT;                                         // width = 32, lineno = 1390
static uint32_t npc_DOT_lsu_DOT__io_redirect_dnpc_T_1;                                      // width = 32, lineno = 1667
static uint32_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT;                             // width = 32, lineno = 1346
static uint32_t mem_DOT_dmem_DOT_wdata;                                                     // width = 32, lineno = 2951
static uint32_t npc_DOT_lsu_DOT_rdataMuxS2;                                                 // width = 32, lineno = 1204
static uint32_t npc_DOT_lsu_DOT_mcause;                                                     // width = 32, lineno = 1383
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR;                     // width = 1, lineno = 2535
static uint8_t npc_DOT_lsu_DOT__WIRE_2[4];                                                  // width = 8, lineno = 1247
static uint8_t npc_DOT_lsu_DOT__WIRE_1[2];                                                  // width = 8, lineno = 1232
static uint32_t npc_DOT_lsu_DOT__io_out_bits_res_T_1;                                       // width = 32, lineno = 1660
static uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;                      // width = 32, lineno = 2535
static uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc;                    // width = 32, lineno = 2535
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;                 // width = 1, lineno = 2535
static uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;                    // width = 32, lineno = 2535
static uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;                     // width = 1, lineno = 2535
static uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT;                             // width = 32, lineno = 2576
static uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT;                               // width = 4, lineno = 2576
static uint32_t npc_DOT_lsu_DOT_marchid_DOT_NEXT;                                           // width = 32, lineno = 1391
static uint32_t npc_DOT_idu_io_in_bits_r_DOT__DOT_inst;                                     // width = 32, lineno = 2479
static uint8_t npc_DOT_idu_DOT_isEbreak;                                                    // width = 1, lineno = 674
static uint8_t npc_DOT_idu_DOT__isStype_T;                                                  // width = 5, lineno = 679
static uint8_t npc_DOT_idu_DOT_isJtype;                                                     // width = 1, lineno = 678
static uint8_t npc_DOT_idu_DOT_isStype;                                                     // width = 1, lineno = 680
static uint8_t npc_DOT_idu_DOT_isBtype;                                                     // width = 1, lineno = 682
static uint8_t npc_DOT_idu_DOT_isRtype;                                                     // width = 1, lineno = 692
static uint8_t npc_DOT_idu_DOT_src2UseReg;                                                  // width = 1, lineno = 901
static uint8_t npc_DOT_idu_DOT_isUtype;                                                     // width = 1, lineno = 676
static uint8_t npc_DOT_idu_DOT_src1UseReg;                                                  // width = 1, lineno = 900
static uint8_t npc_DOT_idu_DOT__rs1_T_1;                                                    // width = 4, lineno = 889
static uint8_t npc_DOT_idu_DOT__rs2_T_1;                                                    // width = 4, lineno = 892
static uint32_t npc_DOT_idu_DOT_MPORT_1;                                                    // width = 32, lineno = 936
static uint8_t npc_DOT_idu_DOT_lsCanFwRs2;                                                  // width = 1, lineno = 924
static uint32_t npc_DOT_idu_DOT_MPORT;                                                      // width = 32, lineno = 929
static uint8_t npc_DOT_idu_DOT_lsCanFwRs1;                                                  // width = 1, lineno = 922
static uint32_t npc_DOT_idu_DOT_MPORT_2;                                                    // width = 32, lineno = 1003
static uint32_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr;                 // width = 32, lineno = 1830
static uint8_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit;                                // width = 1, lineno = 1830
static uint8_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio;                               // width = 1, lineno = 1830
static uint8_t npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT;                                   // width = 2, lineno = 1885
static uint8_t npc_DOT_xbar_DOT_hasReadValid;                                               // width = 1, lineno = 2150
static uint32_t npc_DOT_icache_DOT__tag_s1_T_3;                                             // width = 26, lineno = 1874
static uint8_t npc_DOT_icache_DOT__idx_s1_T_2;                                              // width = 2, lineno = 1861
static uint32_t npc_DOT_icache_DOT_dataRead_s1_MPORT;                                       // width = 32, lineno = 1876
static uint32_t npc_DOT_icache_DOT_dataRead_s1_MPORT_1;                                     // width = 32, lineno = 1877
static uint32_t npc_DOT_icache_DOT_dataRead_s1_MPORT_2;                                     // width = 32, lineno = 1878
static uint32_t npc_DOT_icache_DOT_dataRead_s1_MPORT_3;                                     // width = 32, lineno = 1879
static uint8_t npc_DOT_icache_DOT__wordIdx_s1_T_1;                                          // width = 2, lineno = 1848
static uint32_t npc_DOT_ifu_DOT_pc_s2;                                                      // width = 32, lineno = 664
static uint8_t npc_DOT_xbar_DOT__io_out_ar_valid_T_1;                                       // width = 1, lineno = 2186
static uint8_t npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT;                               // width = 1, lineno = 2178
static uint8_t npc_DOT_xbar_DOT_chosenReadIdxReg_s0;                                        // width = 1, lineno = 2181
static uint32_t npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr[2]; // width = 32, lineno = 2147
static uint32_t npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr;   // width = 32, lineno = 2147
static uint8_t npc_DOT_xbar2_DOT__arSel_1_T_6;                                              // width = 1, lineno = 2277
static uint8_t npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1;                                    // width = 1, lineno = 2325
static uint8_t npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1;                                       // width = 1, lineno = 2285
static uint8_t mem_DOT_dmem_DOT_ren;                                                        // width = 1, lineno = 2946
static uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size[2];  // width = 3, lineno = 2147
static uint8_t mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT;                                  // width = 3, lineno = 2817
static uint8_t npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT;                                      // width = 1, lineno = 2288
static uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[2];               // width = 1, lineno = 2147
static uint8_t npc_DOT_icache_DOT_s1_ok;                                                    // width = 1, lineno = 2092
static uint8_t npc_DOT_icache_DOT__s1_in_ready_T_5;                                         // width = 1, lineno = 2102
static uint8_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT;                      // width = 1, lineno = 1830
static uint8_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT;                       // width = 1, lineno = 1830
static uint8_t npc_DOT_lsu_DOT_state_DOT_NEXT;                                              // width = 2, lineno = 1170
static uint32_t npc_DOT_icache_DOT_dataRead_s1[4];                                          // width = 32, lineno = 1880
static uint32_t npc_DOT_icache_DOT_resFromMem;                                              // width = 32, lineno = 2009
static uint8_t npc_DOT_icache_DOT__io_core_resp_valid_T_2;                                  // width = 1, lineno = 2095
static uint32_t npc_DOT_icache_DOT__res_T_3;                                                // width = 32, lineno = 2015
static uint8_t npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid;                            // width = 1, lineno = 1714
static uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_src1;                                     // width = 32, lineno = 2494
static uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_src2;                                     // width = 32, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_wen;                                       // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_rd;                                        // width = 4, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad;                    // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp;                     // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR;                     // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei;                  // width = 1, lineno = 2494
static uint8_t npc_DOT_idu_DOT_exCanFwRs1;                                                  // width = 1, lineno = 918
static uint8_t npc_DOT_idu_DOT_exCanFwRs2;                                                  // width = 1, lineno = 920
static uint32_t npc_DOT_exu_DOT_xor;                                                        // width = 32, lineno = 1068
static uint8_t npc_DOT_idu_DOT_canIssue;                                                    // width = 1, lineno = 948
static uint32_t npc_DOT_deq_q_DOT_ram_DOT__DOT_pc;                                          // width = 32, lineno = 1716
static uint32_t npc_DOT_deq_q_DOT_ram_DOT__DOT_inst;                                        // width = 32, lineno = 1716
static uint8_t npc_DOT__exu_io_in_valid_T;                                                  // width = 1, lineno = 2525
static uint8_t npc_DOT_exu_io_in_valid_REG_DOT_NEXT;                                        // width = 1, lineno = 2530
static uint8_t npc_DOT_idu_io_in_valid_REG_DOT_NEXT;                                        // width = 1, lineno = 2489
static uint32_t npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT;                            // width = 32, lineno = 2479
static uint32_t npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT;                              // width = 32, lineno = 2479
static uint32_t npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT;                                 // width = 32, lineno = 1716
static uint32_t npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT;                               // width = 32, lineno = 1716
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3;                    // width = 3, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd;               // width = 1, lineno = 2494
static uint32_t npc_DOT_exu_DOT_sum;                                                        // width = 32, lineno = 1067
static uint8_t npc_DOT_exu_DOT_sltu;                                                        // width = 1, lineno = 1069
static uint8_t npc_DOT_exu_DOT_slt;                                                         // width = 1, lineno = 1071
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift;              // width = 1, lineno = 2494
static uint32_t npc_DOT_exu_DOT__aluOut_T_29;                                               // width = 32, lineno = 1106
static uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_src3;                                     // width = 32, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore;                   // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch;                  // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall;                   // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret;                    // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal;                   // width = 1, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen;                    // width = 1, lineno = 2494
static uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;                      // width = 32, lineno = 2494
static uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc;                    // width = 32, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;                 // width = 1, lineno = 2494
static uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;                    // width = 32, lineno = 2494
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;                     // width = 1, lineno = 2494
static uint32_t npc_DOT_idu_io_in_bits_r_DOT__DOT_pc;                                       // width = 32, lineno = 2479
static uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT;         // width = 1, lineno = 2494
static uint32_t mem_DOT_axi4memctrl_DOT_awaddrReg;                                          // width = 32, lineno = 2865
static uint8_t mem_DOT_axi4memctrl_DOT_awsizeReg;                                           // width = 3, lineno = 2868
static uint32_t mem_DOT_dmem_DOT_waddr;                                                     // width = 32, lineno = 2950
static uint8_t mem_DOT_axi4memctrl_DOT_arburstCnt;                                          // width = 8, lineno = 2820
static uint8_t mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T;                               // width = 1, lineno = 2854
static uint8_t npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last[2]; // width = 1, lineno = 2260
static uint8_t npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last;     // width = 1, lineno = 2260
static uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_ready[2];                // width = 1, lineno = 2147
static uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len[2];   // width = 8, lineno = 2147
static uint32_t npc_DOT_icache_DOT_MPORT_4;                                                 // width = 26, lineno = 2082
static uint32_t mem_DOT_axi4memctrl_DOT_araddrReg;                                          // width = 32, lineno = 2814
static uint32_t mem_DOT_dmem_DOT_raddr;                                                     // width = 32, lineno = 2947
static uint32_t mem_DOT_dmem_DOT_rdata;                                                     // width = 32, lineno = 2948
static uint8_t npc_DOT_clint_DOT_isMtimeReg;                                                // width = 1, lineno = 2415
static uint8_t npc_DOT_clint_DOT_isMtimehReg;                                               // width = 1, lineno = 2418
static uint32_t
    npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data[2]; // width = 32, lineno = 2260
static uint32_t npc_DOT_icache_DOT_MPORT_3;                                      // width = 32, lineno = 2075
static uint32_t npc_DOT_icache_DOT_MPORT_2;                                      // width = 32, lineno = 2066
static uint32_t npc_DOT_icache_DOT_MPORT_1;                                      // width = 32, lineno = 2057
static uint32_t npc_DOT_icache_DOT_MPORT;                                        // width = 32, lineno = 2048
static uint8_t clock;                                                            // width = 1, lineno = 2973
static uint8_t mem_DOT_axi4memctrl_DOT_arsizeReg;                                // width = 3, lineno = 2817
static uint32_t npc_DOT_idu_DOT_R[16];                                           // width = 32, lineno = 916
static uint32_t npc_DOT_icache_DOT_tag[4];                                       // width = 26, lineno = 1770
static uint32_t npc_DOT_icache_DOT_data_0[4];                                    // width = 32, lineno = 1772
static uint32_t npc_DOT_icache_DOT_data_1[4];                                    // width = 32, lineno = 1773
static uint32_t npc_DOT_icache_DOT_data_2[4];                                    // width = 32, lineno = 1774
static uint32_t npc_DOT_icache_DOT_data_3[4];                                    // width = 32, lineno = 1775

void gprintf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int fmt_idx = 0;
  while (true) {
    char c = fmt[fmt_idx++];
    switch (c) {
      case '%': break;
      case 0: return;
      default: printf("%c", c); continue;
    }

    unsigned long long lval = 0;
    int bits = va_arg(args, uint32_t);
    if (bits <= 32) {
      lval = va_arg(args, uint32_t);
    } else if (bits <= 64) {
      lval = va_arg(args, unsigned long long);
    } else {
      assert(0);
    }

    c = fmt[fmt_idx++];
    switch (c) {
      case 'd': printf("%lld", lval); break;
      case 'c': printf("%c", (char)lval & 0xff); break;
      case 'x': printf("%llx", lval); break;
      default: assert(0);
    }
  }
}
void STop_init() {
  cycles = 0;
  LOG_START = 0;
  LOG_END = 100;
  init();
}
void init() {
  activateAll();
  npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[0] = 0x1;
  npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[1] = 0x2;
  npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[2] = 0x4;
  npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[3] = 0x8;
  npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_3[0] = 0x3;
  npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_3[1] = 0xc;
}
void activateAll() {
  memset(activeFlags, 0xff, sizeof(activeFlags));
}
void set_clock(uint8_t val) {
  if (clock != val) {
    clock = val;
  }
}
void set_reset(uint8_t val) {
  if (reset != val) {
    reset = val;
    activeFlags[0] |= 0x3; // 0 1
  }
}
void subReset0() {
  if (reset) {
    npc_DOT_ifu_DOT_PC = 0x80000000;
    npc_DOT_lsu_DOT_state = 0x0;
    npc_DOT_lsu_DOT_state_DOT_NEXT = 0x0;
    npc_DOT_lsu_DOT_sbufState = 0x0;
    npc_DOT_lsu_DOT_mstatus = 0x1800;
    npc_DOT_lsu_DOT_mstatus_DOT_NEXT = 0x1800;
    npc_DOT_lsu_DOT_mcycle = 0x0;
    npc_DOT_lsu_DOT_mcycle_DOT_NEXT = 0x0;
    npc_DOT_lsu_DOT_mvendorid = 0x79737978;
    npc_DOT_lsu_DOT_mvendorid_DOT_NEXT = 0x79737978;
    npc_DOT_lsu_DOT_marchid = 0x12211d6;
    npc_DOT_lsu_DOT_marchid_DOT_NEXT = 0x12211d6;
    npc_DOT_deq_q_DOT_maybe_full = 0x0;
    npc_DOT_idu_io_in_valid_REG = 0x0;
    npc_DOT_idu_io_in_valid_REG_DOT_NEXT = 0x0;
    npc_DOT_exu_io_in_valid_REG = 0x0;
    npc_DOT_exu_io_in_valid_REG_DOT_NEXT = 0x0;
    npc_DOT_lsu_io_in_valid_REG = 0x0;
    npc_DOT_wbu_io_in_valid_REG = 0x0;
    npc_DOT_icache_DOT_valid = 0x0;
    npc_DOT_icache_DOT_s1_in_valid_REG = 0x0;
    npc_DOT_icache_DOT_beatCnt_value = 0x0;
    npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT = 0x0;
    npc_DOT_icache_DOT_state = 0x0;
    npc_DOT_icache_DOT_flushReg = 0x0;
    npc_DOT_icache_DOT_flushReg_DOT_NEXT = 0x0;
    npc_DOT_xbar_DOT_stateRead = 0x0;
    npc_DOT_xbar_DOT_chosenReadIdxReg_s1 = 0x0;
    npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT = 0x0;
    npc_DOT_xbar_DOT_stateWrite = 0x0;
    npc_DOT_xbar_DOT_chosenWrite = 0x0;
    npc_DOT_xbar2_DOT_stateRead = 0x0;
    npc_DOT_clint_DOT_cnt = 0x0;
    npc_DOT_clint_DOT_cnt_DOT_NEXT = 0x0;
    npc_DOT_clint_DOT_incCond_c_value = 0x0;
    npc_DOT_clint_DOT_state = 0x0;
    npc_DOT_clint_DOT_state_DOT_NEXT = 0x0;
    mem_DOT_axi4memctrl_DOT_state_r = 0x0;
    mem_DOT_axi4memctrl_DOT_state_w = 0x0;
    mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT = 0x0;
  } else {
  }
}
void resetAll() {
  if (unlikely(reset)) {
    *(uint64_t *)&activeFlags[0] |=
        0x9e734fc7e5e9c; // 51 48 47 46 45 42 41 40 37 36 34 31 30 29 28 27 26 22 21 20 19 18 17 14 12 11 10 9 2 3 4 7
    subReset0();
  }
}
void subStep0() {
  if (unlikely(activeFlags[0] & 0x1)) { // id=0
    uint8_t npc_DOT_lsu_DOT__T_23;
    npc_DOT_lsu_DOT__T_23 = ((uint8_t)reset & 0x1);
    uint8_t npc_DOT_lsu_DOT__T_24_DOT_old_DOT_909 = npc_DOT_lsu_DOT__T_24;
    npc_DOT_lsu_DOT__T_24 = (npc_DOT_lsu_DOT__T_23 == 0x0);
    bool cond_npc_DOT_lsu_DOT__T_24 = npc_DOT_lsu_DOT__T_24 ^ npc_DOT_lsu_DOT__T_24_DOT_old_DOT_909;
    activeFlags[0] |= -(uint8_t)cond_npc_DOT_lsu_DOT__T_24 & 0x80; // 7
    activeFlags[1] |= cond_npc_DOT_lsu_DOT__T_24;                  // 8
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 0 reset: ", cycles);
      printf("%lx", (uint64_t)reset);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 0 npc_DOT_xbar2_DOT_arSel_s1_0: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSel_s1_0);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 0 npc_DOT_xbar2_DOT_arSel_s1_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSel_s1_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 0 npc_DOT_lsu_DOT__T_23: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_23);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 0 npc_DOT_lsu_DOT__T_24: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_24);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[0] & 0x2)) { // id=1
    if (reset) {
      uint32_t npc_DOT_ifu_DOT_PC_DOT_old_DOT_53 = npc_DOT_ifu_DOT_PC;
      npc_DOT_ifu_DOT_PC = 0x80000000;
      bool cond_npc_DOT_ifu_DOT_PC = npc_DOT_ifu_DOT_PC != npc_DOT_ifu_DOT_PC_DOT_old_DOT_53;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_ifu_DOT_PC & 0x8; // 3
      activeFlags[2] |= cond_npc_DOT_ifu_DOT_PC << 4;            // 20
      uint8_t npc_DOT_lsu_DOT_state_DOT_old_DOT_672 = npc_DOT_lsu_DOT_state;
      npc_DOT_lsu_DOT_state = 0x0;
      bool cond_npc_DOT_lsu_DOT_state = npc_DOT_lsu_DOT_state != npc_DOT_lsu_DOT_state_DOT_old_DOT_672;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_lsu_DOT_state & 0x8;                       // 3
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_lsu_DOT_state & 0x20080800; // 29 19 11
      npc_DOT_lsu_DOT_state_DOT_NEXT = 0x0;
      uint8_t npc_DOT_lsu_DOT_sbufState_DOT_old_DOT_757 = npc_DOT_lsu_DOT_sbufState;
      npc_DOT_lsu_DOT_sbufState = 0x0;
      bool cond_npc_DOT_lsu_DOT_sbufState = npc_DOT_lsu_DOT_sbufState != npc_DOT_lsu_DOT_sbufState_DOT_old_DOT_757;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_lsu_DOT_sbufState & 0x8; // 3
      activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT_sbufState & 0x6; // 9 10
      uint32_t npc_DOT_lsu_DOT_mstatus_DOT_old_DOT_846 = npc_DOT_lsu_DOT_mstatus;
      npc_DOT_lsu_DOT_mstatus = 0x1800;
      bool cond_npc_DOT_lsu_DOT_mstatus = npc_DOT_lsu_DOT_mstatus != npc_DOT_lsu_DOT_mstatus_DOT_old_DOT_846;
      activeFlags[1] |= cond_npc_DOT_lsu_DOT_mstatus << 6; // 14
      npc_DOT_lsu_DOT_mstatus_DOT_NEXT = 0x1800;
      uint32_t npc_DOT_lsu_DOT_mcycle_DOT_old_DOT_850 = npc_DOT_lsu_DOT_mcycle;
      npc_DOT_lsu_DOT_mcycle = 0x0;
      bool cond_npc_DOT_lsu_DOT_mcycle = npc_DOT_lsu_DOT_mcycle != npc_DOT_lsu_DOT_mcycle_DOT_old_DOT_850;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_lsu_DOT_mcycle & 0x8; // 3
      activeFlags[1] |= cond_npc_DOT_lsu_DOT_mcycle << 6;            // 14
      npc_DOT_lsu_DOT_mcycle_DOT_NEXT = 0x0;
      uint32_t npc_DOT_lsu_DOT_mvendorid_DOT_old_DOT_854 = npc_DOT_lsu_DOT_mvendorid;
      npc_DOT_lsu_DOT_mvendorid = 0x79737978;
      bool cond_npc_DOT_lsu_DOT_mvendorid = npc_DOT_lsu_DOT_mvendorid != npc_DOT_lsu_DOT_mvendorid_DOT_old_DOT_854;
      activeFlags[1] |= cond_npc_DOT_lsu_DOT_mvendorid << 6; // 14
      npc_DOT_lsu_DOT_mvendorid_DOT_NEXT = 0x79737978;
      uint32_t npc_DOT_lsu_DOT_marchid_DOT_old_DOT_856 = npc_DOT_lsu_DOT_marchid;
      npc_DOT_lsu_DOT_marchid = 0x12211d6;
      bool cond_npc_DOT_lsu_DOT_marchid = npc_DOT_lsu_DOT_marchid != npc_DOT_lsu_DOT_marchid_DOT_old_DOT_856;
      activeFlags[1] |= cond_npc_DOT_lsu_DOT_marchid << 6; // 14
      npc_DOT_lsu_DOT_marchid_DOT_NEXT = 0x12211d6;
      uint8_t npc_DOT_deq_q_DOT_maybe_full_DOT_old_DOT_1003 = npc_DOT_deq_q_DOT_maybe_full;
      npc_DOT_deq_q_DOT_maybe_full = 0x0;
      bool cond_npc_DOT_deq_q_DOT_maybe_full =
          npc_DOT_deq_q_DOT_maybe_full ^ npc_DOT_deq_q_DOT_maybe_full_DOT_old_DOT_1003;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_deq_q_DOT_maybe_full & 0x8; // 3
      uint8_t npc_DOT_idu_io_in_valid_REG_DOT_old_DOT_1043 = npc_DOT_idu_io_in_valid_REG;
      npc_DOT_idu_io_in_valid_REG = 0x0;
      bool cond_npc_DOT_idu_io_in_valid_REG =
          npc_DOT_idu_io_in_valid_REG ^ npc_DOT_idu_io_in_valid_REG_DOT_old_DOT_1043;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_idu_io_in_valid_REG & 0x4400000; // 26 22
      npc_DOT_idu_io_in_valid_REG_DOT_NEXT = 0x0;
      uint8_t npc_DOT_exu_io_in_valid_REG_DOT_old_DOT_1108 = npc_DOT_exu_io_in_valid_REG;
      npc_DOT_exu_io_in_valid_REG = 0x0;
      bool cond_npc_DOT_exu_io_in_valid_REG =
          npc_DOT_exu_io_in_valid_REG ^ npc_DOT_exu_io_in_valid_REG_DOT_old_DOT_1108;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_exu_io_in_valid_REG & 0x80600800; // 31 22 21 11
      npc_DOT_exu_io_in_valid_REG_DOT_NEXT = 0x0;
      uint8_t npc_DOT_lsu_io_in_valid_REG_DOT_old_DOT_1173 = npc_DOT_lsu_io_in_valid_REG;
      npc_DOT_lsu_io_in_valid_REG = 0x0;
      bool cond_npc_DOT_lsu_io_in_valid_REG =
          npc_DOT_lsu_io_in_valid_REG ^ npc_DOT_lsu_io_in_valid_REG_DOT_old_DOT_1173;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_lsu_io_in_valid_REG & 0x88; // 3 7
      activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_io_in_valid_REG & 0xa;  // 9 11
      uint8_t npc_DOT_wbu_io_in_valid_REG_DOT_old_DOT_1204 = npc_DOT_wbu_io_in_valid_REG;
      npc_DOT_wbu_io_in_valid_REG = 0x0;
      bool cond_npc_DOT_wbu_io_in_valid_REG =
          npc_DOT_wbu_io_in_valid_REG ^ npc_DOT_wbu_io_in_valid_REG_DOT_old_DOT_1204;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_wbu_io_in_valid_REG & 0x8; // 3
      activeFlags[1] |= cond_npc_DOT_wbu_io_in_valid_REG << 3;            // 11
      uint8_t npc_DOT_icache_DOT_valid_DOT_old_DOT_1250 = npc_DOT_icache_DOT_valid;
      npc_DOT_icache_DOT_valid = 0x0;
      bool cond_npc_DOT_icache_DOT_valid = npc_DOT_icache_DOT_valid != npc_DOT_icache_DOT_valid_DOT_old_DOT_1250;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_valid & 0x80080000; // 31 19
      uint8_t npc_DOT_icache_DOT_s1_in_valid_REG_DOT_old_DOT_1359 = npc_DOT_icache_DOT_s1_in_valid_REG;
      npc_DOT_icache_DOT_s1_in_valid_REG = 0x0;
      bool cond_npc_DOT_icache_DOT_s1_in_valid_REG =
          npc_DOT_icache_DOT_s1_in_valid_REG ^ npc_DOT_icache_DOT_s1_in_valid_REG_DOT_old_DOT_1359;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_s1_in_valid_REG & 0x181000; // 20 19 12
      uint8_t npc_DOT_icache_DOT_beatCnt_value_DOT_old_DOT_1393 = npc_DOT_icache_DOT_beatCnt_value;
      npc_DOT_icache_DOT_beatCnt_value = 0x0;
      bool cond_npc_DOT_icache_DOT_beatCnt_value =
          npc_DOT_icache_DOT_beatCnt_value != npc_DOT_icache_DOT_beatCnt_value_DOT_old_DOT_1393;
      *(uint64_t *)&activeFlags[0] |= -(uint64_t)cond_npc_DOT_icache_DOT_beatCnt_value & 0x400120000; // 34 17 20
      npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT = 0x0;
      uint8_t npc_DOT_icache_DOT_state_DOT_old_DOT_1401 = npc_DOT_icache_DOT_state;
      npc_DOT_icache_DOT_state = 0x0;
      bool cond_npc_DOT_icache_DOT_state = npc_DOT_icache_DOT_state != npc_DOT_icache_DOT_state_DOT_old_DOT_1401;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_icache_DOT_state & 0x8;                       // 3
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_state & 0x401a1000; // 30 20 19 17 12
      uint8_t npc_DOT_icache_DOT_flushReg_DOT_old_DOT_1403 = npc_DOT_icache_DOT_flushReg;
      npc_DOT_icache_DOT_flushReg = 0x0;
      bool cond_npc_DOT_icache_DOT_flushReg =
          npc_DOT_icache_DOT_flushReg ^ npc_DOT_icache_DOT_flushReg_DOT_old_DOT_1403;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_flushReg & 0x40100000; // 30 20
      npc_DOT_icache_DOT_flushReg_DOT_NEXT = 0x0;
      uint8_t npc_DOT_xbar_DOT_stateRead_DOT_old_DOT_1712 = npc_DOT_xbar_DOT_stateRead;
      npc_DOT_xbar_DOT_stateRead = 0x0;
      bool cond_npc_DOT_xbar_DOT_stateRead = npc_DOT_xbar_DOT_stateRead != npc_DOT_xbar_DOT_stateRead_DOT_old_DOT_1712;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_xbar_DOT_stateRead & 0x200c0000; // 29 18 19
      uint8_t npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_old_DOT_1736 = npc_DOT_xbar_DOT_chosenReadIdxReg_s1;
      npc_DOT_xbar_DOT_chosenReadIdxReg_s1 = 0x0;
      bool cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s1 =
          npc_DOT_xbar_DOT_chosenReadIdxReg_s1 ^ npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_old_DOT_1736;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s1 & 0x10;                      // 4
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s1 & 0x20040000; // 29 18
      npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT = 0x0;
      uint8_t npc_DOT_xbar_DOT_stateWrite_DOT_old_DOT_1775 = npc_DOT_xbar_DOT_stateWrite;
      npc_DOT_xbar_DOT_stateWrite = 0x0;
      bool cond_npc_DOT_xbar_DOT_stateWrite =
          npc_DOT_xbar_DOT_stateWrite != npc_DOT_xbar_DOT_stateWrite_DOT_old_DOT_1775;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_xbar_DOT_stateWrite & 0x8; // 3
      activeFlags[1] |= cond_npc_DOT_xbar_DOT_stateWrite << 1;            // 9
      uint8_t npc_DOT_xbar_DOT_chosenWrite_DOT_old_DOT_1794 = npc_DOT_xbar_DOT_chosenWrite;
      npc_DOT_xbar_DOT_chosenWrite = 0x0;
      bool cond_npc_DOT_xbar_DOT_chosenWrite =
          npc_DOT_xbar_DOT_chosenWrite ^ npc_DOT_xbar_DOT_chosenWrite_DOT_old_DOT_1794;
      activeFlags[1] |= cond_npc_DOT_xbar_DOT_chosenWrite << 1; // 9
      uint8_t npc_DOT_xbar2_DOT_stateRead_DOT_old_DOT_1878 = npc_DOT_xbar2_DOT_stateRead;
      npc_DOT_xbar2_DOT_stateRead = 0x0;
      bool cond_npc_DOT_xbar2_DOT_stateRead =
          npc_DOT_xbar2_DOT_stateRead != npc_DOT_xbar2_DOT_stateRead_DOT_old_DOT_1878;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_xbar2_DOT_stateRead & 0x14;                      // 2 4
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_xbar2_DOT_stateRead & 0x10040000; // 28 18
      uint64_t npc_DOT_clint_DOT_cnt_DOT_old_DOT_1958 = npc_DOT_clint_DOT_cnt;
      npc_DOT_clint_DOT_cnt = 0x0;
      bool cond_npc_DOT_clint_DOT_cnt = npc_DOT_clint_DOT_cnt != npc_DOT_clint_DOT_cnt_DOT_old_DOT_1958;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_clint_DOT_cnt & 0x8; // 3
      activeFlags[4] |= cond_npc_DOT_clint_DOT_cnt << 2;            // 34
      npc_DOT_clint_DOT_cnt_DOT_NEXT = 0x0;
      uint8_t npc_DOT_clint_DOT_incCond_c_value_DOT_old_DOT_1960 = npc_DOT_clint_DOT_incCond_c_value;
      npc_DOT_clint_DOT_incCond_c_value = 0x0;
      bool cond_npc_DOT_clint_DOT_incCond_c_value =
          npc_DOT_clint_DOT_incCond_c_value != npc_DOT_clint_DOT_incCond_c_value_DOT_old_DOT_1960;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_clint_DOT_incCond_c_value & 0x8; // 3
      uint8_t npc_DOT_clint_DOT_state_DOT_old_DOT_1974 = npc_DOT_clint_DOT_state;
      npc_DOT_clint_DOT_state = 0x0;
      bool cond_npc_DOT_clint_DOT_state = npc_DOT_clint_DOT_state ^ npc_DOT_clint_DOT_state_DOT_old_DOT_1974;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_clint_DOT_state & 0xc; // 2 3
      npc_DOT_clint_DOT_state_DOT_NEXT = 0x0;
      uint8_t mem_DOT_axi4memctrl_DOT_state_r_DOT_old_DOT_2179 = mem_DOT_axi4memctrl_DOT_state_r;
      mem_DOT_axi4memctrl_DOT_state_r = 0x0;
      bool cond_mem_DOT_axi4memctrl_DOT_state_r =
          mem_DOT_axi4memctrl_DOT_state_r ^ mem_DOT_axi4memctrl_DOT_state_r_DOT_old_DOT_2179;
      activeFlags[0] |= -(uint8_t)cond_mem_DOT_axi4memctrl_DOT_state_r & 0x8;                       // 3
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_mem_DOT_axi4memctrl_DOT_state_r & 0x80040000; // 31 18
      uint8_t mem_DOT_axi4memctrl_DOT_state_w_DOT_old_DOT_2225 = mem_DOT_axi4memctrl_DOT_state_w;
      mem_DOT_axi4memctrl_DOT_state_w = 0x0;
      bool cond_mem_DOT_axi4memctrl_DOT_state_w =
          mem_DOT_axi4memctrl_DOT_state_w != mem_DOT_axi4memctrl_DOT_state_w_DOT_old_DOT_2225;
      activeFlags[0] |= -(uint8_t)cond_mem_DOT_axi4memctrl_DOT_state_w & 0x8;                      // 3
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_mem_DOT_axi4memctrl_DOT_state_w & 0x8000400; // 27 10
      mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT = 0x0;
    } else {
    }
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_ifu_DOT_PC: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_ifu_DOT_PC);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_lsu_DOT_state: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_state);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_lsu_DOT_sbufState: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbufState);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_lsu_DOT_mstatus: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mstatus);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_lsu_DOT_mcycle: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mcycle);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_lsu_DOT_mvendorid: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mvendorid);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_lsu_DOT_marchid: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_marchid);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_deq_q_DOT_maybe_full: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_maybe_full);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_idu_io_in_valid_REG: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_idu_io_in_valid_REG);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_exu_io_in_valid_REG: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_exu_io_in_valid_REG);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_lsu_io_in_valid_REG: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_io_in_valid_REG);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_wbu_io_in_valid_REG: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_valid_REG);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_icache_DOT_valid: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_valid);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_icache_DOT_s1_in_valid_REG: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_valid_REG);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_icache_DOT_beatCnt_value: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_beatCnt_value);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_icache_DOT_state: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_state);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_icache_DOT_flushReg: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_flushReg);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_xbar_DOT_stateRead: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar_DOT_stateRead);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_xbar_DOT_chosenReadIdxReg_s1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar_DOT_chosenReadIdxReg_s1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_xbar_DOT_stateWrite: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar_DOT_stateWrite);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_xbar_DOT_chosenWrite: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar_DOT_chosenWrite);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_xbar2_DOT_stateRead: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_stateRead);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_clint_DOT_cnt: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_cnt);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_clint_DOT_incCond_c_value: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_incCond_c_value);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 npc_DOT_clint_DOT_state: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_state);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 mem_DOT_axi4memctrl_DOT_state_r: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_state_r);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 1 mem_DOT_axi4memctrl_DOT_state_w: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_state_w);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[0] & 0x4)) { // id=2
    uint8_t npc_DOT_xbar2_DOT__io_out_0_ar_valid_T = 0;
    uint8_t npc_DOT_clint_DOT__state_T_1 = 0;
    uint8_t npc_DOT_clint_DOT__state_T_2 = 0;
    uint8_t npc_DOT_clint_DOT__state_T_3 = 0;
    uint8_t npc_DOT_clint_DOT__state_T_6 = 0;
    uint8_t npc_DOT_clint_DOT__state_T_7 = 0;
    uint8_t npc_DOT_xbar2_DOT__io_out_0_ar_valid_T_1 = 0;
    uint8_t npc_DOT_clint_DOT__state_T_4 = 0;
    uint8_t npc_DOT_clint_DOT__state_T_5 = 0;
    uint8_t npc_DOT_clint_DOT__state_T_8 = 0;
    uint8_t npc_DOT_clint_DOT_isMtime = 0;
    uint8_t npc_DOT_clint_DOT_isMtimeh = 0;
    npc_DOT_xbar2_DOT__io_out_0_ar_valid_T = (npc_DOT_xbar2_DOT_stateRead == 0x3);
    npc_DOT_clint_DOT__state_T_1 = (!npc_DOT_xbar2_DOT_arSel_s1_0);
    npc_DOT_clint_DOT__state_T_2 = (0x0 == npc_DOT_clint_DOT_state);
    npc_DOT_clint_DOT__state_T_3 = npc_DOT_clint_DOT_state;
    npc_DOT_clint_DOT__state_T_6 = ((uint8_t)npc_DOT_clint_DOT__state_T_1 & 0x1);
    npc_DOT_clint_DOT__state_T_7 = (npc_DOT_clint_DOT__state_T_3 & npc_DOT_clint_DOT__state_T_6);
    npc_DOT_xbar2_DOT__io_out_0_ar_valid_T_1 = (npc_DOT_xbar2_DOT__io_out_0_ar_valid_T & npc_DOT_xbar2_DOT_arSel_s1_0);
    npc_DOT_clint_DOT__state_T_4 = ((uint8_t)npc_DOT_xbar2_DOT__io_out_0_ar_valid_T_1 & 0x1);
    npc_DOT_clint_DOT__state_T_5 = (npc_DOT_clint_DOT__state_T_2 & npc_DOT_clint_DOT__state_T_4);
    npc_DOT_clint_DOT__state_T_8 = (npc_DOT_clint_DOT__state_T_5 | npc_DOT_clint_DOT__state_T_7);
    uint8_t npc_DOT_clint_DOT_state_DOT_NEXT_DOT_old_DOT_1975 = npc_DOT_clint_DOT_state_DOT_NEXT;
    npc_DOT_clint_DOT_state_DOT_NEXT = npc_DOT_clint_DOT__state_T_8;
    bool cond_npc_DOT_clint_DOT_state_DOT_NEXT =
        npc_DOT_clint_DOT_state_DOT_NEXT ^ npc_DOT_clint_DOT_state_DOT_NEXT_DOT_old_DOT_1975;
    activeFlags[6] |= cond_npc_DOT_clint_DOT_state_DOT_NEXT; // 48
    if (npc_DOT_xbar2_DOT__io_out_0_ar_valid_T_1) {
      npc_DOT_clint_DOT_isMtime = (npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr == 0xbff8);
      npc_DOT_clint_DOT_isMtimeh = (npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr == 0xbffc);
      uint8_t npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT_DOT_old_DOT_1994 = npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT;
      npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT = npc_DOT_clint_DOT_isMtimeh;
      bool cond_npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT =
          npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT ^ npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT_DOT_old_DOT_1994;
      activeFlags[6] |= cond_npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT; // 48
      uint8_t npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT_DOT_old_DOT_1991 = npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT;
      npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT = npc_DOT_clint_DOT_isMtime;
      bool cond_npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT =
          npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT ^ npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT_DOT_old_DOT_1991;
      activeFlags[6] |= cond_npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT; // 48
    } else {
    }
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_xbar2_DOT__io_out_0_ar_valid_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_out_0_ar_valid_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT__state_T_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__state_T_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT__state_T_2: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__state_T_2);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT__state_T_3: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__state_T_3);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT__state_T_6: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__state_T_6);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT__state_T_7: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__state_T_7);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_xbar2_DOT__io_out_0_ar_valid_T_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_out_0_ar_valid_T_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT__state_T_4: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__state_T_4);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT__state_T_5: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__state_T_5);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT__state_T_8: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__state_T_8);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT_state_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_state_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT_isMtime: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_isMtime);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT_isMtimeh: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_isMtimeh);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 2 npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[0] & 0x8)) { // id=3
    uint32_t npc_DOT_ifu_DOT__io_mem_req_bits_addr_T = 0;
    uint8_t npc_DOT_lsu_DOT__memFinish_T = 0;
    uint32_t npc_DOT_lsu_DOT__mcycle_T = 0;
    uint8_t npc_DOT_clint_DOT_incCond_wrap_wrap = 0;
    uint8_t npc_DOT_clint_DOT__io_ar_ready_T = 0;
    uint8_t npc_DOT_clint_DOT__io_r_valid_T = 0;
    uint8_t mem_DOT_axi4memctrl_DOT__io_axi_ar_ready_T = 0;
    uint8_t npc_DOT_clint_DOT__incCond_wrap_value_T = 0;
    uint64_t npc_DOT_clint_DOT__cnt_T = 0;
    uint8_t npc_DOT_icache_DOT__idx_s0_WIRE_1 = 0;
    npc_DOT_ifu_DOT__io_mem_req_bits_addr_T = ((npc_DOT_ifu_DOT_PC >> 2) & 0x3fffffff);
    npc_DOT_lsu_DOT__memFinish_T = (npc_DOT_lsu_DOT_state == 0x2);
    uint8_t npc_DOT_lsu_DOT__io_mem_b_ready_T_DOT_old_DOT_841 = npc_DOT_lsu_DOT__io_mem_b_ready_T;
    npc_DOT_lsu_DOT__io_mem_b_ready_T = (npc_DOT_lsu_DOT_sbufState == 0x2);
    bool cond_npc_DOT_lsu_DOT__io_mem_b_ready_T =
        npc_DOT_lsu_DOT__io_mem_b_ready_T ^ npc_DOT_lsu_DOT__io_mem_b_ready_T_DOT_old_DOT_841;
    activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT__io_mem_b_ready_T & 0x6; // 9 10
    npc_DOT_lsu_DOT__mcycle_T = ((npc_DOT_lsu_DOT_mcycle + 0x1) & 0xffffffff);
    uint8_t npc_DOT_deq_q_DOT__empty_T_DOT_old_DOT_1006 = npc_DOT_deq_q_DOT__empty_T;
    npc_DOT_deq_q_DOT__empty_T = (npc_DOT_deq_q_DOT_maybe_full == 0x0);
    bool cond_npc_DOT_deq_q_DOT__empty_T = npc_DOT_deq_q_DOT__empty_T ^ npc_DOT_deq_q_DOT__empty_T_DOT_old_DOT_1006;
    *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_deq_q_DOT__empty_T & 0x40580000; // 30 19 20 22
    uint8_t npc_DOT_icache_DOT__io_mem_r_ready_T_DOT_old_DOT_1474 = npc_DOT_icache_DOT__io_mem_r_ready_T;
    npc_DOT_icache_DOT__io_mem_r_ready_T = (npc_DOT_icache_DOT_state == 0x3);
    bool cond_npc_DOT_icache_DOT__io_mem_r_ready_T =
        npc_DOT_icache_DOT__io_mem_r_ready_T ^ npc_DOT_icache_DOT__io_mem_r_ready_T_DOT_old_DOT_1474;
    activeFlags[0] |= -(uint8_t)cond_npc_DOT_icache_DOT__io_mem_r_ready_T & 0x10; // 4
    activeFlags[3] |= cond_npc_DOT_icache_DOT__io_mem_r_ready_T << 5;             // 29
    uint8_t npc_DOT_xbar_DOT_acceptWrite_DOT_old_DOT_1791 = npc_DOT_xbar_DOT_acceptWrite;
    npc_DOT_xbar_DOT_acceptWrite = (npc_DOT_xbar_DOT_stateWrite == 0x0);
    bool cond_npc_DOT_xbar_DOT_acceptWrite =
        npc_DOT_xbar_DOT_acceptWrite ^ npc_DOT_xbar_DOT_acceptWrite_DOT_old_DOT_1791;
    activeFlags[1] |= cond_npc_DOT_xbar_DOT_acceptWrite << 1; // 9
    npc_DOT_clint_DOT_incCond_wrap_wrap = (npc_DOT_clint_DOT_incCond_c_value == 0x63);
    npc_DOT_clint_DOT__io_ar_ready_T = (npc_DOT_clint_DOT_state == 0x0);
    npc_DOT_clint_DOT__io_r_valid_T = npc_DOT_clint_DOT_state;
    uint8_t npc_DOT_npctrap_io_valid_REG_DOT_NEXT_DOT_old_DOT_2091 = npc_DOT_npctrap_io_valid_REG_DOT_NEXT;
    npc_DOT_npctrap_io_valid_REG_DOT_NEXT = npc_DOT_wbu_io_in_valid_REG;
    bool cond_npc_DOT_npctrap_io_valid_REG_DOT_NEXT =
        npc_DOT_npctrap_io_valid_REG_DOT_NEXT ^ npc_DOT_npctrap_io_valid_REG_DOT_NEXT_DOT_old_DOT_2091;
    activeFlags[5] |= cond_npc_DOT_npctrap_io_valid_REG_DOT_NEXT; // 40
    uint8_t mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T_DOT_old_DOT_2199 = mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T;
    mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T = mem_DOT_axi4memctrl_DOT_state_r;
    bool cond_mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T =
        mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T ^ mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T_DOT_old_DOT_2199;
    *(uint64_t *)&activeFlags[0] |= -(uint64_t)cond_mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T & 0x880000000; // 35 31
    mem_DOT_axi4memctrl_DOT__io_axi_ar_ready_T = (mem_DOT_axi4memctrl_DOT_state_r == 0x0);
    uint8_t mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_DOT_old_DOT_2252 = mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T;
    mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T = (mem_DOT_axi4memctrl_DOT_state_w == 0x0);
    bool cond_mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T =
        mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T ^ mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_DOT_old_DOT_2252;
    *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T & 0x8000400; // 27 10
    uint8_t mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T_DOT_old_DOT_2257 = mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T;
    mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T = (mem_DOT_axi4memctrl_DOT_state_w == 0x2);
    bool cond_mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T =
        mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T ^ mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T_DOT_old_DOT_2257;
    activeFlags[1] |= -(uint8_t)cond_mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T & 0x6; // 9 10
    npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_valid[0] = npc_DOT_clint_DOT__io_r_valid_T;
    activeFlags[0] |= 0x10; // 4
    activeFlags[3] |= 0x10; // 28
    npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_valid[1] = mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T;
    activeFlags[0] |= 0x10; // 4
    activeFlags[3] |= 0x10; // 28
    npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[0] = npc_DOT_clint_DOT__io_ar_ready_T;
    activeFlags[0] |= 0x10; // 4
    activeFlags[3] |= 0x10; // 28
    npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[1] = mem_DOT_axi4memctrl_DOT__io_axi_ar_ready_T;
    activeFlags[0] |= 0x10; // 4
    activeFlags[3] |= 0x10; // 28
    if (npc_DOT_clint_DOT_incCond_wrap_wrap) {
      npc_DOT_clint_DOT__cnt_T = ((npc_DOT_clint_DOT_cnt + 0x1) & 0xffffffffffffffff);
      uint64_t npc_DOT_clint_DOT_cnt_DOT_NEXT_DOT_old_DOT_1959 = npc_DOT_clint_DOT_cnt_DOT_NEXT;
      npc_DOT_clint_DOT_cnt_DOT_NEXT = npc_DOT_clint_DOT__cnt_T;
      bool cond_npc_DOT_clint_DOT_cnt_DOT_NEXT =
          npc_DOT_clint_DOT_cnt_DOT_NEXT != npc_DOT_clint_DOT_cnt_DOT_NEXT_DOT_old_DOT_1959;
      activeFlags[5] |= cond_npc_DOT_clint_DOT_cnt_DOT_NEXT; // 40
      uint8_t npc_DOT_clint_DOT_incCond_c_value_DOT_old_DOT_1961 = npc_DOT_clint_DOT_incCond_c_value;
      npc_DOT_clint_DOT_incCond_c_value = 0x0;
      bool cond_npc_DOT_clint_DOT_incCond_c_value =
          npc_DOT_clint_DOT_incCond_c_value != npc_DOT_clint_DOT_incCond_c_value_DOT_old_DOT_1961;
      activeFlags[0] |= cond_npc_DOT_clint_DOT_incCond_c_value << 3; // 3
    } else {
      npc_DOT_clint_DOT__incCond_wrap_value_T = ((npc_DOT_clint_DOT_incCond_c_value + 0x1) & 0x7f);
      uint8_t npc_DOT_clint_DOT_incCond_c_value_DOT_old_DOT_1961 = npc_DOT_clint_DOT_incCond_c_value;
      npc_DOT_clint_DOT_incCond_c_value = npc_DOT_clint_DOT__incCond_wrap_value_T;
      bool cond_npc_DOT_clint_DOT_incCond_c_value =
          npc_DOT_clint_DOT_incCond_c_value != npc_DOT_clint_DOT_incCond_c_value_DOT_old_DOT_1961;
      activeFlags[0] |= cond_npc_DOT_clint_DOT_incCond_c_value << 3; // 3
    }
    uint8_t npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T_DOT_old_DOT_1798 =
        npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T;
    npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T =
        (mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T & npc_DOT_xbar_DOT_acceptWrite);
    bool cond_npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T =
        npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T ^
        npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T_DOT_old_DOT_1798;
    activeFlags[1] |= cond_npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T << 1; // 9
    uint8_t npc_DOT_wbu_DOT__io_wb_wen_T_DOT_old_DOT_986 = npc_DOT_wbu_DOT__io_wb_wen_T;
    npc_DOT_wbu_DOT__io_wb_wen_T = (npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen & npc_DOT_wbu_io_in_valid_REG);
    bool cond_npc_DOT_wbu_DOT__io_wb_wen_T =
        npc_DOT_wbu_DOT__io_wb_wen_T ^ npc_DOT_wbu_DOT__io_wb_wen_T_DOT_old_DOT_986;
    *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_wbu_DOT__io_wb_wen_T & 0x4010000; // 26 16
    uint8_t npc_DOT_lsu_DOT__T_3_DOT_old_DOT_863 = npc_DOT_lsu_DOT__T_3;
    npc_DOT_lsu_DOT__T_3 = (npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen & npc_DOT_lsu_io_in_valid_REG);
    bool cond_npc_DOT_lsu_DOT__T_3 = npc_DOT_lsu_DOT__T_3 ^ npc_DOT_lsu_DOT__T_3_DOT_old_DOT_863;
    activeFlags[0] |= -(uint8_t)cond_npc_DOT_lsu_DOT__T_3 & 0x80; // 7
    activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT__T_3 & 0x9;  // 8 11
    uint32_t npc_DOT_lsu_DOT_mcycle_DOT_NEXT_DOT_old_DOT_851 = npc_DOT_lsu_DOT_mcycle_DOT_NEXT;
    npc_DOT_lsu_DOT_mcycle_DOT_NEXT = npc_DOT_lsu_DOT__mcycle_T;
    bool cond_npc_DOT_lsu_DOT_mcycle_DOT_NEXT =
        npc_DOT_lsu_DOT_mcycle_DOT_NEXT != npc_DOT_lsu_DOT_mcycle_DOT_NEXT_DOT_old_DOT_851;
    activeFlags[5] |= cond_npc_DOT_lsu_DOT_mcycle_DOT_NEXT; // 40
    uint8_t npc_DOT_lsu_DOT_memFinish_DOT_old_DOT_697 = npc_DOT_lsu_DOT_memFinish;
    npc_DOT_lsu_DOT_memFinish = (npc_DOT_lsu_DOT__memFinish_T != 0);
    bool cond_npc_DOT_lsu_DOT_memFinish = npc_DOT_lsu_DOT_memFinish ^ npc_DOT_lsu_DOT_memFinish_DOT_old_DOT_697;
    *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_lsu_DOT_memFinish & 0x200800; // 21 11
    uint32_t npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1_DOT_old_DOT_63 = npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1;
    npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1 = (npc_DOT_ifu_DOT__io_mem_req_bits_addr_T << 2);
    bool cond_npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1 =
        npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1 != npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1_DOT_old_DOT_63;
    activeFlags[2] |= cond_npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1 << 3; // 19
    npc_DOT_icache_DOT__idx_s0_WIRE_1 = (npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1 & 0x3f);
    uint8_t npc_DOT_icache_DOT__idx_s0_T_2_DOT_old_DOT_1301 = npc_DOT_icache_DOT__idx_s0_T_2;
    npc_DOT_icache_DOT__idx_s0_T_2 = ((npc_DOT_icache_DOT__idx_s0_WIRE_1 >> 4) & 0x3);
    bool cond_npc_DOT_icache_DOT__idx_s0_T_2 =
        npc_DOT_icache_DOT__idx_s0_T_2 != npc_DOT_icache_DOT__idx_s0_T_2_DOT_old_DOT_1301;
    activeFlags[2] |= cond_npc_DOT_icache_DOT__idx_s0_T_2 << 3; // 19
    uint32_t npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT_DOT_old_DOT_1305 =
        npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT;
    npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT = npc_DOT_icache_DOT_tag[npc_DOT_icache_DOT__idx_s0_T_2];
    bool cond_npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT =
        npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT != npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT_DOT_old_DOT_1305;
    *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT & 0x80080000; // 31 19
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_ifu_DOT__io_mem_req_bits_addr_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_ifu_DOT__io_mem_req_bits_addr_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_lsu_DOT__memFinish_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__memFinish_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_lsu_DOT__io_mem_b_ready_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_mem_b_ready_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_lsu_DOT__mcycle_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__mcycle_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_deq_q_DOT__empty_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_deq_q_DOT__empty_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_icache_DOT__io_mem_r_ready_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_r_ready_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_xbar_DOT_acceptWrite: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar_DOT_acceptWrite);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_clint_DOT_incCond_wrap_wrap: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_incCond_wrap_wrap);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_clint_DOT__io_ar_ready_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_ar_ready_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_clint_DOT__io_r_valid_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_r_valid_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_npctrap_io_valid_REG_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_valid_REG_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 mem_DOT_axi4memctrl_DOT__io_axi_ar_ready_T: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_axi_ar_ready_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_valid: ", cycles);
      for (int i0 = 0; i0 < 2; i0++) {
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_valid[i0]);
        printf(" ");
      }
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready: ", cycles);
      for (int i0 = 0; i0 < 2; i0++) {
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[i0]);
        printf(" ");
      }
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_clint_DOT__incCond_wrap_value_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__incCond_wrap_value_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_clint_DOT__cnt_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__cnt_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_clint_DOT_cnt_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_cnt_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_clint_DOT_incCond_c_value: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_incCond_c_value);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_wbu_DOT__io_wb_wen_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_DOT__io_wb_wen_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_lsu_DOT__T_3: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_3);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_lsu_DOT_mcycle_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mcycle_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_lsu_DOT_memFinish: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_memFinish);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_icache_DOT__idx_s0_WIRE_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__idx_s0_WIRE_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_icache_DOT__idx_s0_T_2: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__idx_s0_T_2);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 3 npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[0] & 0x10)) { // id=4
    uint8_t npc_DOT_xbar2_DOT__io_in_ar_ready_T;
    uint8_t npc_DOT_xbar2_DOT__io_in_ar_ready_T_2;
    uint8_t npc_DOT_xbar2_DOT__io_in_r_valid_T;
    uint8_t npc_DOT_xbar2_DOT__io_in_ar_ready_T_1;
    uint8_t npc_DOT_xbar2_DOT__io_in_ar_ready_T_3;
    npc_DOT_xbar2_DOT__io_in_ar_ready_T = (npc_DOT_xbar2_DOT_stateRead == 0x0);
    npc_DOT_xbar2_DOT__io_in_ar_ready_T_2 = (npc_DOT_xbar2_DOT_stateRead == 0x2);
    npc_DOT_xbar2_DOT__io_in_r_valid_T = (npc_DOT_xbar2_DOT_stateRead == 0x1);
    npc_DOT_xbar2_DOT__io_in_ar_ready_T_1 =
        (npc_DOT_xbar2_DOT__io_in_ar_ready_T & npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[1]);
    npc_DOT_xbar2_DOT__io_in_ar_ready_T_3 =
        (npc_DOT_xbar2_DOT__io_in_ar_ready_T_2 &
         npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[npc_DOT_xbar2_DOT_arSelIdx_s1]);
    uint8_t npc_DOT_xbar2_DOT__io_in_r_valid_T_1_DOT_old_DOT_1936 = npc_DOT_xbar2_DOT__io_in_r_valid_T_1;
    npc_DOT_xbar2_DOT__io_in_r_valid_T_1 =
        (npc_DOT_xbar2_DOT__io_in_r_valid_T &
         npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_valid[npc_DOT_xbar2_DOT_arSelIdx_s1]);
    bool cond_npc_DOT_xbar2_DOT__io_in_r_valid_T_1 =
        npc_DOT_xbar2_DOT__io_in_r_valid_T_1 ^ npc_DOT_xbar2_DOT__io_in_r_valid_T_1_DOT_old_DOT_1936;
    activeFlags[3] |= cond_npc_DOT_xbar2_DOT__io_in_r_valid_T_1 << 5; // 29
    npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[0] = 0x0;
    *(uint32_t *)&activeFlags[0] |= 0x40080000; // 30 19
    npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[1] = 0x0;
    *(uint32_t *)&activeFlags[0] |= 0x40080000; // 30 19
    npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[npc_DOT_xbar_DOT_chosenReadIdxReg_s1] =
        npc_DOT_xbar2_DOT__io_in_r_valid_T_1;
    *(uint32_t *)&activeFlags[0] |= 0x40080000; // 30 19
    uint8_t npc_DOT_icache_DOT__resFromMem_T_DOT_old_DOT_1488 = npc_DOT_icache_DOT__resFromMem_T;
    npc_DOT_icache_DOT__resFromMem_T =
        (npc_DOT_icache_DOT__io_mem_r_ready_T & npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[1]);
    bool cond_npc_DOT_icache_DOT__resFromMem_T =
        npc_DOT_icache_DOT__resFromMem_T ^ npc_DOT_icache_DOT__resFromMem_T_DOT_old_DOT_1488;
    *(uint64_t *)&activeFlags[0] |= -(uint64_t)cond_npc_DOT_icache_DOT__resFromMem_T & 0x480020000; // 34 31 17
    uint8_t npc_DOT_xbar2_DOT__io_in_ar_ready_T_4_DOT_old_DOT_1934 = npc_DOT_xbar2_DOT__io_in_ar_ready_T_4;
    npc_DOT_xbar2_DOT__io_in_ar_ready_T_4 =
        (npc_DOT_xbar2_DOT__io_in_ar_ready_T_1 | npc_DOT_xbar2_DOT__io_in_ar_ready_T_3);
    bool cond_npc_DOT_xbar2_DOT__io_in_ar_ready_T_4 =
        npc_DOT_xbar2_DOT__io_in_ar_ready_T_4 ^ npc_DOT_xbar2_DOT__io_in_ar_ready_T_4_DOT_old_DOT_1934;
    *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_xbar2_DOT__io_in_ar_ready_T_4 & 0x30080000; // 29 28 19
    uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT_DOT_old_DOT_2089 =
        npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT;
    npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT = npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;
    bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT =
        npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT ^ npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT_DOT_old_DOT_2089;
    activeFlags[6] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT << 1; // 49
    uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT_DOT_old_DOT_2083 = npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT;
    npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT = npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;
    bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT =
        npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT != npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT_DOT_old_DOT_2083;
    activeFlags[6] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT << 1; // 49
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_wbu_io_in_bits_r_DOT__DOT_res: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_res);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar2_DOT_arSelIdx_s1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSelIdx_s1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar2_DOT__io_in_ar_ready_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_in_ar_ready_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar2_DOT__io_in_ar_ready_T_2: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_in_ar_ready_T_2);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar2_DOT__io_in_r_valid_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_in_r_valid_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar2_DOT__io_in_ar_ready_T_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_in_ar_ready_T_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar2_DOT__io_in_ar_ready_T_3: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_in_ar_ready_T_3);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar2_DOT__io_in_r_valid_T_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_in_r_valid_T_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid: ", cycles);
      for (int i0 = 0; i0 < 2; i0++) {
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[i0]);
        printf(" ");
      }
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_icache_DOT__resFromMem_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__resFromMem_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_xbar2_DOT__io_in_ar_ready_T_4: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_in_ar_ready_T_4);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 4 npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[0] & 0x20)) { // id=5
    uint8_t npc_DOT_npctrap_DOT_valid_DOT_old_DOT_2066 = npc_DOT_npctrap_DOT_valid;
    npc_DOT_npctrap_DOT_valid = npc_DOT_npctrap_io_valid_REG;
    uint8_t npc_DOT_npctrap_DOT_skip_DOT_old_DOT_2073 = npc_DOT_npctrap_DOT_skip;
    npc_DOT_npctrap_DOT_skip = npc_DOT_npctrap_io_REG_DOT__DOT_skip;
    uint32_t npc_DOT_npctrap_DOT_memAddr_DOT_old_DOT_2072 = npc_DOT_npctrap_DOT_memAddr;
    npc_DOT_npctrap_DOT_memAddr = npc_DOT_npctrap_io_REG_DOT__DOT_memAddr;
    uint8_t npc_DOT_npctrap_DOT_isMMIO_DOT_old_DOT_2071 = npc_DOT_npctrap_DOT_isMMIO;
    npc_DOT_npctrap_DOT_isMMIO = npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO;
    uint32_t npc_DOT_npctrap_DOT_code_DOT_old_DOT_2070 = npc_DOT_npctrap_DOT_code;
    npc_DOT_npctrap_DOT_code = npc_DOT_npctrap_io_REG_DOT__DOT_code;
    uint8_t npc_DOT_npctrap_DOT_isEbreak_DOT_old_DOT_2069 = npc_DOT_npctrap_DOT_isEbreak;
    npc_DOT_npctrap_DOT_isEbreak = npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak;
    uint32_t npc_DOT_npctrap_DOT_dnpc_DOT_old_DOT_2068 = npc_DOT_npctrap_DOT_dnpc;
    npc_DOT_npctrap_DOT_dnpc = npc_DOT_npctrap_io_REG_DOT__DOT_dnpc;
    uint32_t npc_DOT_npctrap_DOT_pc_DOT_old_DOT_2067 = npc_DOT_npctrap_DOT_pc;
    npc_DOT_npctrap_DOT_pc = npc_DOT_npctrap_io_REG_DOT__DOT_pc;
    uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT_DOT_old_DOT_2088 =
        npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT;
    npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT = npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr;
    bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT =
        npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT !=
        npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT_DOT_old_DOT_2088;
    activeFlags[6] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT << 2; // 50
    uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT_DOT_old_DOT_2087 =
        npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT;
    npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT = npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO;
    bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT =
        npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT ^
        npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT_DOT_old_DOT_2087;
    activeFlags[6] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT << 2; // 50
    uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT_DOT_old_DOT_2086 =
        npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT;
    npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT = npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;
    bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT =
        npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT != npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT_DOT_old_DOT_2086;
    activeFlags[6] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT << 2; // 50
    uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT_DOT_old_DOT_2085 =
        npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT;
    npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT = npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;
    bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT =
        npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT ^
        npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT_DOT_old_DOT_2085;
    activeFlags[6] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT << 2; // 50
    uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT_DOT_old_DOT_2084 =
        npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT;
    npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT = npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc;
    bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT =
        npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT != npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT_DOT_old_DOT_2084;
    activeFlags[6] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT << 2; // 50
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_pc: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_pc);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_dnpc: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_dnpc);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_code: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_code);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_memAddr: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_memAddr);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_skip: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_skip);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_valid_REG: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_valid_REG);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_DOT_valid: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_DOT_valid);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_DOT_skip: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_DOT_skip);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_DOT_memAddr: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_DOT_memAddr);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_DOT_isMMIO: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_DOT_isMMIO);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_DOT_code: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_DOT_code);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_DOT_isEbreak: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_DOT_isEbreak);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_DOT_dnpc: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_DOT_dnpc);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_DOT_pc: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_DOT_pc);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 5 npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT);
      printf("\n");
    }
#endif
  }
  NPCTrap(npc_DOT_npctrap_DOT_valid, npc_DOT_npctrap_DOT_pc, npc_DOT_npctrap_DOT_dnpc, npc_DOT_npctrap_DOT_isEbreak,
          npc_DOT_npctrap_DOT_code, npc_DOT_npctrap_DOT_isMMIO, npc_DOT_npctrap_DOT_memAddr, npc_DOT_npctrap_DOT_skip);
  if (unlikely(activeFlags[0] & 0x80)) { // id=7
    uint16_t npc_DOT_lsu_DOT__csrAddr_T_DOT_old_DOT_859 = npc_DOT_lsu_DOT__csrAddr_T;
    npc_DOT_lsu_DOT__csrAddr_T = (npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2 & 0xfff);
    bool cond_npc_DOT_lsu_DOT__csrAddr_T = npc_DOT_lsu_DOT__csrAddr_T != npc_DOT_lsu_DOT__csrAddr_T_DOT_old_DOT_859;
    activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT__csrAddr_T & 0x41; // 8 14
    uint8_t npc_DOT_lsu_DOT__T_4_DOT_old_DOT_865 = npc_DOT_lsu_DOT__T_4;
    npc_DOT_lsu_DOT__T_4 = (npc_DOT_lsu_DOT__csrAddr_T == 0x305);
    bool cond_npc_DOT_lsu_DOT__T_4 = npc_DOT_lsu_DOT__T_4 ^ npc_DOT_lsu_DOT__T_4_DOT_old_DOT_865;
    activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT__T_4 & 0x9; // 8 11
    uint8_t npc_DOT_lsu_DOT__T_6_DOT_old_DOT_871 = npc_DOT_lsu_DOT__T_6;
    npc_DOT_lsu_DOT__T_6 = (npc_DOT_lsu_DOT__csrAddr_T == 0x341);
    bool cond_npc_DOT_lsu_DOT__T_6 = npc_DOT_lsu_DOT__T_6 ^ npc_DOT_lsu_DOT__T_6_DOT_old_DOT_871;
    activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT__T_6 & 0x9; // 8 11
    uint8_t npc_DOT_lsu_DOT__T_7_DOT_old_DOT_876 = npc_DOT_lsu_DOT__T_7;
    npc_DOT_lsu_DOT__T_7 = (npc_DOT_lsu_DOT__csrAddr_T == 0x300);
    bool cond_npc_DOT_lsu_DOT__T_7 = npc_DOT_lsu_DOT__T_7 ^ npc_DOT_lsu_DOT__T_7_DOT_old_DOT_876;
    activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT__T_7 & 0x9; // 8 11
    gAssert(!((((npc_DOT_lsu_DOT__T_3 & (npc_DOT_lsu_DOT__T_4 ^ 0x1)) & (npc_DOT_lsu_DOT__T_7 ^ 0x1)) &
               (npc_DOT_lsu_DOT__T_6 ^ 0x1)) &
              npc_DOT_lsu_DOT__T_24),
            "assertion fails");
    uint8_t npc_DOT_lsu_DOT__io_fw_wen_T_DOT_old_DOT_952 = npc_DOT_lsu_DOT__io_fw_wen_T;
    npc_DOT_lsu_DOT__io_fw_wen_T = (npc_DOT_lsu_io_in_valid_REG & npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen);
    bool cond_npc_DOT_lsu_DOT__io_fw_wen_T =
        npc_DOT_lsu_DOT__io_fw_wen_T ^ npc_DOT_lsu_DOT__io_fw_wen_T_DOT_old_DOT_952;
    activeFlags[2] |= cond_npc_DOT_lsu_DOT__io_fw_wen_T; // 16
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 7 npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 7 npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 7 npc_DOT_lsu_DOT__csrAddr_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrAddr_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 7 npc_DOT_lsu_DOT__T_4: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_4);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 7 npc_DOT_lsu_DOT__T_6: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_6);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 7 npc_DOT_lsu_DOT__T_7: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_7);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 7 npc_DOT_lsu_DOT_assert: ", cycles);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 7 npc_DOT_lsu_DOT__io_fw_wen_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_fw_wen_T);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[1] != 0)) {
    uint8_t oldFlag = activeFlags[1];
    activeFlags[1] = 0;
    if (unlikely(oldFlag & 0x1)) { // id=8
      uint8_t npc_DOT_lsu_DOT__T_8 = 0;
      uint8_t npc_DOT_lsu_DOT__T_9 = 0;
      uint8_t npc_DOT_lsu_DOT__T_10 = 0;
      uint8_t npc_DOT_lsu_DOT__T_11 = 0;
      uint8_t npc_DOT_lsu_DOT__T_13 = 0;
      uint8_t npc_DOT_lsu_DOT__T_14 = 0;
      uint8_t npc_DOT_lsu_DOT__T_16 = 0;
      uint8_t npc_DOT_lsu_DOT__T_17 = 0;
      uint8_t npc_DOT_lsu_DOT__T_18 = 0;
      uint8_t npc_DOT_lsu_DOT__T_19 = 0;
      uint8_t npc_DOT_lsu_DOT__T_20 = 0;
      uint8_t npc_DOT_lsu_DOT__T_21 = 0;
      uint8_t npc_DOT_lsu_DOT__T_22 = 0;
      uint32_t npc_DOT_lsu_DOT__mtvec_T = 0;
      uint32_t npc_DOT_lsu_DOT__mtvec_T_1 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0;
      uint8_t npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0;
      npc_DOT_lsu_DOT__T_8 = (npc_DOT_lsu_DOT__csrAddr_T == 0x301);
      npc_DOT_lsu_DOT__T_9 = (npc_DOT_lsu_DOT__csrAddr_T == 0x302);
      npc_DOT_lsu_DOT__T_10 = (npc_DOT_lsu_DOT__csrAddr_T == 0x303);
      npc_DOT_lsu_DOT__T_11 = (npc_DOT_lsu_DOT__csrAddr_T == 0x304);
      npc_DOT_lsu_DOT__T_13 = (npc_DOT_lsu_DOT__csrAddr_T == 0x306);
      npc_DOT_lsu_DOT__T_14 = (npc_DOT_lsu_DOT__csrAddr_T == 0x340);
      npc_DOT_lsu_DOT__T_16 = (npc_DOT_lsu_DOT__csrAddr_T == 0x342);
      npc_DOT_lsu_DOT__T_17 = (npc_DOT_lsu_DOT__csrAddr_T == 0x343);
      npc_DOT_lsu_DOT__T_18 = (npc_DOT_lsu_DOT__csrAddr_T == 0x344);
      npc_DOT_lsu_DOT__T_19 = (npc_DOT_lsu_DOT__csrAddr_T == 0xc00);
      npc_DOT_lsu_DOT__T_20 = (npc_DOT_lsu_DOT__csrAddr_T == 0xf11);
      npc_DOT_lsu_DOT__T_21 = (npc_DOT_lsu_DOT__csrAddr_T == 0xf12);
      npc_DOT_lsu_DOT__T_22 = (npc_DOT_lsu_DOT__csrAddr_T == 0xfff);
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_1_DOT_old_DOT_769 = npc_DOT_lsu_DOT__sbufReq_wmask_T_1;
      npc_DOT_lsu_DOT__sbufReq_wmask_T_1 = (npc_DOT_lsu_io_in_bits_r_DOT__DOT_res & 0x3);
      bool cond_npc_DOT_lsu_DOT__sbufReq_wmask_T_1 =
          npc_DOT_lsu_DOT__sbufReq_wmask_T_1 != npc_DOT_lsu_DOT__sbufReq_wmask_T_1_DOT_old_DOT_769;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__sbufReq_wmask_T_1 & 0x50; // 12 14
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_2_DOT_old_DOT_771 = npc_DOT_lsu_DOT__sbufReq_wmask_T_2;
      npc_DOT_lsu_DOT__sbufReq_wmask_T_2 = ((npc_DOT_lsu_io_in_bits_r_DOT__DOT_res >> 1) & 0x1);
      bool cond_npc_DOT_lsu_DOT__sbufReq_wmask_T_2 =
          npc_DOT_lsu_DOT__sbufReq_wmask_T_2 ^ npc_DOT_lsu_DOT__sbufReq_wmask_T_2_DOT_old_DOT_771;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__sbufReq_wmask_T_2 & 0x50; // 12 14
      if (npc_DOT_lsu_DOT__T_3) {
        if (npc_DOT_lsu_DOT__T_4) {
          npc_DOT_lsu_DOT__mtvec_T = ((npc_DOT_lsu_io_in_bits_r_DOT__DOT_res >> 2) & 0x3fffffff);
          npc_DOT_lsu_DOT__mtvec_T_1 = (npc_DOT_lsu_DOT__mtvec_T << 2);
          uint32_t npc_DOT_lsu_DOT_mtvec_DOT_NEXT_DOT_old_DOT_843 = npc_DOT_lsu_DOT_mtvec_DOT_NEXT;
          npc_DOT_lsu_DOT_mtvec_DOT_NEXT = npc_DOT_lsu_DOT__mtvec_T_1;
          bool cond_npc_DOT_lsu_DOT_mtvec_DOT_NEXT =
              npc_DOT_lsu_DOT_mtvec_DOT_NEXT != npc_DOT_lsu_DOT_mtvec_DOT_NEXT_DOT_old_DOT_843;
          activeFlags[4] |= cond_npc_DOT_lsu_DOT_mtvec_DOT_NEXT << 6; // 38
        } else {
          if (npc_DOT_lsu_DOT__T_7) {
          } else {
            if (npc_DOT_lsu_DOT__T_6) {
            } else {
              if (npc_DOT_lsu_DOT__T_24) {
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x20) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_0 = 0x20;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x20) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_1 = 0x20;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x20) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x6f;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x76;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_2 = 0x20;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x6d) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x75;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x73;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_3 = 0x20;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x73) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x69;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x6e;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x6e;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x61;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_4 = 0x20;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x74) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x64;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x64;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x74;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x72;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x64;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x72;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_5 = 0x20;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x61) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x74;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x61;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x61;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x74;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x20;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x79;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x6f;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_6 = 0x6c;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x74) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x69;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x6c;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x6c;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x76;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x72;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x74;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x75;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x76;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x6d;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x72;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x68;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_7 = 0x61;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x75) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x73;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x69;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x70;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x73;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x61;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x69;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x6c;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x69;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x69;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_8 = 0x73;
                } else {
                }
                npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 =
                    ((-(uint8_t)npc_DOT_lsu_DOT__T_7 & 0x73) | ((-(uint8_t)!npc_DOT_lsu_DOT__T_7) & 0x3f));
                if (npc_DOT_lsu_DOT__T_8) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x61;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_9) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x67;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_10) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x67;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_11) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_4) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_13) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x6e;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_14) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x68;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_6) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x63;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_16) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_17) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x6c;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_18) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x70;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_19) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x65;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_20) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x64;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_21) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x64;
                } else {
                }
                if (npc_DOT_lsu_DOT__T_22) {
                  npc_DOT_lsu_DOT__npcCSRAddrPrintable_9 = 0x74;
                } else {
                }
                gprintf(
                    "Assertion failed: Bad csrAddr = %c%c%c%c%c%c%c%c%c%c\n\n    at LSU.scala:134 .otherwise { "
                    "assert(false.B, p\"Bad csrAddr = _DOT_csrAddr\\n\") }\n",
                    8, npc_DOT_lsu_DOT__npcCSRAddrPrintable_0, 8, npc_DOT_lsu_DOT__npcCSRAddrPrintable_1, 8,
                    npc_DOT_lsu_DOT__npcCSRAddrPrintable_2, 8, npc_DOT_lsu_DOT__npcCSRAddrPrintable_3, 8,
                    npc_DOT_lsu_DOT__npcCSRAddrPrintable_4, 8, npc_DOT_lsu_DOT__npcCSRAddrPrintable_5, 8,
                    npc_DOT_lsu_DOT__npcCSRAddrPrintable_6, 8, npc_DOT_lsu_DOT__npcCSRAddrPrintable_7, 8,
                    npc_DOT_lsu_DOT__npcCSRAddrPrintable_8, 8, npc_DOT_lsu_DOT__npcCSRAddrPrintable_9);
              } else {
              }
            }
          }
        }
      } else {
      }
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_16: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_17: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_17);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_18: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_18);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_19: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_19);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_20: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_20);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_21: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_21);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__T_22: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_22);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_io_in_bits_r_DOT__DOT_res: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_res);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__sbufReq_wmask_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__sbufReq_wmask_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__mtvec_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__mtvec_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__mtvec_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__mtvec_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT_mtvec_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mtvec_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_0: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_0);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT__npcCSRAddrPrintable_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__npcCSRAddrPrintable_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 8 npc_DOT_lsu_DOT_PRINTF_1626: ", cycles);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x2)) { // id=9
      uint8_t npc_DOT_lsu_DOT__sbufWen_T;
      uint8_t npc_DOT_lsu_DOT__io_mem_aw_valid_T;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_4;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_5;
      uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_b_DOT__DOT_ready;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_2;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_3;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_8;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_9;
      uint8_t npc_DOT_xbar_DOT_inputArbWrite_DOT_grant_1;
      uint8_t npc_DOT_xbar_DOT_inputArbWrite_DOT__io_out_valid_T;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T;
      uint8_t npc_DOT_xbar_DOT__chosenWrite_T;
      uint8_t npc_DOT_xbar_DOT__chosenWrite_T_1;
      uint8_t npc_DOT_xbar_DOT_inputArbWrite_DOT_io_DOT__DOT_chosen;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_1;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_6;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_7;
      uint8_t npc_DOT_xbar_DOT__stateWrite_T_10;
      npc_DOT_lsu_DOT__sbufWen_T = (npc_DOT_lsu_DOT_sbufState == 0x0);
      npc_DOT_lsu_DOT__io_mem_aw_valid_T = (npc_DOT_lsu_DOT_sbufState == 0x1);
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_b_DOT__DOT_ready[0] = npc_DOT_lsu_DOT__io_mem_b_ready_T;
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_b_DOT__DOT_ready[1] = 0x0;
      npc_DOT_xbar_DOT__stateWrite_T_4 = (0x0 == npc_DOT_xbar_DOT_stateWrite);
      npc_DOT_xbar_DOT__stateWrite_T_5 = (0x2 == npc_DOT_xbar_DOT_stateWrite);
      npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_b_DOT__DOT_ready =
          npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_b_DOT__DOT_ready[npc_DOT_xbar_DOT_chosenWrite];
      npc_DOT_xbar_DOT__stateWrite_T_2 =
          (npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_b_DOT__DOT_ready & mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T);
      npc_DOT_xbar_DOT__stateWrite_T_3 =
          ((-(uint8_t)npc_DOT_xbar_DOT__stateWrite_T_2 & 0x0) | ((-(uint8_t)!npc_DOT_xbar_DOT__stateWrite_T_2) & 0x2));
      npc_DOT_xbar_DOT__stateWrite_T_8 = ((uint8_t)npc_DOT_xbar_DOT__stateWrite_T_3 & 0x3);
      npc_DOT_xbar_DOT__stateWrite_T_9 =
          ((-(uint8_t)npc_DOT_xbar_DOT__stateWrite_T_5 & npc_DOT_xbar_DOT__stateWrite_T_8) |
           ((-(uint8_t)!npc_DOT_xbar_DOT__stateWrite_T_5) & 0x0));
      uint8_t npc_DOT_lsu_DOT_isValidStore_DOT_old_DOT_671 = npc_DOT_lsu_DOT_isValidStore;
      npc_DOT_lsu_DOT_isValidStore =
          (npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore & npc_DOT_lsu_io_in_valid_REG);
      bool cond_npc_DOT_lsu_DOT_isValidStore =
          npc_DOT_lsu_DOT_isValidStore ^ npc_DOT_lsu_DOT_isValidStore_DOT_old_DOT_671;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT_isValidStore & 0x8c; // 10 11 15
      uint8_t npc_DOT_lsu_DOT_sbufWen_DOT_old_DOT_804 = npc_DOT_lsu_DOT_sbufWen;
      npc_DOT_lsu_DOT_sbufWen = (npc_DOT_lsu_DOT__sbufWen_T & npc_DOT_lsu_DOT_isValidStore);
      bool cond_npc_DOT_lsu_DOT_sbufWen = npc_DOT_lsu_DOT_sbufWen ^ npc_DOT_lsu_DOT_sbufWen_DOT_old_DOT_804;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT_sbufWen & 0x38; // 11 12 13
      uint32_t npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr_DOT_old_DOT_816 = npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr;
      npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr =
          ((-(uint32_t)npc_DOT_lsu_DOT_sbufWen & npc_DOT_lsu_io_in_bits_r_DOT__DOT_res) |
           ((-(uint32_t)!npc_DOT_lsu_DOT_sbufWen) & npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr));
      bool cond_npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr =
          npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr != npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr_DOT_old_DOT_816;
      activeFlags[3] |= cond_npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr << 3; // 27
      uint8_t npc_DOT_lsu_DOT__io_mem_aw_valid_T_1_DOT_old_DOT_840 = npc_DOT_lsu_DOT__io_mem_aw_valid_T_1;
      npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 = (npc_DOT_lsu_DOT_sbufWen | npc_DOT_lsu_DOT__io_mem_aw_valid_T);
      bool cond_npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 =
          npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 ^ npc_DOT_lsu_DOT__io_mem_aw_valid_T_1_DOT_old_DOT_840;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 & 0x14; // 10 12
      activeFlags[3] |= cond_npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 << 3;      // 27
      npc_DOT_xbar_DOT_inputArbWrite_DOT_grant_1 = (npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 == 0x0);
      uint8_t mem_DOT_dmem_DOT_wen_DOT_old_DOT_2265 = mem_DOT_dmem_DOT_wen;
      mem_DOT_dmem_DOT_wen = npc_DOT_lsu_DOT__io_mem_aw_valid_T_1;
      npc_DOT_xbar_DOT_inputArbWrite_DOT__io_out_valid_T = (npc_DOT_xbar_DOT_inputArbWrite_DOT_grant_1 == 0x0);
      npc_DOT_xbar_DOT__stateWrite_T =
          (npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T & npc_DOT_xbar_DOT_inputArbWrite_DOT__io_out_valid_T);
      npc_DOT_xbar_DOT__chosenWrite_T =
          (npc_DOT_xbar_DOT__inputArbWrite_io_out_ready_T & npc_DOT_xbar_DOT_inputArbWrite_DOT__io_out_valid_T);
      npc_DOT_xbar_DOT__chosenWrite_T_1 = (npc_DOT_xbar_DOT_acceptWrite & npc_DOT_xbar_DOT__chosenWrite_T);
      if (npc_DOT_xbar_DOT__chosenWrite_T_1) {
        npc_DOT_xbar_DOT_inputArbWrite_DOT_io_DOT__DOT_chosen = (!npc_DOT_lsu_DOT__io_mem_aw_valid_T_1);
        uint8_t npc_DOT_xbar_DOT_chosenWrite_DOT_old_DOT_1795 = npc_DOT_xbar_DOT_chosenWrite;
        npc_DOT_xbar_DOT_chosenWrite = npc_DOT_xbar_DOT_inputArbWrite_DOT_io_DOT__DOT_chosen;
        bool cond_npc_DOT_xbar_DOT_chosenWrite =
            npc_DOT_xbar_DOT_chosenWrite ^ npc_DOT_xbar_DOT_chosenWrite_DOT_old_DOT_1795;
        activeFlags[1] |= cond_npc_DOT_xbar_DOT_chosenWrite << 1; // 9
      } else {
      }
      npc_DOT_xbar_DOT__stateWrite_T_1 =
          ((-(uint8_t)npc_DOT_xbar_DOT__stateWrite_T & 0x2) | ((-(uint8_t)!npc_DOT_xbar_DOT__stateWrite_T) & 0x0));
      npc_DOT_xbar_DOT__stateWrite_T_6 = ((uint8_t)npc_DOT_xbar_DOT__stateWrite_T_1 & 0x3);
      npc_DOT_xbar_DOT__stateWrite_T_7 =
          ((-(uint8_t)npc_DOT_xbar_DOT__stateWrite_T_4 & npc_DOT_xbar_DOT__stateWrite_T_6) |
           ((-(uint8_t)!npc_DOT_xbar_DOT__stateWrite_T_4) & 0x0));
      npc_DOT_xbar_DOT__stateWrite_T_10 = (npc_DOT_xbar_DOT__stateWrite_T_7 | npc_DOT_xbar_DOT__stateWrite_T_9);
      uint8_t npc_DOT_xbar_DOT_stateWrite_DOT_old_DOT_1776 = npc_DOT_xbar_DOT_stateWrite;
      npc_DOT_xbar_DOT_stateWrite = npc_DOT_xbar_DOT__stateWrite_T_10;
      bool cond_npc_DOT_xbar_DOT_stateWrite =
          npc_DOT_xbar_DOT_stateWrite != npc_DOT_xbar_DOT_stateWrite_DOT_old_DOT_1776;
      *(uint16_t *)&activeFlags[0] |= -(uint16_t)cond_npc_DOT_xbar_DOT_stateWrite & 0x208; // 9 3
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_DOT__sbufWen_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufWen_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_DOT__io_mem_aw_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_mem_aw_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_b_DOT__DOT_ready: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_b_DOT__DOT_ready[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_b_DOT__DOT_ready: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_b_DOT__DOT_ready);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_DOT_isValidStore: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_isValidStore);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_DOT_sbufWen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbufWen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_lsu_DOT__io_mem_aw_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_mem_aw_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT_inputArbWrite_DOT_grant_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_inputArbWrite_DOT_grant_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 mem_DOT_dmem_DOT_wen: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_dmem_DOT_wen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT_inputArbWrite_DOT__io_out_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_inputArbWrite_DOT__io_out_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__chosenWrite_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__chosenWrite_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__chosenWrite_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__chosenWrite_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT_inputArbWrite_DOT_io_DOT__DOT_chosen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_inputArbWrite_DOT_io_DOT__DOT_chosen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT_chosenWrite: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_chosenWrite);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT__stateWrite_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateWrite_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 9 npc_DOT_xbar_DOT_stateWrite: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_stateWrite);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x4)) { // id=10
      uint8_t npc_DOT_lsu_DOT__sbufState_T;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_2;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_3;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_4;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_5;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_6;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_1;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_4;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_5;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_6;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_7;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_8;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_13;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_14;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_11;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_12;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_2;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_9;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_10;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_15;
      uint8_t mem_DOT_axi4memctrl_DOT__state_w_T_16;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_11;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_12;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_9;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_10;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_1;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_7;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_8;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_13;
      uint8_t npc_DOT_lsu_DOT__sbufState_T_14;
      npc_DOT_lsu_DOT__sbufState_T = ((-(uint8_t)mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T & 0x2) |
                                      ((-(uint8_t)!mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T) & 0x1));
      npc_DOT_lsu_DOT__sbufState_T_2 = ((-(uint8_t)mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T & 0x2) |
                                        ((-(uint8_t)!mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T) & 0x1));
      npc_DOT_lsu_DOT__sbufState_T_3 = ((-(uint8_t)mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T & 0x0) |
                                        ((-(uint8_t)!mem_DOT_axi4memctrl_DOT__io_axi_b_valid_T) & 0x2));
      npc_DOT_lsu_DOT__sbufState_T_4 = (0x0 == npc_DOT_lsu_DOT_sbufState);
      npc_DOT_lsu_DOT__sbufState_T_5 = (0x1 == npc_DOT_lsu_DOT_sbufState);
      npc_DOT_lsu_DOT__sbufState_T_6 = (0x2 == npc_DOT_lsu_DOT_sbufState);
      mem_DOT_axi4memctrl_DOT__state_w_T_1 = ((-(uint8_t)npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 & 0x2) |
                                              ((-(uint8_t)!npc_DOT_lsu_DOT__io_mem_aw_valid_T_1) & 0x1));
      mem_DOT_axi4memctrl_DOT__state_w_T_4 = ((-(uint8_t)npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 & 0x2) |
                                              ((-(uint8_t)!npc_DOT_lsu_DOT__io_mem_aw_valid_T_1) & 0x1));
      mem_DOT_axi4memctrl_DOT__state_w_T_5 = ((-(uint8_t)npc_DOT_lsu_DOT__io_mem_b_ready_T & 0x0) |
                                              ((-(uint8_t)!npc_DOT_lsu_DOT__io_mem_b_ready_T) & 0x2));
      mem_DOT_axi4memctrl_DOT__state_w_T_6 = (0x0 == mem_DOT_axi4memctrl_DOT_state_w);
      mem_DOT_axi4memctrl_DOT__state_w_T_7 = (0x1 == mem_DOT_axi4memctrl_DOT_state_w);
      mem_DOT_axi4memctrl_DOT__state_w_T_8 = (0x2 == mem_DOT_axi4memctrl_DOT_state_w);
      mem_DOT_axi4memctrl_DOT__state_w_T_13 = ((uint8_t)mem_DOT_axi4memctrl_DOT__state_w_T_5 & 0x3);
      mem_DOT_axi4memctrl_DOT__state_w_T_14 =
          ((-(uint8_t)mem_DOT_axi4memctrl_DOT__state_w_T_8 & mem_DOT_axi4memctrl_DOT__state_w_T_13) |
           ((-(uint8_t)!mem_DOT_axi4memctrl_DOT__state_w_T_8) & 0x0));
      mem_DOT_axi4memctrl_DOT__state_w_T_11 = ((uint8_t)mem_DOT_axi4memctrl_DOT__state_w_T_4 & 0x3);
      mem_DOT_axi4memctrl_DOT__state_w_T_12 =
          ((-(uint8_t)mem_DOT_axi4memctrl_DOT__state_w_T_7 & mem_DOT_axi4memctrl_DOT__state_w_T_11) |
           ((-(uint8_t)!mem_DOT_axi4memctrl_DOT__state_w_T_7) & 0x0));
      mem_DOT_axi4memctrl_DOT__state_w_T_2 =
          ((-(uint8_t)npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 & mem_DOT_axi4memctrl_DOT__state_w_T_1) |
           ((-(uint8_t)!npc_DOT_lsu_DOT__io_mem_aw_valid_T_1) & 0x0));
      mem_DOT_axi4memctrl_DOT__state_w_T_9 = ((uint8_t)mem_DOT_axi4memctrl_DOT__state_w_T_2 & 0x3);
      mem_DOT_axi4memctrl_DOT__state_w_T_10 =
          ((-(uint8_t)mem_DOT_axi4memctrl_DOT__state_w_T_6 & mem_DOT_axi4memctrl_DOT__state_w_T_9) |
           ((-(uint8_t)!mem_DOT_axi4memctrl_DOT__state_w_T_6) & 0x0));
      mem_DOT_axi4memctrl_DOT__state_w_T_15 =
          (mem_DOT_axi4memctrl_DOT__state_w_T_10 | mem_DOT_axi4memctrl_DOT__state_w_T_12);
      mem_DOT_axi4memctrl_DOT__state_w_T_16 =
          (mem_DOT_axi4memctrl_DOT__state_w_T_15 | mem_DOT_axi4memctrl_DOT__state_w_T_14);
      uint8_t mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT_DOT_old_DOT_2226 = mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT;
      mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT = mem_DOT_axi4memctrl_DOT__state_w_T_16;
      bool cond_mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT =
          mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT != mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT_DOT_old_DOT_2226;
      activeFlags[6] |= cond_mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT << 3; // 51
      npc_DOT_lsu_DOT__sbufState_T_11 = ((uint8_t)npc_DOT_lsu_DOT__sbufState_T_3 & 0x3);
      npc_DOT_lsu_DOT__sbufState_T_12 = ((-(uint8_t)npc_DOT_lsu_DOT__sbufState_T_6 & npc_DOT_lsu_DOT__sbufState_T_11) |
                                         ((-(uint8_t)!npc_DOT_lsu_DOT__sbufState_T_6) & 0x0));
      npc_DOT_lsu_DOT__sbufState_T_9 = ((uint8_t)npc_DOT_lsu_DOT__sbufState_T_2 & 0x3);
      npc_DOT_lsu_DOT__sbufState_T_10 = ((-(uint8_t)npc_DOT_lsu_DOT__sbufState_T_5 & npc_DOT_lsu_DOT__sbufState_T_9) |
                                         ((-(uint8_t)!npc_DOT_lsu_DOT__sbufState_T_5) & 0x0));
      npc_DOT_lsu_DOT__sbufState_T_1 = ((-(uint8_t)npc_DOT_lsu_DOT_isValidStore & npc_DOT_lsu_DOT__sbufState_T) |
                                        ((-(uint8_t)!npc_DOT_lsu_DOT_isValidStore) & 0x0));
      npc_DOT_lsu_DOT__sbufState_T_7 = ((uint8_t)npc_DOT_lsu_DOT__sbufState_T_1 & 0x3);
      npc_DOT_lsu_DOT__sbufState_T_8 = ((-(uint8_t)npc_DOT_lsu_DOT__sbufState_T_4 & npc_DOT_lsu_DOT__sbufState_T_7) |
                                        ((-(uint8_t)!npc_DOT_lsu_DOT__sbufState_T_4) & 0x0));
      npc_DOT_lsu_DOT__sbufState_T_13 = (npc_DOT_lsu_DOT__sbufState_T_8 | npc_DOT_lsu_DOT__sbufState_T_10);
      npc_DOT_lsu_DOT__sbufState_T_14 = (npc_DOT_lsu_DOT__sbufState_T_13 | npc_DOT_lsu_DOT__sbufState_T_12);
      uint8_t npc_DOT_lsu_DOT_sbufState_DOT_old_DOT_758 = npc_DOT_lsu_DOT_sbufState;
      npc_DOT_lsu_DOT_sbufState = npc_DOT_lsu_DOT__sbufState_T_14;
      bool cond_npc_DOT_lsu_DOT_sbufState = npc_DOT_lsu_DOT_sbufState != npc_DOT_lsu_DOT_sbufState_DOT_old_DOT_758;
      *(uint16_t *)&activeFlags[0] |= -(uint16_t)cond_npc_DOT_lsu_DOT_sbufState & 0x608; // 10 9 3
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_1: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_4: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_5: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_6: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_7: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_8: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_13: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_14: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_11: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_12: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_2: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_9: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_10: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_15: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT__state_w_T_16: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_w_T_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT__sbufState_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufState_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 10 npc_DOT_lsu_DOT_sbufState: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbufState);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x8)) { // id=11
      uint8_t npc_DOT_lsu_DOT__io_mem_ar_valid_T = 0;
      uint8_t npc_DOT__wbu_io_in_valid_T_2 = 0;
      uint8_t npc_DOT_lsu_DOT__T_26 = 0;
      uint8_t npc_DOT_lsu_DOT__io_redirect_valid_T = 0;
      uint8_t npc_DOT_lsu_DOT__io_redirect_valid_T_1 = 0;
      uint32_t npc_DOT_lsu_DOT__mepc_T = 0;
      uint8_t npc_DOT_lsu_DOT__mcause_T = 0;
      uint32_t npc_DOT_lsu_DOT__mepc_T_1 = 0;
      uint8_t npc_DOT_lsu_DOT__io_out_valid_T = 0;
      uint8_t npc_DOT_lsu_DOT__io_out_valid_T_1 = 0;
      uint8_t npc_DOT__lsu_io_in_valid_T_2 = 0;
      uint8_t npc_DOT__wbu_io_in_valid_T_3 = 0;
      uint8_t npc_DOT_lsu_DOT__io_in_ready_T = 0;
      uint8_t npc_DOT__lsu_io_in_valid_T_3 = 0;
      uint8_t npc_DOT__lsu_io_in_valid_T_4 = 0;
      npc_DOT_lsu_DOT__io_mem_ar_valid_T = (npc_DOT_lsu_DOT_state == 0x0);
      npc_DOT__wbu_io_in_valid_T_2 = ((!npc_DOT_wbu_io_in_valid_REG) & npc_DOT_wbu_io_in_valid_REG);
      uint8_t npc_DOT_lsu_DOT_raiseException_DOT_old_DOT_858 = npc_DOT_lsu_DOT_raiseException;
      npc_DOT_lsu_DOT_raiseException = (npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal |
                                        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall);
      bool cond_npc_DOT_lsu_DOT_raiseException =
          npc_DOT_lsu_DOT_raiseException ^ npc_DOT_lsu_DOT_raiseException_DOT_old_DOT_858;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT_raiseException & 0x20; // 13
      npc_DOT_lsu_DOT__T_26 = (npc_DOT_lsu_DOT_raiseException & npc_DOT_lsu_io_in_valid_REG);
      npc_DOT_lsu_DOT__io_redirect_valid_T =
          (npc_DOT_lsu_DOT_raiseException | npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret);
      npc_DOT_lsu_DOT__io_redirect_valid_T_1 =
          (npc_DOT_lsu_DOT__io_redirect_valid_T | npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect);
      uint8_t npc_DOT_lsu_DOT__io_redirect_valid_T_2_DOT_old_DOT_951 = npc_DOT_lsu_DOT__io_redirect_valid_T_2;
      npc_DOT_lsu_DOT__io_redirect_valid_T_2 = (npc_DOT_lsu_DOT__io_redirect_valid_T_1 & npc_DOT_lsu_io_in_valid_REG);
      bool cond_npc_DOT_lsu_DOT__io_redirect_valid_T_2 =
          npc_DOT_lsu_DOT__io_redirect_valid_T_2 ^ npc_DOT_lsu_DOT__io_redirect_valid_T_2_DOT_old_DOT_951;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__io_redirect_valid_T_2 & 0x90;        // 12 15
      activeFlags[2] |= -(uint8_t)cond_npc_DOT_lsu_DOT__io_redirect_valid_T_2 & 0x50; // 20 22
      if (npc_DOT_lsu_DOT__T_26) {
        npc_DOT_lsu_DOT__mcause_T = ((-(uint8_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall & 0xb) |
                                     ((-(uint8_t)!npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall) & 0x2));
        uint32_t npc_DOT_lsu_DOT_mcause_DOT_NEXT_DOT_old_DOT_845 = npc_DOT_lsu_DOT_mcause_DOT_NEXT;
        npc_DOT_lsu_DOT_mcause_DOT_NEXT = ((uint32_t)npc_DOT_lsu_DOT__mcause_T);
        bool cond_npc_DOT_lsu_DOT_mcause_DOT_NEXT =
            npc_DOT_lsu_DOT_mcause_DOT_NEXT != npc_DOT_lsu_DOT_mcause_DOT_NEXT_DOT_old_DOT_845;
        activeFlags[4] |= cond_npc_DOT_lsu_DOT_mcause_DOT_NEXT << 7; // 39
        uint32_t npc_DOT_lsu_DOT_mepc_DOT_NEXT_DOT_old_DOT_849 = npc_DOT_lsu_DOT_mepc_DOT_NEXT;
        npc_DOT_lsu_DOT_mepc_DOT_NEXT = npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2;
        bool cond_npc_DOT_lsu_DOT_mepc_DOT_NEXT =
            npc_DOT_lsu_DOT_mepc_DOT_NEXT != npc_DOT_lsu_DOT_mepc_DOT_NEXT_DOT_old_DOT_849;
        activeFlags[4] |= cond_npc_DOT_lsu_DOT_mepc_DOT_NEXT << 7; // 39
      } else {
        if (npc_DOT_lsu_DOT__T_3) {
          if (npc_DOT_lsu_DOT__T_4) {
          } else {
            if (npc_DOT_lsu_DOT__T_7) {
            } else {
              if (npc_DOT_lsu_DOT__T_6) {
                npc_DOT_lsu_DOT__mepc_T = ((npc_DOT_lsu_io_in_bits_r_DOT__DOT_res >> 2) & 0x3fffffff);
                npc_DOT_lsu_DOT__mepc_T_1 = (npc_DOT_lsu_DOT__mepc_T << 2);
                uint32_t npc_DOT_lsu_DOT_mepc_DOT_NEXT_DOT_old_DOT_849 = npc_DOT_lsu_DOT_mepc_DOT_NEXT;
                npc_DOT_lsu_DOT_mepc_DOT_NEXT = npc_DOT_lsu_DOT__mepc_T_1;
                bool cond_npc_DOT_lsu_DOT_mepc_DOT_NEXT =
                    npc_DOT_lsu_DOT_mepc_DOT_NEXT != npc_DOT_lsu_DOT_mepc_DOT_NEXT_DOT_old_DOT_849;
                activeFlags[4] |= cond_npc_DOT_lsu_DOT_mepc_DOT_NEXT << 7; // 39
              } else {
              }
            }
          }
        } else {
        }
      }
      uint8_t npc_DOT_lsu_DOT_isValidLoad_DOT_old_DOT_670 = npc_DOT_lsu_DOT_isValidLoad;
      npc_DOT_lsu_DOT_isValidLoad =
          (npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad & npc_DOT_lsu_io_in_valid_REG);
      bool cond_npc_DOT_lsu_DOT_isValidLoad = npc_DOT_lsu_DOT_isValidLoad ^ npc_DOT_lsu_DOT_isValidLoad_DOT_old_DOT_670;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT_isValidLoad & 0x80; // 15
      activeFlags[2] |= cond_npc_DOT_lsu_DOT_isValidLoad << 3;      // 19
      npc_DOT_lsu_DOT__io_out_valid_T =
          ((!npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad) | npc_DOT_lsu_DOT_memFinish);
      npc_DOT_lsu_DOT__io_out_valid_T_1 =
          ((npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore & npc_DOT_lsu_DOT_sbufWen) |
           ((!npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore) & npc_DOT_lsu_DOT__io_out_valid_T));
      uint8_t npc_DOT_lsu_DOT__io_out_valid_T_2_DOT_old_DOT_965 = npc_DOT_lsu_DOT__io_out_valid_T_2;
      npc_DOT_lsu_DOT__io_out_valid_T_2 = (npc_DOT_lsu_DOT__io_out_valid_T_1 & npc_DOT_lsu_io_in_valid_REG);
      bool cond_npc_DOT_lsu_DOT__io_out_valid_T_2 =
          npc_DOT_lsu_DOT__io_out_valid_T_2 ^ npc_DOT_lsu_DOT__io_out_valid_T_2_DOT_old_DOT_965;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__io_out_valid_T_2 & 0x80; // 15
      npc_DOT__lsu_io_in_valid_T_2 = ((!npc_DOT_lsu_DOT__io_out_valid_T_2) & npc_DOT_lsu_io_in_valid_REG);
      npc_DOT__wbu_io_in_valid_T_3 = (npc_DOT_lsu_DOT__io_out_valid_T_2 | npc_DOT__wbu_io_in_valid_T_2);
      uint8_t npc_DOT_wbu_io_in_valid_REG_DOT_old_DOT_1205 = npc_DOT_wbu_io_in_valid_REG;
      npc_DOT_wbu_io_in_valid_REG = npc_DOT__wbu_io_in_valid_T_3;
      bool cond_npc_DOT_wbu_io_in_valid_REG =
          npc_DOT_wbu_io_in_valid_REG ^ npc_DOT_wbu_io_in_valid_REG_DOT_old_DOT_1205;
      *(uint16_t *)&activeFlags[0] |= -(uint16_t)cond_npc_DOT_wbu_io_in_valid_REG & 0x808; // 11 3
      npc_DOT_lsu_DOT__io_in_ready_T = ((!npc_DOT_lsu_DOT_isValidLoad) | npc_DOT_lsu_DOT_memFinish);
      uint8_t npc_DOT_lsu_DOT__io_in_ready_T_1_DOT_old_DOT_961 = npc_DOT_lsu_DOT__io_in_ready_T_1;
      npc_DOT_lsu_DOT__io_in_ready_T_1 = ((npc_DOT_lsu_DOT_isValidStore & npc_DOT_lsu_DOT_sbufWen) |
                                          ((!npc_DOT_lsu_DOT_isValidStore) & npc_DOT_lsu_DOT__io_in_ready_T));
      bool cond_npc_DOT_lsu_DOT__io_in_ready_T_1 =
          npc_DOT_lsu_DOT__io_in_ready_T_1 ^ npc_DOT_lsu_DOT__io_in_ready_T_1_DOT_old_DOT_961;
      activeFlags[2] |= cond_npc_DOT_lsu_DOT__io_in_ready_T_1 << 6; // 22
      uint8_t npc_DOT__lsu_io_in_valid_T_DOT_old_DOT_1168 = npc_DOT__lsu_io_in_valid_T;
      npc_DOT__lsu_io_in_valid_T = (npc_DOT_exu_io_in_valid_REG & npc_DOT_lsu_DOT__io_in_ready_T_1);
      bool cond_npc_DOT__lsu_io_in_valid_T = npc_DOT__lsu_io_in_valid_T ^ npc_DOT__lsu_io_in_valid_T_DOT_old_DOT_1168;
      activeFlags[3] |= cond_npc_DOT__lsu_io_in_valid_T << 1; // 25
      npc_DOT__lsu_io_in_valid_T_3 = (npc_DOT__lsu_io_in_valid_T | npc_DOT__lsu_io_in_valid_T_2);
      npc_DOT__lsu_io_in_valid_T_4 = ((!npc_DOT_lsu_DOT__io_redirect_valid_T_2) & npc_DOT__lsu_io_in_valid_T_3);
      uint8_t npc_DOT_lsu_io_in_valid_REG_DOT_old_DOT_1174 = npc_DOT_lsu_io_in_valid_REG;
      npc_DOT_lsu_io_in_valid_REG = npc_DOT__lsu_io_in_valid_T_4;
      bool cond_npc_DOT_lsu_io_in_valid_REG =
          npc_DOT_lsu_io_in_valid_REG ^ npc_DOT_lsu_io_in_valid_REG_DOT_old_DOT_1174;
      *(uint16_t *)&activeFlags[0] |= -(uint16_t)cond_npc_DOT_lsu_io_in_valid_REG & 0xa88; // 11 9 3 7
      uint8_t npc_DOT_lsu_DOT__io_mem_ar_valid_T_1_DOT_old_DOT_692 = npc_DOT_lsu_DOT__io_mem_ar_valid_T_1;
      npc_DOT_lsu_DOT__io_mem_ar_valid_T_1 = (npc_DOT_lsu_DOT__io_mem_ar_valid_T & npc_DOT_lsu_DOT_isValidLoad);
      bool cond_npc_DOT_lsu_DOT__io_mem_ar_valid_T_1 =
          npc_DOT_lsu_DOT__io_mem_ar_valid_T_1 ^ npc_DOT_lsu_DOT__io_mem_ar_valid_T_1_DOT_old_DOT_692;
      activeFlags[2] |= cond_npc_DOT_lsu_DOT__io_mem_ar_valid_T_1 << 1; // 17
      uint8_t npc_DOT_xbar_DOT_chosenReadIdx_DOT_old_DOT_1710 = npc_DOT_xbar_DOT_chosenReadIdx;
      npc_DOT_xbar_DOT_chosenReadIdx = (!npc_DOT_lsu_DOT__io_mem_ar_valid_T_1);
      bool cond_npc_DOT_xbar_DOT_chosenReadIdx =
          npc_DOT_xbar_DOT_chosenReadIdx ^ npc_DOT_xbar_DOT_chosenReadIdx_DOT_old_DOT_1710;
      activeFlags[2] |= cond_npc_DOT_xbar_DOT_chosenReadIdx << 2; // 18
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_mem_ar_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_mem_ar_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT__wbu_io_in_valid_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__wbu_io_in_valid_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT_raiseException: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_raiseException);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__T_26: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T_26);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_redirect_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_redirect_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_redirect_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_redirect_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_redirect_valid_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_redirect_valid_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__mepc_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__mepc_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__mcause_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__mcause_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT_mcause_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mcause_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__mepc_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__mepc_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT_mepc_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mepc_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT_isValidLoad: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_isValidLoad);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_out_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_out_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_out_valid_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_valid_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT__lsu_io_in_valid_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__lsu_io_in_valid_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT__wbu_io_in_valid_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__wbu_io_in_valid_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_wbu_io_in_valid_REG: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_valid_REG);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_in_ready_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_in_ready_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_in_ready_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_in_ready_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT__lsu_io_in_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__lsu_io_in_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT__lsu_io_in_valid_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__lsu_io_in_valid_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT__lsu_io_in_valid_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__lsu_io_in_valid_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_io_in_valid_REG: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_valid_REG);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_lsu_DOT__io_mem_ar_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_mem_ar_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 11 npc_DOT_xbar_DOT_chosenReadIdx: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_chosenReadIdx);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x10)) { // id=12
      uint8_t npc_DOT_icache_DOT__needFlushReg_T = 0;
      uint8_t npc_DOT_icache_DOT__needFlushReg_T_1 = 0;
      uint8_t npc_DOT_icache_DOT__reqValid_T = 0;
      uint8_t npc_DOT_icache_DOT__needFlushReg_T_2 = 0;
      uint8_t npc_DOT_icache_DOT__needFlushReg_T_3 = 0;
      uint8_t npc_DOT_icache_DOT_needFlushReg = 0;
      uint8_t npc_DOT_icache_DOT__T_1 = 0;
      uint8_t npc_DOT_icache_DOT__T = 0;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_3 = 0;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_4 = 0;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_5 = 0;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_8 = 0;
      uint8_t npc_DOT_lsu_DOT_sbuf_DOT__DOT_size = 0;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_7 = 0;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_6 = 0;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_9 = 0;
      uint8_t npc_DOT_lsu_DOT_sbuf_DOT__DOT_wmask = 0;
      npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[0] = 0x1;
      npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[1] = 0x2;
      npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[2] = 0x4;
      npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[3] = 0x8;
      npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_3[0] = 0x3;
      npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_3[1] = 0xc;
      npc_DOT_icache_DOT__needFlushReg_T = (npc_DOT_icache_DOT_state == 0x0);
      npc_DOT_icache_DOT__needFlushReg_T_1 = (npc_DOT_icache_DOT_state == 0x1);
      npc_DOT_icache_DOT__reqValid_T = (npc_DOT_lsu_DOT__io_redirect_valid_T_2 == 0x0);
      uint8_t npc_DOT_icache_DOT_reqValid_DOT_old_DOT_1416 = npc_DOT_icache_DOT_reqValid;
      npc_DOT_icache_DOT_reqValid = (npc_DOT_icache_DOT_s1_in_valid_REG & npc_DOT_icache_DOT__reqValid_T);
      bool cond_npc_DOT_icache_DOT_reqValid =
          npc_DOT_icache_DOT_reqValid ^ npc_DOT_icache_DOT_reqValid_DOT_old_DOT_1416;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_reqValid & 0x40020000; // 30 17
      npc_DOT_icache_DOT__needFlushReg_T_2 =
          ((npc_DOT_icache_DOT__needFlushReg_T_1 << 1) | (uint8_t)npc_DOT_icache_DOT__needFlushReg_T);
      npc_DOT_icache_DOT__needFlushReg_T_3 = (npc_DOT_icache_DOT__needFlushReg_T_2 != 0);
      npc_DOT_icache_DOT_needFlushReg = (npc_DOT_icache_DOT__needFlushReg_T_3 == 0x0);
      npc_DOT_icache_DOT__T_1 = (npc_DOT_lsu_DOT__io_redirect_valid_T_2 & npc_DOT_icache_DOT_needFlushReg);
      if (npc_DOT_icache_DOT__T_1) {
        uint8_t npc_DOT_icache_DOT_flushReg_DOT_NEXT_DOT_old_DOT_1404 = npc_DOT_icache_DOT_flushReg_DOT_NEXT;
        npc_DOT_icache_DOT_flushReg_DOT_NEXT = 0x1;
        bool cond_npc_DOT_icache_DOT_flushReg_DOT_NEXT =
            npc_DOT_icache_DOT_flushReg_DOT_NEXT ^ npc_DOT_icache_DOT_flushReg_DOT_NEXT_DOT_old_DOT_1404;
        activeFlags[5] |= cond_npc_DOT_icache_DOT_flushReg_DOT_NEXT << 6; // 46
      } else {
        npc_DOT_icache_DOT__T = (npc_DOT_icache_DOT_state == 0x1);
        if (npc_DOT_icache_DOT__T) {
          uint8_t npc_DOT_icache_DOT_flushReg_DOT_NEXT_DOT_old_DOT_1404 = npc_DOT_icache_DOT_flushReg_DOT_NEXT;
          npc_DOT_icache_DOT_flushReg_DOT_NEXT = 0x0;
          bool cond_npc_DOT_icache_DOT_flushReg_DOT_NEXT =
              npc_DOT_icache_DOT_flushReg_DOT_NEXT ^ npc_DOT_icache_DOT_flushReg_DOT_NEXT_DOT_old_DOT_1404;
          activeFlags[5] |= cond_npc_DOT_icache_DOT_flushReg_DOT_NEXT << 6; // 46
        } else {
        }
      }
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_DOT_old_DOT_765 = npc_DOT_lsu_DOT__sbufReq_wmask_T;
      npc_DOT_lsu_DOT__sbufReq_wmask_T = (npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 & 0x3);
      bool cond_npc_DOT_lsu_DOT__sbufReq_wmask_T =
          npc_DOT_lsu_DOT__sbufReq_wmask_T != npc_DOT_lsu_DOT__sbufReq_wmask_T_DOT_old_DOT_765;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__sbufReq_wmask_T & 0x60; // 13 14
      activeFlags[2] |= cond_npc_DOT_lsu_DOT__sbufReq_wmask_T << 2;      // 18
      npc_DOT_lsu_DOT__sbufReq_wmask_T_3 = (0x0 == npc_DOT_lsu_DOT__sbufReq_wmask_T);
      npc_DOT_lsu_DOT__sbufReq_wmask_T_4 = (0x1 == npc_DOT_lsu_DOT__sbufReq_wmask_T);
      npc_DOT_lsu_DOT__sbufReq_wmask_T_5 = (0x2 == npc_DOT_lsu_DOT__sbufReq_wmask_T);
      npc_DOT_lsu_DOT__sbufReq_wmask_T_8 = ((-(uint8_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_5 & 0xf) |
                                            ((-(uint8_t)!npc_DOT_lsu_DOT__sbufReq_wmask_T_5) & 0x0));
      npc_DOT_lsu_DOT_sbuf_DOT__DOT_size =
          ((-(uint8_t)npc_DOT_lsu_DOT_sbufWen & npc_DOT_lsu_DOT__sbufReq_wmask_T) |
           ((-(uint8_t)!npc_DOT_lsu_DOT_sbufWen) & npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size));
      uint8_t npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size_DOT_old_DOT_650 =
          npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size;
      npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size = npc_DOT_lsu_DOT_sbuf_DOT__DOT_size;
      bool cond_npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size =
          npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size !=
          npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size_DOT_old_DOT_650;
      activeFlags[3] |= cond_npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size << 3; // 27
      if (npc_DOT_lsu_DOT__io_mem_aw_valid_T_1) {
        uint8_t mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT_DOT_old_DOT_2205 =
            mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT;
        mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT =
            npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size;
        bool cond_mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT =
            mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT != mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT_DOT_old_DOT_2205;
        activeFlags[5] |= cond_mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT << 6; // 46
      } else {
      }
      npc_DOT_lsu_DOT__sbufReq_wmask_T_7 =
          ((-(uint8_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_4 &
            npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_3[npc_DOT_lsu_DOT__sbufReq_wmask_T_2]) |
           ((-(uint8_t)!npc_DOT_lsu_DOT__sbufReq_wmask_T_4) & 0x0));
      npc_DOT_lsu_DOT__sbufReq_wmask_T_6 =
          ((-(uint8_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_3 &
            npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[npc_DOT_lsu_DOT__sbufReq_wmask_T_1]) |
           ((-(uint8_t)!npc_DOT_lsu_DOT__sbufReq_wmask_T_3) & 0x0));
      npc_DOT_lsu_DOT__sbufReq_wmask_T_9 = (npc_DOT_lsu_DOT__sbufReq_wmask_T_6 | npc_DOT_lsu_DOT__sbufReq_wmask_T_7);
      uint8_t npc_DOT_lsu_DOT__sbufReq_wmask_T_10_DOT_old_DOT_780 = npc_DOT_lsu_DOT__sbufReq_wmask_T_10;
      npc_DOT_lsu_DOT__sbufReq_wmask_T_10 = (npc_DOT_lsu_DOT__sbufReq_wmask_T_9 | npc_DOT_lsu_DOT__sbufReq_wmask_T_8);
      bool cond_npc_DOT_lsu_DOT__sbufReq_wmask_T_10 =
          npc_DOT_lsu_DOT__sbufReq_wmask_T_10 != npc_DOT_lsu_DOT__sbufReq_wmask_T_10_DOT_old_DOT_780;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__sbufReq_wmask_T_10 & 0x20; // 13
      npc_DOT_lsu_DOT_sbuf_DOT__DOT_wmask =
          ((-(uint8_t)npc_DOT_lsu_DOT_sbufWen & npc_DOT_lsu_DOT__sbufReq_wmask_T_10) |
           ((-(uint8_t)!npc_DOT_lsu_DOT_sbufWen) & npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask));
      uint8_t mem_DOT_dmem_DOT_wmask_DOT_old_DOT_2268 = mem_DOT_dmem_DOT_wmask;
      mem_DOT_dmem_DOT_wmask = npc_DOT_lsu_DOT_sbuf_DOT__DOT_wmask;
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2: ", cycles);
        for (int i0 = 0; i0 < 4; i0++) {
          printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_2[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_3: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_WIRE_3[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT__needFlushReg_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__needFlushReg_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT__needFlushReg_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__needFlushReg_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT__reqValid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__reqValid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT_reqValid: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_reqValid);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT__needFlushReg_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__needFlushReg_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT__needFlushReg_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__needFlushReg_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT_needFlushReg: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_needFlushReg);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT__T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT__T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_icache_DOT_flushReg_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_flushReg_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT_sbuf_DOT__DOT_size: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_DOT__DOT_size);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT__sbufReq_wmask_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wmask_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 npc_DOT_lsu_DOT_sbuf_DOT__DOT_wmask: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_DOT__DOT_wmask);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 12 mem_DOT_dmem_DOT_wmask: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_dmem_DOT_wmask);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x20)) { // id=13
      uint8_t npc_DOT_lsu_DOT__sbufReq_wdata_T_1;
      uint16_t npc_DOT_lsu_DOT__sbufReq_wdata_T_5;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wdata_T_10;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wdata_T_11;
      uint8_t npc_DOT_lsu_DOT__sbufReq_wdata_T_12;
      uint32_t npc_DOT_lsu_DOT__dnpc_T;
      uint32_t npc_DOT_lsu_DOT_dnpc;
      uint32_t npc_DOT_lsu_DOT__io_redirect_dnpc_T;
      uint32_t npc_DOT_lsu_DOT__sbufReq_wdata_T_15;
      uint32_t npc_DOT_lsu_DOT__sbufReq_wdata_T_6;
      uint32_t npc_DOT_lsu_DOT__sbufReq_wdata_T_14;
      uint16_t npc_DOT_lsu_DOT__sbufReq_wdata_T_2;
      uint32_t npc_DOT_lsu_DOT__sbufReq_wdata_T_3;
      uint32_t npc_DOT_lsu_DOT__sbufReq_wdata_T_13;
      uint32_t npc_DOT_lsu_DOT__sbufReq_wdata_T_16;
      uint32_t npc_DOT_lsu_DOT__sbufReq_wdata_T_17;
      uint32_t npc_DOT_lsu_DOT_sbuf_DOT__DOT_wdata;
      npc_DOT_lsu_DOT__sbufReq_wdata_T_1 = (npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2 & 0xff);
      npc_DOT_lsu_DOT__sbufReq_wdata_T_5 = (npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2 & 0xffff);
      npc_DOT_lsu_DOT__sbufReq_wdata_T_10 = (0x0 == npc_DOT_lsu_DOT__sbufReq_wmask_T);
      npc_DOT_lsu_DOT__sbufReq_wdata_T_11 = (0x1 == npc_DOT_lsu_DOT__sbufReq_wmask_T);
      npc_DOT_lsu_DOT__sbufReq_wdata_T_12 = (0x2 == npc_DOT_lsu_DOT__sbufReq_wmask_T);
      if (npc_DOT_lsu_DOT_sbufWen) {
        uint32_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr_DOT_old_DOT_810 = npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr;
        npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr = npc_DOT_lsu_io_in_bits_r_DOT__DOT_res;
        bool cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr =
            npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr != npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr_DOT_old_DOT_810;
        activeFlags[1] |= cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr << 1; // 9
        uint8_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size_DOT_old_DOT_811 = npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size;
        npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size = npc_DOT_lsu_DOT__sbufReq_wmask_T;
        bool cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size =
            npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size != npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size_DOT_old_DOT_811;
        activeFlags[1] |= cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size << 4; // 12
        uint8_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask_DOT_old_DOT_814 = npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask;
        npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask = npc_DOT_lsu_DOT__sbufReq_wmask_T_10;
        bool cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask =
            npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask != npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask_DOT_old_DOT_814;
        activeFlags[1] |= cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask << 4; // 12
      } else {
      }
      npc_DOT_lsu_DOT__dnpc_T =
          ((-(uint32_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret & npc_DOT_lsu_DOT_mepc) |
           ((-(uint32_t)!npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret) &
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2));
      npc_DOT_lsu_DOT_dnpc = ((-(uint32_t)npc_DOT_lsu_DOT_raiseException & npc_DOT_lsu_DOT_mtvec) |
                              ((-(uint32_t)!npc_DOT_lsu_DOT_raiseException) & npc_DOT_lsu_DOT__dnpc_T));
      npc_DOT_lsu_DOT__io_redirect_dnpc_T = ((npc_DOT_lsu_DOT_dnpc >> 2) & 0x3fffffff);
      uint32_t npc_DOT_lsu_DOT__io_redirect_dnpc_T_1_DOT_old_DOT_948 = npc_DOT_lsu_DOT__io_redirect_dnpc_T_1;
      npc_DOT_lsu_DOT__io_redirect_dnpc_T_1 = (npc_DOT_lsu_DOT__io_redirect_dnpc_T << 2);
      bool cond_npc_DOT_lsu_DOT__io_redirect_dnpc_T_1 =
          npc_DOT_lsu_DOT__io_redirect_dnpc_T_1 != npc_DOT_lsu_DOT__io_redirect_dnpc_T_1_DOT_old_DOT_948;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__io_redirect_dnpc_T_1 & 0x80; // 15
      activeFlags[2] |= cond_npc_DOT_lsu_DOT__io_redirect_dnpc_T_1 << 4;      // 20
      npc_DOT_lsu_DOT__sbufReq_wdata_T_15 =
          ((-(uint32_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_12 & npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2) |
           ((-(uint32_t)!npc_DOT_lsu_DOT__sbufReq_wdata_T_12) & 0x0));
      npc_DOT_lsu_DOT__sbufReq_wdata_T_6 =
          (((uint32_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_5 << 16) | (uint16_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_5);
      npc_DOT_lsu_DOT__sbufReq_wdata_T_14 =
          ((-(uint32_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_11 & npc_DOT_lsu_DOT__sbufReq_wdata_T_6) |
           ((-(uint32_t)!npc_DOT_lsu_DOT__sbufReq_wdata_T_11) & 0x0));
      npc_DOT_lsu_DOT__sbufReq_wdata_T_2 =
          (((uint16_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_1 << 8) | (uint8_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_1);
      npc_DOT_lsu_DOT__sbufReq_wdata_T_3 =
          (((uint32_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_2 << 16) | (uint16_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_2);
      npc_DOT_lsu_DOT__sbufReq_wdata_T_13 =
          ((-(uint32_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_10 & npc_DOT_lsu_DOT__sbufReq_wdata_T_3) |
           ((-(uint32_t)!npc_DOT_lsu_DOT__sbufReq_wdata_T_10) & 0x0));
      npc_DOT_lsu_DOT__sbufReq_wdata_T_16 = (npc_DOT_lsu_DOT__sbufReq_wdata_T_13 | npc_DOT_lsu_DOT__sbufReq_wdata_T_14);
      npc_DOT_lsu_DOT__sbufReq_wdata_T_17 = (npc_DOT_lsu_DOT__sbufReq_wdata_T_16 | npc_DOT_lsu_DOT__sbufReq_wdata_T_15);
      if (npc_DOT_lsu_DOT_sbufWen) {
        uint32_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT_DOT_old_DOT_813 =
            npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT;
        npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT = npc_DOT_lsu_DOT__sbufReq_wdata_T_17;
        bool cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT =
            npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT !=
            npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT_DOT_old_DOT_813;
        activeFlags[4] |= cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT << 5; // 37
      } else {
      }
      npc_DOT_lsu_DOT_sbuf_DOT__DOT_wdata =
          ((-(uint32_t)npc_DOT_lsu_DOT_sbufWen & npc_DOT_lsu_DOT__sbufReq_wdata_T_17) |
           ((-(uint32_t)!npc_DOT_lsu_DOT_sbufWen) & npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata));
      uint32_t mem_DOT_dmem_DOT_wdata_DOT_old_DOT_2267 = mem_DOT_dmem_DOT_wdata;
      mem_DOT_dmem_DOT_wdata = npc_DOT_lsu_DOT_sbuf_DOT__DOT_wdata;
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_addr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_size);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wmask);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_mtvec: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mtvec);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_mstatus_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mstatus_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_mepc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mepc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_mvendorid_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mvendorid_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__dnpc_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__dnpc_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_dnpc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_dnpc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__io_redirect_dnpc_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_redirect_dnpc_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__io_redirect_dnpc_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_redirect_dnpc_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_15: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_16: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT__sbufReq_wdata_T_17: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__sbufReq_wdata_T_17);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 npc_DOT_lsu_DOT_sbuf_DOT__DOT_wdata: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_DOT__DOT_wdata);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 13 mem_DOT_dmem_DOT_wdata: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_dmem_DOT_wdata);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x40)) { // id=14
      uint8_t npc_DOT_lsu_DOT_loadUnsign;
      uint8_t npc_DOT_lsu_DOT_loadByte;
      uint8_t npc_DOT_lsu_DOT_loadHalf;
      uint32_t npc_DOT_lsu_DOT__csrOut_T;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_2;
      uint8_t npc_DOT_lsu_DOT__csrOut_T_4;
      uint8_t npc_DOT_lsu_DOT__csrOut_T_5;
      uint8_t npc_DOT_lsu_DOT__csrOut_T_6;
      uint8_t npc_DOT_lsu_DOT__csrOut_T_7;
      uint8_t npc_DOT_lsu_DOT__csrOut_T_8;
      uint8_t npc_DOT_lsu_DOT__csrOut_T_9;
      uint8_t npc_DOT_lsu_DOT__csrOut_T_10;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_17;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_16;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_15;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_13;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_3;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_14;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_1;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_11;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_12;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_18;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_19;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_20;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_21;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_22;
      uint32_t npc_DOT_lsu_DOT__csrOut_T_23;
      uint32_t npc_DOT_lsu_DOT__io_out_bits_res_T;
      uint8_t npc_DOT_lsu_DOT__rdataMuxVecS2_T_2;
      uint8_t npc_DOT_lsu_DOT__rdataMuxVecS2_T_3;
      uint8_t npc_DOT_lsu_DOT__rdataMuxVecS2_T_5;
      uint8_t npc_DOT_lsu_DOT__rdataMuxVecS2_T_7;
      uint8_t npc_DOT_lsu_DOT__rdataMuxVecS2_T_8;
      uint8_t npc_DOT_lsu_DOT__rdataMuxVecS2_T_9;
      uint8_t npc_DOT_lsu_DOT__rdataMuxVecS2_T_10;
      uint8_t npc_DOT_lsu_DOT__rdataMuxVecS2_T_11;
      uint8_t npc_DOT_lsu_DOT__rdata15_8_T;
      uint8_t npc_DOT_lsu_DOT__rdata31_16_T;
      uint16_t npc_DOT_lsu_DOT__rdata31_16_T_1;
      uint16_t npc_DOT_lsu_DOT__rdata31_16_T_2;
      uint8_t npc_DOT_lsu_DOT__rdata15_8_T_1;
      uint8_t npc_DOT_lsu_DOT__rdata15_8_T_2;
      uint8_t npc_DOT_lsu_DOT_rdata15_8;
      uint8_t npc_DOT_lsu_DOT__rdata31_16_T_3;
      uint16_t npc_DOT_lsu_DOT__rdata31_16_T_4;
      uint16_t npc_DOT_lsu_DOT__rdata31_16_T_5;
      uint16_t npc_DOT_lsu_DOT__T;
      uint16_t npc_DOT_lsu_DOT__rdata31_16_T_6;
      uint16_t npc_DOT_lsu_DOT_rdata31_16;
      uint32_t npc_DOT_lsu_DOT_rdata_31_0_hi;
      uint32_t npc_DOT_lsu_DOT_rdata_31_0;
      npc_DOT_lsu_DOT_loadUnsign = ((npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 >> 2) & 0x1);
      npc_DOT_lsu_DOT_loadByte = (npc_DOT_lsu_DOT__sbufReq_wmask_T == 0x0);
      npc_DOT_lsu_DOT_loadHalf = (npc_DOT_lsu_DOT__sbufReq_wmask_T == 0x1);
      npc_DOT_lsu_DOT__csrOut_T = ((npc_DOT_lsu_DOT_mtvec >> 2) & 0x3fffffff);
      npc_DOT_lsu_DOT__csrOut_T_2 = ((npc_DOT_lsu_DOT_mepc >> 2) & 0x3fffffff);
      npc_DOT_lsu_DOT__csrOut_T_4 = (0x305 == npc_DOT_lsu_DOT__csrAddr_T);
      npc_DOT_lsu_DOT__csrOut_T_5 = (0x342 == npc_DOT_lsu_DOT__csrAddr_T);
      npc_DOT_lsu_DOT__csrOut_T_6 = (0x300 == npc_DOT_lsu_DOT__csrAddr_T);
      npc_DOT_lsu_DOT__csrOut_T_7 = (0x341 == npc_DOT_lsu_DOT__csrAddr_T);
      npc_DOT_lsu_DOT__csrOut_T_8 = (0xc00 == npc_DOT_lsu_DOT__csrAddr_T);
      npc_DOT_lsu_DOT__csrOut_T_9 = (0xf11 == npc_DOT_lsu_DOT__csrAddr_T);
      npc_DOT_lsu_DOT__csrOut_T_10 = (0xf12 == npc_DOT_lsu_DOT__csrAddr_T);
      npc_DOT_lsu_DOT__csrOut_T_17 = ((-(uint32_t)npc_DOT_lsu_DOT__csrOut_T_10 & npc_DOT_lsu_DOT_marchid) |
                                      ((-(uint32_t)!npc_DOT_lsu_DOT__csrOut_T_10) & 0x0));
      npc_DOT_lsu_DOT__csrOut_T_16 = ((-(uint32_t)npc_DOT_lsu_DOT__csrOut_T_9 & npc_DOT_lsu_DOT_mvendorid) |
                                      ((-(uint32_t)!npc_DOT_lsu_DOT__csrOut_T_9) & 0x0));
      npc_DOT_lsu_DOT__csrOut_T_15 = ((-(uint32_t)npc_DOT_lsu_DOT__csrOut_T_8 & npc_DOT_lsu_DOT_mcycle) |
                                      ((-(uint32_t)!npc_DOT_lsu_DOT__csrOut_T_8) & 0x0));
      npc_DOT_lsu_DOT__csrOut_T_13 = ((-(uint32_t)npc_DOT_lsu_DOT__csrOut_T_6 & npc_DOT_lsu_DOT_mstatus) |
                                      ((-(uint32_t)!npc_DOT_lsu_DOT__csrOut_T_6) & 0x0));
      npc_DOT_lsu_DOT__csrOut_T_3 = (npc_DOT_lsu_DOT__csrOut_T_2 << 2);
      npc_DOT_lsu_DOT__csrOut_T_14 = ((-(uint32_t)npc_DOT_lsu_DOT__csrOut_T_7 & npc_DOT_lsu_DOT__csrOut_T_3) |
                                      ((-(uint32_t)!npc_DOT_lsu_DOT__csrOut_T_7) & 0x0));
      npc_DOT_lsu_DOT__csrOut_T_1 = (npc_DOT_lsu_DOT__csrOut_T << 2);
      npc_DOT_lsu_DOT__csrOut_T_11 = ((-(uint32_t)npc_DOT_lsu_DOT__csrOut_T_4 & npc_DOT_lsu_DOT__csrOut_T_1) |
                                      ((-(uint32_t)!npc_DOT_lsu_DOT__csrOut_T_4) & 0x0));
      npc_DOT_lsu_DOT__csrOut_T_12 = ((-(uint32_t)npc_DOT_lsu_DOT__csrOut_T_5 & npc_DOT_lsu_DOT_mcause) |
                                      ((-(uint32_t)!npc_DOT_lsu_DOT__csrOut_T_5) & 0x0));
      npc_DOT_lsu_DOT__csrOut_T_18 = (npc_DOT_lsu_DOT__csrOut_T_11 | npc_DOT_lsu_DOT__csrOut_T_12);
      npc_DOT_lsu_DOT__csrOut_T_19 = (npc_DOT_lsu_DOT__csrOut_T_18 | npc_DOT_lsu_DOT__csrOut_T_13);
      npc_DOT_lsu_DOT__csrOut_T_20 = (npc_DOT_lsu_DOT__csrOut_T_19 | npc_DOT_lsu_DOT__csrOut_T_14);
      npc_DOT_lsu_DOT__csrOut_T_21 = (npc_DOT_lsu_DOT__csrOut_T_20 | npc_DOT_lsu_DOT__csrOut_T_15);
      npc_DOT_lsu_DOT__csrOut_T_22 = (npc_DOT_lsu_DOT__csrOut_T_21 | npc_DOT_lsu_DOT__csrOut_T_16);
      npc_DOT_lsu_DOT__csrOut_T_23 = (npc_DOT_lsu_DOT__csrOut_T_22 | npc_DOT_lsu_DOT__csrOut_T_17);
      npc_DOT_lsu_DOT__io_out_bits_res_T =
          ((-(uint32_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR & npc_DOT_lsu_DOT__csrOut_T_23) |
           ((-(uint32_t)!npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR) &
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_res));
      npc_DOT_lsu_DOT__rdataMuxVecS2_T_2 = ((npc_DOT_lsu_DOT_rdataMuxS2 >> 16) & 0xff);
      npc_DOT_lsu_DOT__rdataMuxVecS2_T_3 = ((npc_DOT_lsu_DOT_rdataMuxS2 >> 24) & 0xff);
      npc_DOT_lsu_DOT__rdataMuxVecS2_T_5 = ((npc_DOT_lsu_DOT_rdataMuxS2 >> 8) & 0xff);
      npc_DOT_lsu_DOT__rdataMuxVecS2_T_7 = ((npc_DOT_lsu_DOT_rdataMuxS2 >> 24) & 0xff);
      npc_DOT_lsu_DOT__rdataMuxVecS2_T_8 = (npc_DOT_lsu_DOT_rdataMuxS2 & 0xff);
      npc_DOT_lsu_DOT__rdataMuxVecS2_T_9 = ((npc_DOT_lsu_DOT_rdataMuxS2 >> 8) & 0xff);
      npc_DOT_lsu_DOT__rdataMuxVecS2_T_10 = ((npc_DOT_lsu_DOT_rdataMuxS2 >> 16) & 0xff);
      npc_DOT_lsu_DOT__rdataMuxVecS2_T_11 = ((npc_DOT_lsu_DOT_rdataMuxS2 >> 24) & 0xff);
      npc_DOT_lsu_DOT__WIRE_2[0] = npc_DOT_lsu_DOT__rdataMuxVecS2_T_8;
      npc_DOT_lsu_DOT__WIRE_2[1] = npc_DOT_lsu_DOT__rdataMuxVecS2_T_9;
      npc_DOT_lsu_DOT__WIRE_2[2] = npc_DOT_lsu_DOT__rdataMuxVecS2_T_10;
      npc_DOT_lsu_DOT__WIRE_2[3] = npc_DOT_lsu_DOT__rdataMuxVecS2_T_11;
      npc_DOT_lsu_DOT__rdata15_8_T = ((npc_DOT_lsu_DOT__WIRE_2[npc_DOT_lsu_DOT__sbufReq_wmask_T_1] >> 7) & 0x1);
      npc_DOT_lsu_DOT__rdata31_16_T = ((npc_DOT_lsu_DOT__WIRE_2[npc_DOT_lsu_DOT__sbufReq_wmask_T_1] >> 7) & 0x1);
      npc_DOT_lsu_DOT__rdata31_16_T_1 =
          ((-(uint16_t)npc_DOT_lsu_DOT__rdata31_16_T & 0xffff) | ((-(uint16_t)!npc_DOT_lsu_DOT__rdata31_16_T) & 0x0));
      npc_DOT_lsu_DOT__rdata31_16_T_2 = ((-(uint16_t)npc_DOT_lsu_DOT_loadUnsign & 0x0) |
                                         ((-(uint16_t)!npc_DOT_lsu_DOT_loadUnsign) & npc_DOT_lsu_DOT__rdata31_16_T_1));
      npc_DOT_lsu_DOT__rdata15_8_T_1 =
          ((-(uint8_t)npc_DOT_lsu_DOT__rdata15_8_T & 0xff) | ((-(uint8_t)!npc_DOT_lsu_DOT__rdata15_8_T) & 0x0));
      npc_DOT_lsu_DOT__rdata15_8_T_2 = ((-(uint8_t)npc_DOT_lsu_DOT_loadUnsign & 0x0) |
                                        ((-(uint8_t)!npc_DOT_lsu_DOT_loadUnsign) & npc_DOT_lsu_DOT__rdata15_8_T_1));
      npc_DOT_lsu_DOT__WIRE_1[0] = npc_DOT_lsu_DOT__rdataMuxVecS2_T_5;
      npc_DOT_lsu_DOT__WIRE_1[1] = npc_DOT_lsu_DOT__rdataMuxVecS2_T_7;
      npc_DOT_lsu_DOT_rdata15_8 =
          ((-(uint8_t)npc_DOT_lsu_DOT_loadByte & npc_DOT_lsu_DOT__rdata15_8_T_2) |
           ((-(uint8_t)!npc_DOT_lsu_DOT_loadByte) & npc_DOT_lsu_DOT__WIRE_1[npc_DOT_lsu_DOT__sbufReq_wmask_T_2]));
      npc_DOT_lsu_DOT__rdata31_16_T_3 = ((npc_DOT_lsu_DOT__WIRE_1[npc_DOT_lsu_DOT__sbufReq_wmask_T_2] >> 7) & 0x1);
      npc_DOT_lsu_DOT__rdata31_16_T_4 = ((-(uint16_t)npc_DOT_lsu_DOT__rdata31_16_T_3 & 0xffff) |
                                         ((-(uint16_t)!npc_DOT_lsu_DOT__rdata31_16_T_3) & 0x0));
      npc_DOT_lsu_DOT__rdata31_16_T_5 = ((-(uint16_t)npc_DOT_lsu_DOT_loadUnsign & 0x0) |
                                         ((-(uint16_t)!npc_DOT_lsu_DOT_loadUnsign) & npc_DOT_lsu_DOT__rdata31_16_T_4));
      npc_DOT_lsu_DOT__T =
          (((uint16_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_3 << 8) | (uint8_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_2);
      npc_DOT_lsu_DOT__rdata31_16_T_6 = ((-(uint16_t)npc_DOT_lsu_DOT_loadHalf & npc_DOT_lsu_DOT__rdata31_16_T_5) |
                                         ((-(uint16_t)!npc_DOT_lsu_DOT_loadHalf) & npc_DOT_lsu_DOT__T));
      npc_DOT_lsu_DOT_rdata31_16 = ((-(uint16_t)npc_DOT_lsu_DOT_loadByte & npc_DOT_lsu_DOT__rdata31_16_T_2) |
                                    ((-(uint16_t)!npc_DOT_lsu_DOT_loadByte) & npc_DOT_lsu_DOT__rdata31_16_T_6));
      npc_DOT_lsu_DOT_rdata_31_0_hi =
          (((uint32_t)npc_DOT_lsu_DOT_rdata31_16 << 8) | (uint8_t)npc_DOT_lsu_DOT_rdata15_8);
      npc_DOT_lsu_DOT_rdata_31_0 =
          ((npc_DOT_lsu_DOT_rdata_31_0_hi << 8) | (uint8_t)npc_DOT_lsu_DOT__WIRE_2[npc_DOT_lsu_DOT__sbufReq_wmask_T_1]);
      uint32_t npc_DOT_lsu_DOT__io_out_bits_res_T_1_DOT_old_DOT_944 = npc_DOT_lsu_DOT__io_out_bits_res_T_1;
      npc_DOT_lsu_DOT__io_out_bits_res_T_1 =
          ((-(uint32_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad & npc_DOT_lsu_DOT_rdata_31_0) |
           ((-(uint32_t)!npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad) &
            npc_DOT_lsu_DOT__io_out_bits_res_T));
      bool cond_npc_DOT_lsu_DOT__io_out_bits_res_T_1 =
          npc_DOT_lsu_DOT__io_out_bits_res_T_1 != npc_DOT_lsu_DOT__io_out_bits_res_T_1_DOT_old_DOT_944;
      oldFlag |= -(uint8_t)cond_npc_DOT_lsu_DOT__io_out_bits_res_T_1 & 0x80; // 15
      activeFlags[3] |= cond_npc_DOT_lsu_DOT__io_out_bits_res_T_1 << 2;      // 26
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_rdataMuxS2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_rdataMuxS2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_loadUnsign: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_loadUnsign);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_loadByte: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_loadByte);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_loadHalf: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_loadHalf);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_mcause: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mcause);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_17: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_17);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_16: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_15: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_18: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_18);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_19: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_19);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_20: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_20);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_21: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_21);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_22: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_22);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__csrOut_T_23: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__csrOut_T_23);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__io_out_bits_res_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_bits_res_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdataMuxVecS2_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdataMuxVecS2_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdataMuxVecS2_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdataMuxVecS2_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdataMuxVecS2_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdataMuxVecS2_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdataMuxVecS2_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdataMuxVecS2_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdataMuxVecS2_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__WIRE_2: ", cycles);
        for (int i0 = 0; i0 < 4; i0++) {
          printf("%lx", (uint64_t)npc_DOT_lsu_DOT__WIRE_2[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata15_8_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata15_8_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata31_16_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata31_16_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata31_16_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata31_16_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata31_16_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata31_16_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata15_8_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata15_8_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata15_8_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata15_8_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__WIRE_1: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_lsu_DOT__WIRE_1[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_rdata15_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_rdata15_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata31_16_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata31_16_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata31_16_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata31_16_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata31_16_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata31_16_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__rdata31_16_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__rdata31_16_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_rdata31_16: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_rdata31_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_rdata_31_0_hi: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_rdata_31_0_hi);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT_rdata_31_0: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_rdata_31_0);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 14 npc_DOT_lsu_DOT__io_out_bits_res_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_bits_res_T_1);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x80)) { // id=15
      uint8_t npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T = 0;
      uint8_t npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_1 = 0;
      uint32_t npc_DOT_lsu_DOT__io_out_bits_npctrap_dnpc_T = 0;
      uint8_t npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_2 = 0;
      uint8_t npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_3 = 0;
      if (npc_DOT_lsu_DOT__io_out_valid_T_2) {
        npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T = (npc_DOT_lsu_DOT_isValidLoad | npc_DOT_lsu_DOT_isValidStore);
        npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_1 = ((npc_DOT_lsu_io_in_bits_r_DOT__DOT_res >> 31) & 0x1);
        uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT_DOT_old_DOT_1187 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT = npc_DOT_lsu_DOT__io_out_bits_res_T_1;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT !=
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT_DOT_old_DOT_1187;
        activeFlags[5] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT << 4; // 44
        uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen_DOT_old_DOT_1188 = npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen = npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen ^ npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen_DOT_old_DOT_1188;
        activeFlags[0] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen << 3; // 3
        uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT_DOT_old_DOT_1189 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT = npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT !=
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT_DOT_old_DOT_1189;
        activeFlags[5] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT << 4; // 44
        uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr_DOT_old_DOT_1196 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr = npc_DOT_lsu_io_in_bits_r_DOT__DOT_res;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr !=
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr_DOT_old_DOT_1196;
        activeFlags[0] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr << 5; // 5
        uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip_DOT_old_DOT_1197 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip ^
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip_DOT_old_DOT_1197;
        activeFlags[0] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip << 4; // 4
        uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code_DOT_old_DOT_1194 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code !=
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code_DOT_old_DOT_1194;
        activeFlags[0] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code << 5; // 5
        uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak_DOT_old_DOT_1193 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak ^
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak_DOT_old_DOT_1193;
        activeFlags[0] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak << 5; // 5
        npc_DOT_lsu_DOT__io_out_bits_npctrap_dnpc_T =
            ((-(uint32_t)npc_DOT_lsu_DOT__io_redirect_valid_T_2 & npc_DOT_lsu_DOT__io_redirect_dnpc_T_1) |
             ((-(uint32_t)!npc_DOT_lsu_DOT__io_redirect_valid_T_2) &
              npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc));
        uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc_DOT_old_DOT_1192 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc = npc_DOT_lsu_DOT__io_out_bits_npctrap_dnpc_T;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc !=
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc_DOT_old_DOT_1192;
        activeFlags[0] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc << 5; // 5
        uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc_DOT_old_DOT_1191 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc = npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc !=
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc_DOT_old_DOT_1191;
        activeFlags[0] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc << 4; // 4
        npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_2 = (npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_1 == 0x0);
        npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_3 =
            (npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T & npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_2);
        uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO_DOT_old_DOT_1195 =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO;
        npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO = npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_3;
        bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO =
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO ^
            npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO_DOT_old_DOT_1195;
        activeFlags[0] |= cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO << 5; // 5
      } else {
      }
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_wen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_memAddr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_DOT__io_out_bits_npctrap_dnpc_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_bits_npctrap_dnpc_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_out_bits_npctrap_isMMIO_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 15 npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isMMIO);
        printf("\n");
      }
#endif
    }
  }
  if (unlikely(activeFlags[2] != 0)) {
    uint8_t oldFlag = activeFlags[2];
    activeFlags[2] = 0;
    if (unlikely(oldFlag & 0x1)) { // id=16
      uint8_t npc_DOT_idu_DOT__T_14 = 0;
      uint8_t npc_DOT_idu_DOT__isUtype_T = 0;
      uint8_t npc_DOT_idu_DOT__rs1_T = 0;
      uint8_t npc_DOT_idu_DOT__rs2_T = 0;
      uint8_t npc_DOT_idu_DOT__isRtype_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__isRtype_T_3 = 0;
      uint8_t npc_DOT_idu_DOT__src1UseReg_T = 0;
      uint8_t npc_DOT_idu_DOT__T_3 = 0;
      uint8_t npc_DOT_idu_DOT__T_2 = 0;
      if (npc_DOT_wbu_DOT__io_wb_wen_T) {
        npc_DOT_idu_DOT__T_14 = (npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd != 0x0);
      } else {
      }
      uint8_t npc_DOT_idu_DOT_isEbreak_DOT_old_DOT_113 = npc_DOT_idu_DOT_isEbreak;
      npc_DOT_idu_DOT_isEbreak = (npc_DOT_idu_io_in_bits_r_DOT__DOT_inst == 0x100073);
      bool cond_npc_DOT_idu_DOT_isEbreak = npc_DOT_idu_DOT_isEbreak ^ npc_DOT_idu_DOT_isEbreak_DOT_old_DOT_113;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_isEbreak << 2; // 26
      npc_DOT_idu_DOT__isUtype_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 2) & 0x7);
      uint8_t npc_DOT_idu_DOT__isStype_T_DOT_old_DOT_118 = npc_DOT_idu_DOT__isStype_T;
      npc_DOT_idu_DOT__isStype_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 2) & 0x1f);
      bool cond_npc_DOT_idu_DOT__isStype_T = npc_DOT_idu_DOT__isStype_T != npc_DOT_idu_DOT__isStype_T_DOT_old_DOT_118;
      activeFlags[3] |= cond_npc_DOT_idu_DOT__isStype_T << 2; // 26
      npc_DOT_idu_DOT__rs1_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 15) & 0xf);
      npc_DOT_idu_DOT__rs2_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 20) & 0xf);
      uint8_t npc_DOT_idu_DOT_isJtype_DOT_old_DOT_117 = npc_DOT_idu_DOT_isJtype;
      npc_DOT_idu_DOT_isJtype = (npc_DOT_idu_DOT__isStype_T == 0x1b);
      bool cond_npc_DOT_idu_DOT_isJtype = npc_DOT_idu_DOT_isJtype ^ npc_DOT_idu_DOT_isJtype_DOT_old_DOT_117;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_isJtype << 2; // 26
      uint8_t npc_DOT_idu_DOT_isStype_DOT_old_DOT_119 = npc_DOT_idu_DOT_isStype;
      npc_DOT_idu_DOT_isStype = (npc_DOT_idu_DOT__isStype_T == 0x8);
      bool cond_npc_DOT_idu_DOT_isStype = npc_DOT_idu_DOT_isStype ^ npc_DOT_idu_DOT_isStype_DOT_old_DOT_119;
      oldFlag |= -(uint8_t)cond_npc_DOT_idu_DOT_isStype & 0x20; // 21
      activeFlags[3] |= cond_npc_DOT_idu_DOT_isStype << 2;      // 26
      uint8_t npc_DOT_idu_DOT_isBtype_DOT_old_DOT_121 = npc_DOT_idu_DOT_isBtype;
      npc_DOT_idu_DOT_isBtype = (npc_DOT_idu_DOT__isStype_T == 0x18);
      bool cond_npc_DOT_idu_DOT_isBtype = npc_DOT_idu_DOT_isBtype ^ npc_DOT_idu_DOT_isBtype_DOT_old_DOT_121;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_isBtype << 2; // 26
      npc_DOT_idu_DOT__isRtype_T_1 = (npc_DOT_idu_DOT__isStype_T == 0xc);
      npc_DOT_idu_DOT__isRtype_T_3 = (npc_DOT_idu_DOT__isStype_T == 0xe);
      uint8_t npc_DOT_idu_DOT_isRtype_DOT_old_DOT_131 = npc_DOT_idu_DOT_isRtype;
      npc_DOT_idu_DOT_isRtype = (npc_DOT_idu_DOT__isRtype_T_1 | npc_DOT_idu_DOT__isRtype_T_3);
      bool cond_npc_DOT_idu_DOT_isRtype = npc_DOT_idu_DOT_isRtype ^ npc_DOT_idu_DOT_isRtype_DOT_old_DOT_131;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_isRtype << 2; // 26
      uint8_t npc_DOT_idu_DOT_src2UseReg_DOT_old_DOT_328 = npc_DOT_idu_DOT_src2UseReg;
      npc_DOT_idu_DOT_src2UseReg = (npc_DOT_idu_DOT_isRtype | npc_DOT_idu_DOT_isBtype);
      bool cond_npc_DOT_idu_DOT_src2UseReg = npc_DOT_idu_DOT_src2UseReg ^ npc_DOT_idu_DOT_src2UseReg_DOT_old_DOT_328;
      oldFlag |= -(uint8_t)cond_npc_DOT_idu_DOT_src2UseReg & 0x20; // 21
      activeFlags[3] |= cond_npc_DOT_idu_DOT_src2UseReg << 2;      // 26
      uint8_t npc_DOT_idu_DOT_isUtype_DOT_old_DOT_115 = npc_DOT_idu_DOT_isUtype;
      npc_DOT_idu_DOT_isUtype = (npc_DOT_idu_DOT__isUtype_T == 0x5);
      bool cond_npc_DOT_idu_DOT_isUtype = npc_DOT_idu_DOT_isUtype ^ npc_DOT_idu_DOT_isUtype_DOT_old_DOT_115;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_isUtype << 2; // 26
      npc_DOT_idu_DOT__src1UseReg_T = (npc_DOT_idu_DOT_isUtype | npc_DOT_idu_DOT_isJtype);
      uint8_t npc_DOT_idu_DOT_src1UseReg_DOT_old_DOT_327 = npc_DOT_idu_DOT_src1UseReg;
      npc_DOT_idu_DOT_src1UseReg = (npc_DOT_idu_DOT__src1UseReg_T == 0x0);
      bool cond_npc_DOT_idu_DOT_src1UseReg = npc_DOT_idu_DOT_src1UseReg ^ npc_DOT_idu_DOT_src1UseReg_DOT_old_DOT_327;
      oldFlag |= -(uint8_t)cond_npc_DOT_idu_DOT_src1UseReg & 0x20; // 21
      activeFlags[3] |= cond_npc_DOT_idu_DOT_src1UseReg << 2;      // 26
      uint8_t npc_DOT_idu_DOT__rs1_T_1_DOT_old_DOT_317 = npc_DOT_idu_DOT__rs1_T_1;
      npc_DOT_idu_DOT__rs1_T_1 = ((-(uint8_t)npc_DOT_idu_DOT_isEbreak & 0xa) |
                                  ((-(uint8_t)!npc_DOT_idu_DOT_isEbreak) & npc_DOT_idu_DOT__rs1_T));
      bool cond_npc_DOT_idu_DOT__rs1_T_1 = npc_DOT_idu_DOT__rs1_T_1 != npc_DOT_idu_DOT__rs1_T_1_DOT_old_DOT_317;
      oldFlag |= -(uint8_t)cond_npc_DOT_idu_DOT__rs1_T_1 & 0x20; // 21
      activeFlags[3] |= cond_npc_DOT_idu_DOT__rs1_T_1 << 2;      // 26
      uint8_t npc_DOT_idu_DOT__rs2_T_1_DOT_old_DOT_320 = npc_DOT_idu_DOT__rs2_T_1;
      npc_DOT_idu_DOT__rs2_T_1 = ((-(uint8_t)npc_DOT_idu_DOT_isEbreak & 0xb) |
                                  ((-(uint8_t)!npc_DOT_idu_DOT_isEbreak) & npc_DOT_idu_DOT__rs2_T));
      bool cond_npc_DOT_idu_DOT__rs2_T_1 = npc_DOT_idu_DOT__rs2_T_1 != npc_DOT_idu_DOT__rs2_T_1_DOT_old_DOT_320;
      oldFlag |= -(uint8_t)cond_npc_DOT_idu_DOT__rs2_T_1 & 0x20; // 21
      activeFlags[3] |= cond_npc_DOT_idu_DOT__rs2_T_1 << 2;      // 26
      npc_DOT_idu_DOT__T_3 = (npc_DOT_idu_DOT__rs2_T_1 == npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd);
      uint32_t npc_DOT_idu_DOT_MPORT_1_DOT_old_DOT_360 = npc_DOT_idu_DOT_MPORT_1;
      npc_DOT_idu_DOT_MPORT_1 = npc_DOT_idu_DOT_R[npc_DOT_idu_DOT__rs2_T_1];
      bool cond_npc_DOT_idu_DOT_MPORT_1 = npc_DOT_idu_DOT_MPORT_1 != npc_DOT_idu_DOT_MPORT_1_DOT_old_DOT_360;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_MPORT_1 << 2; // 26
      uint8_t npc_DOT_idu_DOT_lsCanFwRs2_DOT_old_DOT_348 = npc_DOT_idu_DOT_lsCanFwRs2;
      npc_DOT_idu_DOT_lsCanFwRs2 = (npc_DOT_lsu_DOT__io_fw_wen_T & npc_DOT_idu_DOT__T_3);
      bool cond_npc_DOT_idu_DOT_lsCanFwRs2 = npc_DOT_idu_DOT_lsCanFwRs2 ^ npc_DOT_idu_DOT_lsCanFwRs2_DOT_old_DOT_348;
      oldFlag |= -(uint8_t)cond_npc_DOT_idu_DOT_lsCanFwRs2 & 0x20; // 21
      activeFlags[3] |= cond_npc_DOT_idu_DOT_lsCanFwRs2 << 2;      // 26
      npc_DOT_idu_DOT__T_2 = (npc_DOT_idu_DOT__rs1_T_1 == npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd);
      uint32_t npc_DOT_idu_DOT_MPORT_DOT_old_DOT_353 = npc_DOT_idu_DOT_MPORT;
      npc_DOT_idu_DOT_MPORT = npc_DOT_idu_DOT_R[npc_DOT_idu_DOT__rs1_T_1];
      bool cond_npc_DOT_idu_DOT_MPORT = npc_DOT_idu_DOT_MPORT != npc_DOT_idu_DOT_MPORT_DOT_old_DOT_353;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_MPORT << 2; // 26
      uint8_t npc_DOT_idu_DOT_lsCanFwRs1_DOT_old_DOT_346 = npc_DOT_idu_DOT_lsCanFwRs1;
      npc_DOT_idu_DOT_lsCanFwRs1 = (npc_DOT_lsu_DOT__io_fw_wen_T & npc_DOT_idu_DOT__T_2);
      bool cond_npc_DOT_idu_DOT_lsCanFwRs1 = npc_DOT_idu_DOT_lsCanFwRs1 ^ npc_DOT_idu_DOT_lsCanFwRs1_DOT_old_DOT_346;
      oldFlag |= -(uint8_t)cond_npc_DOT_idu_DOT_lsCanFwRs1 & 0x20; // 21
      activeFlags[3] |= cond_npc_DOT_idu_DOT_lsCanFwRs1 << 2;      // 26
      if (npc_DOT_wbu_DOT__io_wb_wen_T) {
        if (npc_DOT_idu_DOT__T_14) {
          npc_DOT_idu_DOT_R[npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd] = npc_DOT_wbu_io_in_bits_r_DOT__DOT_res;
          activeFlags[2] |= 0x1; // 16
        } else {
        }
      } else {
      }
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_lsu_DOT_marchid_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_marchid_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_io_in_bits_r_DOT__DOT_inst: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_io_in_bits_r_DOT__DOT_inst);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_isEbreak: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isEbreak);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__isUtype_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__isUtype_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__isStype_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__isStype_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__rs1_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__rs1_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__rs2_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__rs2_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_isJtype: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isJtype);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_isStype: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isStype);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_isBtype: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isBtype);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__isRtype_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__isRtype_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__isRtype_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__isRtype_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_isRtype: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isRtype);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_src2UseReg: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_src2UseReg);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_isUtype: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isUtype);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__src1UseReg_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__src1UseReg_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_src1UseReg: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_src1UseReg);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__rs1_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__rs1_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__rs2_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__rs2_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_MPORT_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_MPORT_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_lsCanFwRs2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_lsCanFwRs2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT__T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_MPORT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_MPORT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_lsCanFwRs1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_lsCanFwRs1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 16 npc_DOT_idu_DOT_MPORT_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_MPORT_2);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x2)) { // id=17
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T_11 = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T_1 = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T_4 = 0;
      uint8_t npc_DOT_icache_DOT__T_21 = 0;
      uint8_t npc_DOT_icache_DOT__T_25 = 0;
      uint8_t npc_DOT_icache_DOT__value_T = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T_5 = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T_6 = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T_9 = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T_10 = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_valid_T_12 = 0;
      uint32_t npc_DOT_ifu_DOT__pc_s2_T = 0;
      uint8_t npc_DOT_icache_DOT__wordIdx_s1_WIRE_1 = 0;
      uint8_t npc_DOT_icache_DOT__idx_s1_WIRE_1 = 0;
      npc_DOT_icache_DOT__io_mem_ar_valid_T = (npc_DOT_icache_DOT_state == 0x0);
      npc_DOT_icache_DOT__io_mem_ar_valid_T_11 = (npc_DOT_icache_DOT_state == 0x2);
      npc_DOT_icache_DOT__io_mem_ar_valid_T_1 = (npc_DOT_icache_DOT__io_mem_ar_valid_T & npc_DOT_icache_DOT_reqValid);
      npc_DOT_icache_DOT__io_mem_ar_valid_T_4 = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio == 0x0);
      npc_DOT_icache_DOT__T_21 = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio == 0x0);
      npc_DOT_icache_DOT__T_25 = (npc_DOT_icache_DOT__T_21 & npc_DOT_icache_DOT__resFromMem_T);
      if (npc_DOT_icache_DOT__T_25) {
        npc_DOT_icache_DOT__value_T = ((npc_DOT_icache_DOT_beatCnt_value + 0x1) & 0x3);
        uint8_t npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT_DOT_old_DOT_1394 = npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT;
        npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT = npc_DOT_icache_DOT__value_T;
        bool cond_npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT =
            npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT != npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT_DOT_old_DOT_1394;
        activeFlags[5] |= cond_npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT << 5; // 45
      } else {
      }
      npc_DOT_icache_DOT__io_mem_ar_valid_T_5 = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit == 0x0);
      npc_DOT_icache_DOT__io_mem_ar_valid_T_6 =
          (npc_DOT_icache_DOT__io_mem_ar_valid_T_4 & npc_DOT_icache_DOT__io_mem_ar_valid_T_5);
      npc_DOT_icache_DOT__io_mem_ar_valid_T_9 =
          (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio | npc_DOT_icache_DOT__io_mem_ar_valid_T_6);
      npc_DOT_icache_DOT__io_mem_ar_valid_T_10 =
          (npc_DOT_icache_DOT__io_mem_ar_valid_T_1 & npc_DOT_icache_DOT__io_mem_ar_valid_T_9);
      npc_DOT_icache_DOT__io_mem_ar_valid_T_12 =
          (npc_DOT_icache_DOT__io_mem_ar_valid_T_10 | npc_DOT_icache_DOT__io_mem_ar_valid_T_11);
      uint8_t npc_DOT_xbar_DOT_hasReadValid_DOT_old_DOT_1711 = npc_DOT_xbar_DOT_hasReadValid;
      npc_DOT_xbar_DOT_hasReadValid = (npc_DOT_lsu_DOT__io_mem_ar_valid_T_1 | npc_DOT_icache_DOT__io_mem_ar_valid_T_12);
      bool cond_npc_DOT_xbar_DOT_hasReadValid =
          npc_DOT_xbar_DOT_hasReadValid ^ npc_DOT_xbar_DOT_hasReadValid_DOT_old_DOT_1711;
      oldFlag |= -(uint8_t)cond_npc_DOT_xbar_DOT_hasReadValid & 0x4; // 18
      activeFlags[3] |= cond_npc_DOT_xbar_DOT_hasReadValid << 5;     // 29
      npc_DOT_ifu_DOT__pc_s2_T = ((npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr >> 2) & 0x3fffffff);
      npc_DOT_icache_DOT__wordIdx_s1_WIRE_1 = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr & 0xf);
      npc_DOT_icache_DOT__idx_s1_WIRE_1 = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr & 0x3f);
      uint32_t npc_DOT_icache_DOT__tag_s1_T_3_DOT_old_DOT_1387 = npc_DOT_icache_DOT__tag_s1_T_3;
      npc_DOT_icache_DOT__tag_s1_T_3 = ((npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr >> 6) & 0x3ffffff);
      bool cond_npc_DOT_icache_DOT__tag_s1_T_3 =
          npc_DOT_icache_DOT__tag_s1_T_3 != npc_DOT_icache_DOT__tag_s1_T_3_DOT_old_DOT_1387;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT__tag_s1_T_3 & 0x4; // 18
      activeFlags[3] |= cond_npc_DOT_icache_DOT__tag_s1_T_3 << 7;     // 31
      uint8_t npc_DOT_icache_DOT__idx_s1_T_2_DOT_old_DOT_1377 = npc_DOT_icache_DOT__idx_s1_T_2;
      npc_DOT_icache_DOT__idx_s1_T_2 = ((npc_DOT_icache_DOT__idx_s1_WIRE_1 >> 4) & 0x3);
      bool cond_npc_DOT_icache_DOT__idx_s1_T_2 =
          npc_DOT_icache_DOT__idx_s1_T_2 != npc_DOT_icache_DOT__idx_s1_T_2_DOT_old_DOT_1377;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT__idx_s1_T_2 & 0x4;                               // 18
      *(uint64_t *)&activeFlags[0] |= -(uint64_t)cond_npc_DOT_icache_DOT__idx_s1_T_2 & 0x480000000; // 34 31
      uint32_t npc_DOT_icache_DOT_dataRead_s1_MPORT_DOT_old_DOT_1388 = npc_DOT_icache_DOT_dataRead_s1_MPORT;
      npc_DOT_icache_DOT_dataRead_s1_MPORT = npc_DOT_icache_DOT_data_0[npc_DOT_icache_DOT__idx_s1_T_2];
      bool cond_npc_DOT_icache_DOT_dataRead_s1_MPORT =
          npc_DOT_icache_DOT_dataRead_s1_MPORT != npc_DOT_icache_DOT_dataRead_s1_MPORT_DOT_old_DOT_1388;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT_dataRead_s1_MPORT & 0x10; // 20
      activeFlags[4] |= cond_npc_DOT_icache_DOT_dataRead_s1_MPORT << 2;      // 34
      uint32_t npc_DOT_icache_DOT_dataRead_s1_MPORT_1_DOT_old_DOT_1389 = npc_DOT_icache_DOT_dataRead_s1_MPORT_1;
      npc_DOT_icache_DOT_dataRead_s1_MPORT_1 = npc_DOT_icache_DOT_data_1[npc_DOT_icache_DOT__idx_s1_T_2];
      bool cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_1 =
          npc_DOT_icache_DOT_dataRead_s1_MPORT_1 != npc_DOT_icache_DOT_dataRead_s1_MPORT_1_DOT_old_DOT_1389;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_1 & 0x10; // 20
      activeFlags[4] |= cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_1 << 2;      // 34
      uint32_t npc_DOT_icache_DOT_dataRead_s1_MPORT_2_DOT_old_DOT_1390 = npc_DOT_icache_DOT_dataRead_s1_MPORT_2;
      npc_DOT_icache_DOT_dataRead_s1_MPORT_2 = npc_DOT_icache_DOT_data_2[npc_DOT_icache_DOT__idx_s1_T_2];
      bool cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_2 =
          npc_DOT_icache_DOT_dataRead_s1_MPORT_2 != npc_DOT_icache_DOT_dataRead_s1_MPORT_2_DOT_old_DOT_1390;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_2 & 0x10; // 20
      activeFlags[4] |= cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_2 << 2;      // 34
      uint32_t npc_DOT_icache_DOT_dataRead_s1_MPORT_3_DOT_old_DOT_1391 = npc_DOT_icache_DOT_dataRead_s1_MPORT_3;
      npc_DOT_icache_DOT_dataRead_s1_MPORT_3 = npc_DOT_icache_DOT_data_3[npc_DOT_icache_DOT__idx_s1_T_2];
      bool cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_3 =
          npc_DOT_icache_DOT_dataRead_s1_MPORT_3 != npc_DOT_icache_DOT_dataRead_s1_MPORT_3_DOT_old_DOT_1391;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_3 & 0x10; // 20
      activeFlags[4] |= cond_npc_DOT_icache_DOT_dataRead_s1_MPORT_3 << 2;      // 34
      uint8_t npc_DOT_icache_DOT__wordIdx_s1_T_1_DOT_old_DOT_1367 = npc_DOT_icache_DOT__wordIdx_s1_T_1;
      npc_DOT_icache_DOT__wordIdx_s1_T_1 = ((npc_DOT_icache_DOT__wordIdx_s1_WIRE_1 >> 2) & 0x3);
      bool cond_npc_DOT_icache_DOT__wordIdx_s1_T_1 =
          npc_DOT_icache_DOT__wordIdx_s1_T_1 != npc_DOT_icache_DOT__wordIdx_s1_T_1_DOT_old_DOT_1367;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT__wordIdx_s1_T_1 & 0x10; // 20
      activeFlags[4] |= cond_npc_DOT_icache_DOT__wordIdx_s1_T_1 << 2;      // 34
      uint32_t npc_DOT_ifu_DOT_pc_s2_DOT_old_DOT_65 = npc_DOT_ifu_DOT_pc_s2;
      npc_DOT_ifu_DOT_pc_s2 = (npc_DOT_ifu_DOT__pc_s2_T << 2);
      bool cond_npc_DOT_ifu_DOT_pc_s2 = npc_DOT_ifu_DOT_pc_s2 != npc_DOT_ifu_DOT_pc_s2_DOT_old_DOT_65;
      oldFlag |= -(uint8_t)cond_npc_DOT_ifu_DOT_pc_s2 & 0x40; // 22
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__T_21: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_21);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__T_25: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_25);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__value_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__value_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__io_mem_ar_valid_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_valid_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_xbar_DOT_hasReadValid: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_hasReadValid);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_ifu_DOT__pc_s2_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_ifu_DOT__pc_s2_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__wordIdx_s1_WIRE_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__wordIdx_s1_WIRE_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__idx_s1_WIRE_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__idx_s1_WIRE_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__tag_s1_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__tag_s1_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__idx_s1_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__idx_s1_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT_dataRead_s1_MPORT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_dataRead_s1_MPORT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT_dataRead_s1_MPORT_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_dataRead_s1_MPORT_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT_dataRead_s1_MPORT_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_dataRead_s1_MPORT_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT_dataRead_s1_MPORT_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_dataRead_s1_MPORT_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_icache_DOT__wordIdx_s1_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__wordIdx_s1_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 17 npc_DOT_ifu_DOT_pc_s2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_ifu_DOT_pc_s2);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x4)) { // id=18
      uint32_t npc_DOT_icache_DOT__beatAddr_T = 0;
      uint8_t npc_DOT_xbar_DOT__acceptRead_T = 0;
      uint8_t npc_DOT_xbar_DOT__io_out_ar_valid_T = 0;
      uint8_t npc_DOT_xbar2_DOT__io_out_1_ar_valid_T = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__io_dmem_ren_T = 0;
      uint8_t npc_DOT_xbar_DOT_acceptRead = 0;
      uint32_t npc_DOT_icache_DOT_beatAddr = 0;
      uint32_t npc_DOT_icache_DOT__io_mem_ar_bits_addr_T = 0;
      uint32_t npc_DOT_xbar2_DOT__arSel_0_T = 0;
      uint32_t npc_DOT_xbar2_DOT__arSel_0_T_2 = 0;
      uint8_t npc_DOT_xbar2_DOT__arSel_0_T_3 = 0;
      uint8_t npc_DOT_xbar2_DOT__arSel_0_T_4 = 0;
      uint8_t npc_DOT_xbar2_DOT__arSel_1_T_5 = 0;
      uint8_t npc_DOT_xbar2_DOT__arSelIdx_T = 0;
      uint8_t npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__io_dmem_ren_T_1 = 0;
      uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size = 0;
      uint8_t npc_DOT_xbar2_DOT_arSelIdx = 0;
      npc_DOT_icache_DOT__beatAddr_T =
          ((npc_DOT_icache_DOT__tag_s1_T_3 << 2) | (uint8_t)npc_DOT_icache_DOT__idx_s1_T_2);
      npc_DOT_xbar_DOT__acceptRead_T = (npc_DOT_xbar_DOT_stateRead == 0x0);
      npc_DOT_xbar_DOT__io_out_ar_valid_T = (npc_DOT_xbar_DOT_stateRead != 0x2);
      npc_DOT_xbar2_DOT__io_out_1_ar_valid_T = (npc_DOT_xbar2_DOT_stateRead == 0x0);
      mem_DOT_axi4memctrl_DOT__io_dmem_ren_T = mem_DOT_axi4memctrl_DOT_state_r;
      uint8_t npc_DOT_xbar_DOT__io_out_ar_valid_T_1_DOT_old_DOT_1743 = npc_DOT_xbar_DOT__io_out_ar_valid_T_1;
      npc_DOT_xbar_DOT__io_out_ar_valid_T_1 = (npc_DOT_xbar_DOT_hasReadValid & npc_DOT_xbar_DOT__io_out_ar_valid_T);
      bool cond_npc_DOT_xbar_DOT__io_out_ar_valid_T_1 =
          npc_DOT_xbar_DOT__io_out_ar_valid_T_1 ^ npc_DOT_xbar_DOT__io_out_ar_valid_T_1_DOT_old_DOT_1743;
      activeFlags[3] |= cond_npc_DOT_xbar_DOT__io_out_ar_valid_T_1 << 4; // 28
      npc_DOT_xbar_DOT_acceptRead = (npc_DOT_xbar_DOT__acceptRead_T & npc_DOT_xbar_DOT__io_out_ar_valid_T_1);
      if (npc_DOT_xbar_DOT_acceptRead) {
        uint8_t npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT_DOT_old_DOT_1737 =
            npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT;
        npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT = npc_DOT_xbar_DOT_chosenReadIdx;
        bool cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT =
            npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT ^
            npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT_DOT_old_DOT_1737;
        activeFlags[5] |= cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT << 7; // 47
      } else {
      }
      uint8_t npc_DOT_xbar_DOT_chosenReadIdxReg_s0_DOT_old_DOT_1739 = npc_DOT_xbar_DOT_chosenReadIdxReg_s0;
      npc_DOT_xbar_DOT_chosenReadIdxReg_s0 = ((npc_DOT_xbar_DOT_acceptRead & npc_DOT_xbar_DOT_chosenReadIdx) |
                                              ((!npc_DOT_xbar_DOT_acceptRead) & npc_DOT_xbar_DOT_chosenReadIdxReg_s1));
      bool cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s0 =
          npc_DOT_xbar_DOT_chosenReadIdxReg_s0 ^ npc_DOT_xbar_DOT_chosenReadIdxReg_s0_DOT_old_DOT_1739;
      oldFlag |= -(uint8_t)cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s0 & 0x8; // 19
      activeFlags[3] |= cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s0 << 7;     // 31
      npc_DOT_icache_DOT_beatAddr = (npc_DOT_icache_DOT__beatAddr_T << 4);
      npc_DOT_icache_DOT__io_mem_ar_bits_addr_T =
          ((-(uint32_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio &
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr) |
           ((-(uint32_t)!npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio) & npc_DOT_icache_DOT_beatAddr));
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr[0] =
          npc_DOT_lsu_io_in_bits_r_DOT__DOT_res;
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr[1] =
          npc_DOT_icache_DOT__io_mem_ar_bits_addr_T;
      uint32_t npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr_DOT_old_DOT_1670 =
          npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr;
      npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr =
          npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr[npc_DOT_xbar_DOT_chosenReadIdxReg_s0];
      bool cond_npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr =
          npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr !=
          npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr_DOT_old_DOT_1670;
      activeFlags[4] |=
          -(uint8_t)cond_npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr & 0x9; // 32 35
      npc_DOT_xbar2_DOT__arSel_0_T =
          (npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr ^ 0x2000000);
      if (npc_DOT_xbar_DOT__io_out_ar_valid_T_1) {
        uint16_t npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr_DOT_old_DOT_1920 =
            npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr;
        npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr =
            (npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr & 0xffff);
        bool cond_npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr =
            npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr !=
            npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr_DOT_old_DOT_1920;
        activeFlags[0] |= cond_npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr << 2; // 2
      } else {
      }
      npc_DOT_xbar2_DOT__arSel_0_T_2 = (npc_DOT_xbar2_DOT__arSel_0_T & 0xffff0000);
      npc_DOT_xbar2_DOT__arSel_0_T_3 = (npc_DOT_xbar2_DOT__arSel_0_T_2 == 0x0);
      npc_DOT_xbar2_DOT__arSel_0_T_4 = (npc_DOT_xbar_DOT__io_out_ar_valid_T_1 & npc_DOT_xbar2_DOT__arSel_0_T_3);
      npc_DOT_xbar2_DOT__arSel_1_T_5 = (npc_DOT_xbar2_DOT__arSel_0_T_4 == 0x0);
      if (npc_DOT_xbar_DOT__io_out_ar_valid_T_1) {
        uint8_t npc_DOT_xbar2_DOT_arSel_s1_0_DOT_old_DOT_2399 = npc_DOT_xbar2_DOT_arSel_s1_0;
        npc_DOT_xbar2_DOT_arSel_s1_0 = npc_DOT_xbar2_DOT__arSel_0_T_4;
        bool cond_npc_DOT_xbar2_DOT_arSel_s1_0 =
            npc_DOT_xbar2_DOT_arSel_s1_0 ^ npc_DOT_xbar2_DOT_arSel_s1_0_DOT_old_DOT_2399;
        activeFlags[0] |= cond_npc_DOT_xbar2_DOT_arSel_s1_0 << 2; // 2
      } else {
      }
      uint8_t npc_DOT_xbar2_DOT__arSel_1_T_6_DOT_old_DOT_1877 = npc_DOT_xbar2_DOT__arSel_1_T_6;
      npc_DOT_xbar2_DOT__arSel_1_T_6 = (npc_DOT_xbar_DOT__io_out_ar_valid_T_1 & npc_DOT_xbar2_DOT__arSel_1_T_5);
      bool cond_npc_DOT_xbar2_DOT__arSel_1_T_6 =
          npc_DOT_xbar2_DOT__arSel_1_T_6 ^ npc_DOT_xbar2_DOT__arSel_1_T_6_DOT_old_DOT_1877;
      activeFlags[3] |= cond_npc_DOT_xbar2_DOT__arSel_1_T_6 << 4; // 28
      if (npc_DOT_xbar_DOT__io_out_ar_valid_T_1) {
        npc_DOT_xbar2_DOT__arSelIdx_T =
            ((npc_DOT_xbar2_DOT__arSel_1_T_6 << 1) | (uint8_t)npc_DOT_xbar2_DOT__arSel_0_T_4);
        uint8_t npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1_DOT_old_DOT_2400 = npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1;
        npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1 = npc_DOT_xbar2_DOT__arSel_1_T_6;
        bool cond_npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1 =
            npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1 ^ npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1_DOT_old_DOT_2400;
        activeFlags[5] |= cond_npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1 << 7; // 47
        npc_DOT_xbar2_DOT_arSelIdx = ((npc_DOT_xbar2_DOT__arSelIdx_T >> 1) & 0x1);
        uint8_t npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT_DOT_old_DOT_1887 = npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT;
        npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT = npc_DOT_xbar2_DOT_arSelIdx;
        bool cond_npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT =
            npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT ^ npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT_DOT_old_DOT_1887;
        activeFlags[5] |= cond_npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT << 7; // 47
      } else {
      }
      uint8_t npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1_DOT_old_DOT_1927 = npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1;
      npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1 =
          (npc_DOT_xbar2_DOT__io_out_1_ar_valid_T & npc_DOT_xbar2_DOT__arSel_1_T_6);
      bool cond_npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1 =
          npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1 ^ npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1_DOT_old_DOT_1927;
      *(uint64_t *)&activeFlags[0] |=
          -(uint64_t)cond_npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1 & 0x980000000; // 35 32 31
      if (npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1) {
        npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size = npc_DOT_lsu_DOT__sbufReq_wmask_T;
        npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size[0] =
            npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size;
        npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size[1] = 0x2;
        npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size =
            npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size
                [npc_DOT_xbar_DOT_chosenReadIdxReg_s0];
        uint8_t mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT_DOT_old_DOT_2165 =
            mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT;
        mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT =
            npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size;
        bool cond_mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT =
            mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT != mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT_DOT_old_DOT_2165;
        activeFlags[5] |= cond_mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT << 7; // 47
      } else {
      }
      mem_DOT_axi4memctrl_DOT__io_dmem_ren_T_1 =
          (npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1 | mem_DOT_axi4memctrl_DOT__io_dmem_ren_T);
      uint8_t mem_DOT_dmem_DOT_ren_DOT_old_DOT_2262 = mem_DOT_dmem_DOT_ren;
      mem_DOT_dmem_DOT_ren = mem_DOT_axi4memctrl_DOT__io_dmem_ren_T_1;
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_icache_DOT__beatAddr_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__beatAddr_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT__acceptRead_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__acceptRead_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT__io_out_ar_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__io_out_ar_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__io_out_1_ar_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_out_1_ar_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 mem_DOT_axi4memctrl_DOT__io_dmem_ren_T: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_dmem_ren_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT__io_out_ar_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__io_out_ar_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT_acceptRead: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_acceptRead);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT_chosenReadIdxReg_s0: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_chosenReadIdxReg_s0);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_icache_DOT_beatAddr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_beatAddr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_icache_DOT__io_mem_ar_bits_addr_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_bits_addr_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__arSel_0_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__arSel_0_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_in_ar_bits_s1_DOT__DOT_addr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__arSel_0_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__arSel_0_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__arSel_0_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__arSel_0_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__arSel_0_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__arSel_0_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__arSel_1_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__arSel_1_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT_arSel_s1_0: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSel_s1_0);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__arSel_1_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__arSel_1_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__arSelIdx_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__arSelIdx_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 mem_DOT_axi4memctrl_DOT__io_dmem_ren_T_1: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_dmem_ren_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 mem_DOT_dmem_DOT_ren: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_dmem_DOT_ren);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_size);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT_arSelIdx: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSelIdx);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 18 npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x8)) { // id=19
      uint8_t npc_DOT_lsu_DOT__state_T_2 = 0;
      uint8_t npc_DOT_lsu_DOT__state_T_3 = 0;
      uint8_t npc_DOT_lsu_DOT__state_T_4 = 0;
      uint32_t npc_DOT_icache_DOT__s0_out_bits_req_addr_T = 0;
      uint8_t npc_DOT_icache_DOT__s1_ok_T = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_ready_T = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_ready_T_1 = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_ready_T_3 = 0;
      uint8_t npc_DOT_xbar_DOT__io_in_ar_ready_T = 0;
      uint8_t npc_DOT_xbar_DOT__io_in_ar_ready_T_1 = 0;
      uint8_t npc_DOT_lsu_DOT__state_T = 0;
      uint8_t npc_DOT_lsu_DOT__state_T_6 = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_ready_T_2 = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_ready_T_4 = 0;
      uint8_t npc_DOT_icache_DOT__s0_out_bits_hit_T = 0;
      uint8_t npc_DOT_icache_DOT__s0_out_bits_mmio_T = 0;
      uint32_t npc_DOT_icache_DOT__s0_out_bits_mmio_T_2 = 0;
      uint8_t npc_DOT_icache_DOT__s0_out_bits_mmio_T_3 = 0;
      uint8_t npc_DOT_icache_DOT__s0_out_bits_mmio_T_4 = 0;
      uint8_t npc_DOT_icache_DOT__s0_out_bits_mmio_T_5 = 0;
      uint32_t npc_DOT_icache_DOT__s0_out_bits_req_addr_T_1 = 0;
      uint32_t npc_DOT_icache_DOT__s0_out_bits_hit_T_5 = 0;
      uint8_t npc_DOT_icache_DOT__s0_out_bits_hit_T_6 = 0;
      uint8_t npc_DOT_icache_DOT__s0_out_bits_hit_T_7 = 0;
      uint8_t npc_DOT_lsu_DOT__state_T_7 = 0;
      uint8_t npc_DOT_lsu_DOT__state_T_8 = 0;
      uint8_t npc_DOT_lsu_DOT__state_T_9 = 0;
      uint8_t npc_DOT_lsu_DOT__state_T_12 = 0;
      npc_DOT_lsu_DOT__state_T_2 = ((-(uint8_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[0] & 0x2) |
                                    ((-(uint8_t)!npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[0]) & 0x1));
      npc_DOT_lsu_DOT__state_T_3 = (0x0 == npc_DOT_lsu_DOT_state);
      npc_DOT_lsu_DOT__state_T_4 = (0x1 == npc_DOT_lsu_DOT_state);
      npc_DOT_icache_DOT__s0_out_bits_req_addr_T = ((npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1 >> 2) & 0x3fffffff);
      npc_DOT_icache_DOT__s1_ok_T = (npc_DOT_icache_DOT_state == 0x1);
      npc_DOT_icache_DOT__s1_in_ready_T = (npc_DOT_icache_DOT_s1_in_valid_REG == 0x0);
      npc_DOT_icache_DOT__s1_in_ready_T_1 = (npc_DOT_icache_DOT_state == 0x0);
      npc_DOT_icache_DOT__s1_in_ready_T_3 = (npc_DOT_deq_q_DOT__empty_T & npc_DOT_icache_DOT_s1_in_valid_REG);
      npc_DOT_xbar_DOT__io_in_ar_ready_T = (npc_DOT_xbar_DOT_stateRead != 0x2);
      npc_DOT_xbar_DOT__io_in_ar_ready_T_1 =
          (npc_DOT_xbar2_DOT__io_in_ar_ready_T_4 & npc_DOT_xbar_DOT__io_in_ar_ready_T);
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[0] = 0x0;
      activeFlags[3] |= 0x40; // 30
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[1] = 0x0;
      activeFlags[3] |= 0x40; // 30
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[npc_DOT_xbar_DOT_chosenReadIdxReg_s0] =
          npc_DOT_xbar_DOT__io_in_ar_ready_T_1;
      activeFlags[3] |= 0x40; // 30
      npc_DOT_lsu_DOT__state_T =
          (npc_DOT_lsu_DOT_isValidLoad & npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[0]);
      npc_DOT_lsu_DOT__state_T_6 = ((uint8_t)npc_DOT_lsu_DOT__state_T & 0x1);
      npc_DOT_icache_DOT__s1_in_ready_T_2 = (npc_DOT_icache_DOT__s1_in_ready_T & npc_DOT_icache_DOT__s1_in_ready_T_1);
      uint8_t npc_DOT_icache_DOT_s1_ok_DOT_old_DOT_1565 = npc_DOT_icache_DOT_s1_ok;
      npc_DOT_icache_DOT_s1_ok = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit | npc_DOT_icache_DOT__s1_ok_T);
      bool cond_npc_DOT_icache_DOT_s1_ok = npc_DOT_icache_DOT_s1_ok ^ npc_DOT_icache_DOT_s1_ok_DOT_old_DOT_1565;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT_s1_ok & 0x10; // 20
      npc_DOT_icache_DOT__s1_in_ready_T_4 = (npc_DOT_icache_DOT__s1_in_ready_T_3 & npc_DOT_icache_DOT_s1_ok);
      uint8_t npc_DOT_icache_DOT__s1_in_ready_T_5_DOT_old_DOT_1574 = npc_DOT_icache_DOT__s1_in_ready_T_5;
      npc_DOT_icache_DOT__s1_in_ready_T_5 = (npc_DOT_icache_DOT__s1_in_ready_T_2 | npc_DOT_icache_DOT__s1_in_ready_T_4);
      bool cond_npc_DOT_icache_DOT__s1_in_ready_T_5 =
          npc_DOT_icache_DOT__s1_in_ready_T_5 ^ npc_DOT_icache_DOT__s1_in_ready_T_5_DOT_old_DOT_1574;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT__s1_in_ready_T_5 & 0x10; // 20
      if (npc_DOT_icache_DOT__s1_in_ready_T_5) {
        npc_DOT_icache_DOT__s0_out_bits_hit_T =
            (((uint8_t)npc_DOT_icache_DOT_valid >> npc_DOT_icache_DOT__idx_s0_T_2) & 0x1);
        npc_DOT_icache_DOT__s0_out_bits_mmio_T = ((npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1 >> 31) & 0x1);
        npc_DOT_icache_DOT__s0_out_bits_mmio_T_2 = (npc_DOT_ifu_DOT__io_mem_req_bits_addr_T_1 & 0xf0000000);
        npc_DOT_icache_DOT__s0_out_bits_mmio_T_3 = (npc_DOT_icache_DOT__s0_out_bits_mmio_T_2 == 0x30000000);
        npc_DOT_icache_DOT__s0_out_bits_mmio_T_4 =
            (npc_DOT_icache_DOT__s0_out_bits_mmio_T | npc_DOT_icache_DOT__s0_out_bits_mmio_T_3);
        npc_DOT_icache_DOT__s0_out_bits_mmio_T_5 = (npc_DOT_icache_DOT__s0_out_bits_mmio_T_4 == 0x0);
        uint8_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT_DOT_old_DOT_1352 =
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT;
        npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT = npc_DOT_icache_DOT__s0_out_bits_mmio_T_5;
        bool cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT =
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT ^
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT_DOT_old_DOT_1352;
        activeFlags[4] |= cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT << 4; // 36
      } else {
      }
      npc_DOT_icache_DOT__s0_out_bits_req_addr_T_1 = (npc_DOT_icache_DOT__s0_out_bits_req_addr_T << 2);
      if (npc_DOT_icache_DOT__s1_in_ready_T_5) {
        npc_DOT_icache_DOT__s0_out_bits_hit_T_5 = ((npc_DOT_icache_DOT__s0_out_bits_req_addr_T_1 >> 6) & 0x3ffffff);
        uint32_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr_DOT_old_DOT_1341 =
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr;
        npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr = npc_DOT_icache_DOT__s0_out_bits_req_addr_T_1;
        bool cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr =
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr !=
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr_DOT_old_DOT_1341;
        activeFlags[2] |= -(uint8_t)cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr & 0x6; // 17 18
        npc_DOT_icache_DOT__s0_out_bits_hit_T_6 =
            (npc_DOT_icache_DOT__s0_out_bits_hit_T_5 == npc_DOT_icache_DOT_s0_out_bits_tagRead_MPORT);
        npc_DOT_icache_DOT__s0_out_bits_hit_T_7 =
            (npc_DOT_icache_DOT__s0_out_bits_hit_T & npc_DOT_icache_DOT__s0_out_bits_hit_T_6);
        uint8_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT_DOT_old_DOT_1347 =
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT;
        npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT = npc_DOT_icache_DOT__s0_out_bits_hit_T_7;
        bool cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT =
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT ^
            npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT_DOT_old_DOT_1347;
        activeFlags[4] |= cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT << 4; // 36
      } else {
      }
      npc_DOT_lsu_DOT__state_T_7 = (npc_DOT_lsu_DOT__state_T_3 & npc_DOT_lsu_DOT__state_T_6);
      npc_DOT_lsu_DOT__state_T_8 = ((uint8_t)npc_DOT_lsu_DOT__state_T_2 & 0x3);
      npc_DOT_lsu_DOT__state_T_9 = ((-(uint8_t)npc_DOT_lsu_DOT__state_T_4 & npc_DOT_lsu_DOT__state_T_8) |
                                    ((-(uint8_t)!npc_DOT_lsu_DOT__state_T_4) & 0x0));
      npc_DOT_lsu_DOT__state_T_12 = (npc_DOT_lsu_DOT__state_T_7 | npc_DOT_lsu_DOT__state_T_9);
      uint8_t npc_DOT_lsu_DOT_state_DOT_NEXT_DOT_old_DOT_673 = npc_DOT_lsu_DOT_state_DOT_NEXT;
      npc_DOT_lsu_DOT_state_DOT_NEXT = npc_DOT_lsu_DOT__state_T_12;
      bool cond_npc_DOT_lsu_DOT_state_DOT_NEXT =
          npc_DOT_lsu_DOT_state_DOT_NEXT != npc_DOT_lsu_DOT_state_DOT_NEXT_DOT_old_DOT_673;
      activeFlags[4] |= cond_npc_DOT_lsu_DOT_state_DOT_NEXT << 4; // 36
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_req_addr_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_req_addr_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s1_ok_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_ok_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s1_in_ready_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_ready_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s1_in_ready_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_ready_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s1_in_ready_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_ready_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_xbar_DOT__io_in_ar_ready_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__io_in_ar_ready_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_xbar_DOT__io_in_ar_ready_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__io_in_ar_ready_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s1_in_ready_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_ready_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT_s1_ok: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_ok);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s1_in_ready_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_ready_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s1_in_ready_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_ready_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_hit_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_hit_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_mmio_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_mmio_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_mmio_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_mmio_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_mmio_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_mmio_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_mmio_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_mmio_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_mmio_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_mmio_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_req_addr_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_req_addr_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_hit_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_hit_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_req_DOT__DOT_addr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_hit_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_hit_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT__s0_out_bits_hit_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s0_out_bits_hit_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT__state_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__state_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 19 npc_DOT_lsu_DOT_state_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_state_DOT_NEXT);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x10)) { // id=20
      uint32_t npc_DOT_ifu_DOT__PC_T_1 = 0;
      uint8_t npc_DOT_deq_q_DOT__io_deq_valid_T = 0;
      uint8_t npc_DOT_icache_DOT_dataReadIdx = 0;
      uint8_t npc_DOT_icache_DOT__res_T = 0;
      uint8_t npc_DOT_icache_DOT__io_core_resp_valid_T = 0;
      uint8_t npc_DOT_icache_DOT__io_core_resp_valid_T_1 = 0;
      uint8_t npc_DOT_icache_DOT__io_core_req_ready_T = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_valid_T_1 = 0;
      uint8_t npc_DOT_icache_DOT__io_core_req_ready_T_1 = 0;
      uint8_t npc_DOT_icache_DOT__io_core_req_ready_T_2 = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_valid_T_2 = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_valid_T_3 = 0;
      uint8_t npc_DOT_icache_DOT__s1_in_valid_T_4 = 0;
      uint32_t npc_DOT_icache_DOT__res_T_2 = 0;
      uint32_t npc_DOT_icache_DOT__res_T_1 = 0;
      uint32_t npc_DOT_ifu_DOT__PC_T_3 = 0;
      uint32_t npc_DOT_ifu_DOT__PC_T_4 = 0;
      uint32_t npc_DOT_ifu_DOT__PC_T_5 = 0;
      uint32_t npc_DOT_ifu_DOT__PC_T_6 = 0;
      npc_DOT_ifu_DOT__PC_T_1 = ((npc_DOT_ifu_DOT_PC + 0x4) & 0xffffffff);
      npc_DOT_deq_q_DOT__io_deq_valid_T = (npc_DOT_deq_q_DOT__empty_T == 0x0);
      npc_DOT_icache_DOT_dataRead_s1[0] = npc_DOT_icache_DOT_dataRead_s1_MPORT;
      npc_DOT_icache_DOT_dataRead_s1[1] = npc_DOT_icache_DOT_dataRead_s1_MPORT_1;
      npc_DOT_icache_DOT_dataRead_s1[2] = npc_DOT_icache_DOT_dataRead_s1_MPORT_2;
      npc_DOT_icache_DOT_dataRead_s1[3] = npc_DOT_icache_DOT_dataRead_s1_MPORT_3;
      npc_DOT_icache_DOT_dataReadIdx =
          ((-(uint8_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit & npc_DOT_icache_DOT__wordIdx_s1_T_1) |
           ((-(uint8_t)!npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit) & npc_DOT_icache_DOT_beatCnt_value));
      npc_DOT_icache_DOT__res_T = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit == 0x0);
      npc_DOT_icache_DOT__io_core_resp_valid_T = (npc_DOT_icache_DOT_s1_in_valid_REG & npc_DOT_icache_DOT_s1_ok);
      npc_DOT_icache_DOT__io_core_resp_valid_T_1 = (npc_DOT_icache_DOT_flushReg == 0x0);
      npc_DOT_icache_DOT__io_core_req_ready_T = (npc_DOT_icache_DOT_state == 0x0);
      uint8_t npc_DOT_icache_DOT__io_core_resp_valid_T_2_DOT_old_DOT_1568 = npc_DOT_icache_DOT__io_core_resp_valid_T_2;
      npc_DOT_icache_DOT__io_core_resp_valid_T_2 =
          (npc_DOT_icache_DOT__io_core_resp_valid_T & npc_DOT_icache_DOT__io_core_resp_valid_T_1);
      bool cond_npc_DOT_icache_DOT__io_core_resp_valid_T_2 =
          npc_DOT_icache_DOT__io_core_resp_valid_T_2 ^ npc_DOT_icache_DOT__io_core_resp_valid_T_2_DOT_old_DOT_1568;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT__io_core_resp_valid_T_2 & 0x40; // 22
      npc_DOT_icache_DOT__s1_in_valid_T_1 = (npc_DOT_deq_q_DOT__empty_T & npc_DOT_icache_DOT__io_core_resp_valid_T_2);
      npc_DOT_icache_DOT__io_core_req_ready_T_1 =
          (npc_DOT_icache_DOT__io_core_req_ready_T | npc_DOT_icache_DOT__io_core_resp_valid_T_2);
      npc_DOT_icache_DOT__io_core_req_ready_T_2 =
          (npc_DOT_icache_DOT__s1_in_ready_T_5 & npc_DOT_icache_DOT__io_core_req_ready_T_1);
      npc_DOT_icache_DOT__s1_in_valid_T_2 =
          ((!npc_DOT_icache_DOT__s1_in_valid_T_1) & npc_DOT_icache_DOT_s1_in_valid_REG);
      npc_DOT_icache_DOT__s1_in_valid_T_3 = (npc_DOT_icache_DOT__s1_in_ready_T_5 | npc_DOT_icache_DOT__s1_in_valid_T_2);
      npc_DOT_icache_DOT__s1_in_valid_T_4 =
          ((!npc_DOT_lsu_DOT__io_redirect_valid_T_2) & npc_DOT_icache_DOT__s1_in_valid_T_3);
      uint8_t npc_DOT_icache_DOT_s1_in_valid_REG_DOT_old_DOT_1360 = npc_DOT_icache_DOT_s1_in_valid_REG;
      npc_DOT_icache_DOT_s1_in_valid_REG = npc_DOT_icache_DOT__s1_in_valid_T_4;
      bool cond_npc_DOT_icache_DOT_s1_in_valid_REG =
          npc_DOT_icache_DOT_s1_in_valid_REG ^ npc_DOT_icache_DOT_s1_in_valid_REG_DOT_old_DOT_1360;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_s1_in_valid_REG & 0x181000; // 20 19 12
      npc_DOT_icache_DOT__res_T_2 = ((-(uint32_t)npc_DOT_icache_DOT__res_T & npc_DOT_icache_DOT_resFromMem) |
                                     ((-(uint32_t)!npc_DOT_icache_DOT__res_T) & 0x0));
      npc_DOT_icache_DOT__res_T_1 = ((-(uint32_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit &
                                      npc_DOT_icache_DOT_dataRead_s1[npc_DOT_icache_DOT_dataReadIdx]) |
                                     ((-(uint32_t)!npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit) & 0x0));
      uint32_t npc_DOT_icache_DOT__res_T_3_DOT_old_DOT_1498 = npc_DOT_icache_DOT__res_T_3;
      npc_DOT_icache_DOT__res_T_3 = (npc_DOT_icache_DOT__res_T_1 | npc_DOT_icache_DOT__res_T_2);
      bool cond_npc_DOT_icache_DOT__res_T_3 =
          npc_DOT_icache_DOT__res_T_3 != npc_DOT_icache_DOT__res_T_3_DOT_old_DOT_1498;
      oldFlag |= -(uint8_t)cond_npc_DOT_icache_DOT__res_T_3 & 0x40; // 22
      uint8_t npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid_DOT_old_DOT_994 =
          npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid;
      npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid =
          (npc_DOT_icache_DOT__io_core_resp_valid_T_2 | npc_DOT_deq_q_DOT__io_deq_valid_T);
      bool cond_npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid =
          npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid ^
          npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid_DOT_old_DOT_994;
      oldFlag |= -(uint8_t)cond_npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid & 0x40; // 22
      npc_DOT_ifu_DOT__PC_T_3 = ((-(uint32_t)npc_DOT_icache_DOT__io_core_req_ready_T_2 & npc_DOT_ifu_DOT__PC_T_1) |
                                 ((-(uint32_t)!npc_DOT_icache_DOT__io_core_req_ready_T_2) & npc_DOT_ifu_DOT_PC));
      npc_DOT_ifu_DOT__PC_T_4 =
          ((-(uint32_t)npc_DOT_lsu_DOT__io_redirect_valid_T_2 & npc_DOT_lsu_DOT__io_redirect_dnpc_T_1) |
           ((-(uint32_t)!npc_DOT_lsu_DOT__io_redirect_valid_T_2) & npc_DOT_ifu_DOT__PC_T_3));
      npc_DOT_ifu_DOT__PC_T_5 = ((npc_DOT_ifu_DOT__PC_T_4 >> 2) & 0x3fffffff);
      npc_DOT_ifu_DOT__PC_T_6 = (npc_DOT_ifu_DOT__PC_T_5 << 2);
      uint32_t npc_DOT_ifu_DOT_PC_DOT_old_DOT_54 = npc_DOT_ifu_DOT_PC;
      npc_DOT_ifu_DOT_PC = npc_DOT_ifu_DOT__PC_T_6;
      bool cond_npc_DOT_ifu_DOT_PC = npc_DOT_ifu_DOT_PC != npc_DOT_ifu_DOT_PC_DOT_old_DOT_54;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_ifu_DOT_PC & 0x100008; // 20 3
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_ifu_DOT__PC_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_ifu_DOT__PC_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_deq_q_DOT__io_deq_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT__io_deq_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT_dataRead_s1: ", cycles);
        for (int i0 = 0; i0 < 4; i0++) {
          printf("%lx", (uint64_t)npc_DOT_icache_DOT_dataRead_s1[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT_dataReadIdx: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_dataReadIdx);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT_resFromMem: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_resFromMem);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__res_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__res_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__io_core_resp_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_core_resp_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__io_core_resp_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_core_resp_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__io_core_req_ready_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_core_req_ready_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__io_core_resp_valid_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_core_resp_valid_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__s1_in_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__io_core_req_ready_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_core_req_ready_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__io_core_req_ready_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_core_req_ready_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__s1_in_valid_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_valid_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__s1_in_valid_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_valid_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__s1_in_valid_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__s1_in_valid_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT_s1_in_valid_REG: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_valid_REG);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__res_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__res_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__res_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__res_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_icache_DOT__res_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__res_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_ifu_DOT__PC_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_ifu_DOT__PC_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_ifu_DOT__PC_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_ifu_DOT__PC_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_ifu_DOT__PC_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_ifu_DOT__PC_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_ifu_DOT__PC_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_ifu_DOT__PC_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 20 npc_DOT_ifu_DOT_PC: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_ifu_DOT_PC);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x20)) { // id=21
      uint8_t npc_DOT_idu_DOT__rs1Ready_T = 0;
      uint8_t npc_DOT_idu_DOT__rs2Ready_T = 0;
      uint8_t npc_DOT_lsu_DOT__io_fw_notReady_T = 0;
      uint8_t npc_DOT_exu_DOT__io_fw_notReady_T = 0;
      uint8_t npc_DOT_exu_DOT__io_fw_notReady_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__T = 0;
      uint8_t npc_DOT_idu_DOT__T_1 = 0;
      uint8_t npc_DOT_exu_DOT__io_fw_wen_T = 0;
      uint8_t npc_DOT_lsu_DOT__io_fw_notReady_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__T_8 = 0;
      uint8_t npc_DOT_idu_DOT__T_12 = 0;
      uint8_t npc_DOT_idu_DOT__T_13 = 0;
      uint8_t npc_DOT_idu_DOT_rs2ReadyTmp = 0;
      uint8_t npc_DOT_idu_DOT__T_9 = 0;
      uint8_t npc_DOT_idu_DOT_rs1ReadyTmp = 0;
      uint8_t npc_DOT_idu_DOT__rs2Ready_T_1 = 0;
      uint8_t npc_DOT_idu_DOT_rs2Ready = 0;
      uint8_t npc_DOT_idu_DOT_rs1Ready = 0;
      npc_DOT_idu_DOT__rs1Ready_T = (npc_DOT_idu_DOT_src1UseReg == 0x0);
      npc_DOT_idu_DOT__rs2Ready_T = (npc_DOT_idu_DOT_src2UseReg | npc_DOT_idu_DOT_isStype);
      npc_DOT_lsu_DOT__io_fw_notReady_T = (npc_DOT_lsu_DOT_memFinish == 0x0);
      npc_DOT_exu_DOT__io_fw_notReady_T = (npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad |
                                           npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR);
      npc_DOT_exu_DOT__io_fw_notReady_T_1 =
          (npc_DOT_exu_DOT__io_fw_notReady_T | npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp);
      npc_DOT_idu_DOT__T = (npc_DOT_idu_DOT__rs1_T_1 == npc_DOT_exu_io_in_bits_r_DOT__DOT_rd);
      npc_DOT_idu_DOT__T_1 = (npc_DOT_idu_DOT__rs2_T_1 == npc_DOT_exu_io_in_bits_r_DOT__DOT_rd);
      npc_DOT_exu_DOT__io_fw_wen_T = (npc_DOT_exu_io_in_valid_REG & npc_DOT_exu_io_in_bits_r_DOT__DOT_wen);
      uint8_t npc_DOT_idu_DOT_exCanFwRs1_DOT_old_DOT_342 = npc_DOT_idu_DOT_exCanFwRs1;
      npc_DOT_idu_DOT_exCanFwRs1 = (npc_DOT_exu_DOT__io_fw_wen_T & npc_DOT_idu_DOT__T);
      bool cond_npc_DOT_idu_DOT_exCanFwRs1 = npc_DOT_idu_DOT_exCanFwRs1 ^ npc_DOT_idu_DOT_exCanFwRs1_DOT_old_DOT_342;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_exCanFwRs1 << 2; // 26
      uint8_t npc_DOT_idu_DOT_exCanFwRs2_DOT_old_DOT_344 = npc_DOT_idu_DOT_exCanFwRs2;
      npc_DOT_idu_DOT_exCanFwRs2 = (npc_DOT_exu_DOT__io_fw_wen_T & npc_DOT_idu_DOT__T_1);
      bool cond_npc_DOT_idu_DOT_exCanFwRs2 = npc_DOT_idu_DOT_exCanFwRs2 ^ npc_DOT_idu_DOT_exCanFwRs2_DOT_old_DOT_344;
      activeFlags[3] |= cond_npc_DOT_idu_DOT_exCanFwRs2 << 2; // 26
      uint32_t npc_DOT_exu_DOT_xor_DOT_old_DOT_527 = npc_DOT_exu_DOT_xor;
      npc_DOT_exu_DOT_xor = (npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 ^ npc_DOT_exu_io_in_bits_r_DOT__DOT_src2);
      bool cond_npc_DOT_exu_DOT_xor = npc_DOT_exu_DOT_xor != npc_DOT_exu_DOT_xor_DOT_old_DOT_527;
      oldFlag |= -(uint8_t)cond_npc_DOT_exu_DOT_xor & 0x80;       // 23
      activeFlags[3] |= -(uint8_t)cond_npc_DOT_exu_DOT_xor & 0x3; // 24 25
      npc_DOT_lsu_DOT__io_fw_notReady_T_1 =
          (npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad & npc_DOT_lsu_DOT__io_fw_notReady_T);
      npc_DOT_idu_DOT__T_8 = (npc_DOT_idu_DOT_lsCanFwRs1 & npc_DOT_lsu_DOT__io_fw_notReady_T_1);
      npc_DOT_idu_DOT__T_12 = (npc_DOT_idu_DOT_lsCanFwRs2 & npc_DOT_lsu_DOT__io_fw_notReady_T_1);
      npc_DOT_idu_DOT__T_13 = ((npc_DOT_idu_DOT_exCanFwRs2 & npc_DOT_exu_DOT__io_fw_notReady_T_1) |
                               ((!npc_DOT_idu_DOT_exCanFwRs2) & npc_DOT_idu_DOT__T_12));
      npc_DOT_idu_DOT_rs2ReadyTmp = (npc_DOT_idu_DOT__T_13 == 0x0);
      npc_DOT_idu_DOT__T_9 = ((npc_DOT_idu_DOT_exCanFwRs1 & npc_DOT_exu_DOT__io_fw_notReady_T_1) |
                              ((!npc_DOT_idu_DOT_exCanFwRs1) & npc_DOT_idu_DOT__T_8));
      npc_DOT_idu_DOT_rs1ReadyTmp = (npc_DOT_idu_DOT__T_9 == 0x0);
      npc_DOT_idu_DOT__rs2Ready_T_1 = (npc_DOT_idu_DOT__rs2Ready_T == 0x0);
      npc_DOT_idu_DOT_rs2Ready = (npc_DOT_idu_DOT_rs2ReadyTmp | npc_DOT_idu_DOT__rs2Ready_T_1);
      npc_DOT_idu_DOT_rs1Ready = (npc_DOT_idu_DOT_rs1ReadyTmp | npc_DOT_idu_DOT__rs1Ready_T);
      uint8_t npc_DOT_idu_DOT_canIssue_DOT_old_DOT_372 = npc_DOT_idu_DOT_canIssue;
      npc_DOT_idu_DOT_canIssue = (npc_DOT_idu_DOT_rs1Ready & npc_DOT_idu_DOT_rs2Ready);
      bool cond_npc_DOT_idu_DOT_canIssue = npc_DOT_idu_DOT_canIssue ^ npc_DOT_idu_DOT_canIssue_DOT_old_DOT_372;
      oldFlag |= -(uint8_t)cond_npc_DOT_idu_DOT_canIssue & 0x40; // 22
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__rs1Ready_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__rs1Ready_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__rs2Ready_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__rs2Ready_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_lsu_DOT__io_fw_notReady_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_fw_notReady_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_io_in_bits_r_DOT__DOT_src1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_io_in_bits_r_DOT__DOT_src2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_io_in_bits_r_DOT__DOT_wen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_wen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_io_in_bits_r_DOT__DOT_rd: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_rd);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_DOT__io_fw_notReady_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_fw_notReady_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_DOT__io_fw_notReady_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_fw_notReady_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_DOT__io_fw_wen_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_fw_wen_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT_exCanFwRs1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_exCanFwRs1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT_exCanFwRs2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_exCanFwRs2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_exu_DOT_xor: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_xor);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_lsu_DOT__io_fw_notReady_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_fw_notReady_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT_rs2ReadyTmp: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_rs2ReadyTmp);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT_rs1ReadyTmp: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_rs1ReadyTmp);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT__rs2Ready_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__rs2Ready_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT_rs2Ready: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_rs2Ready);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT_rs1Ready: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_rs1Ready);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 21 npc_DOT_idu_DOT_canIssue: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_canIssue);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x40)) { // id=22
      uint8_t npc_DOT_idu_DOT__io_in_ready_T = 0;
      uint8_t npc_DOT_idu_DOT__io_in_ready_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_valid_T = 0;
      uint8_t npc_DOT_deq_q_DOT__do_enq_T = 0;
      uint8_t npc_DOT__exu_io_in_valid_T_1 = 0;
      uint8_t npc_DOT__exu_io_in_valid_T_2 = 0;
      uint8_t npc_DOT__idu_io_in_valid_T_1 = 0;
      uint8_t npc_DOT__exu_io_in_valid_T_3 = 0;
      uint8_t npc_DOT__exu_io_in_valid_T_4 = 0;
      uint8_t npc_DOT__idu_io_in_valid_T_2 = 0;
      uint8_t npc_DOT_idu_DOT__io_in_ready_T_2 = 0;
      uint8_t npc_DOT_deq_q_DOT_do_enq = 0;
      uint8_t npc_DOT_deq_q_DOT__do_deq_T = 0;
      uint8_t npc_DOT__idu_io_in_valid_T = 0;
      uint32_t npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_pc = 0;
      uint32_t npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_inst = 0;
      uint8_t npc_DOT__idu_io_in_valid_T_3 = 0;
      uint8_t npc_DOT__idu_io_in_valid_T_4 = 0;
      uint8_t npc_DOT_deq_q_DOT_do_deq = 0;
      uint8_t npc_DOT_deq_q_DOT__T = 0;
      npc_DOT_idu_DOT__io_in_ready_T = (npc_DOT_lsu_DOT__io_in_ready_T_1 & npc_DOT_idu_DOT_canIssue);
      npc_DOT_idu_DOT__io_in_ready_T_1 = (npc_DOT_idu_io_in_valid_REG == 0x0);
      npc_DOT_idu_DOT__io_out_valid_T = (npc_DOT_idu_io_in_valid_REG & npc_DOT_idu_DOT_canIssue);
      npc_DOT_deq_q_DOT__do_enq_T = (npc_DOT_deq_q_DOT__empty_T & npc_DOT_icache_DOT__io_core_resp_valid_T_2);
      npc_DOT__exu_io_in_valid_T_1 = (npc_DOT_lsu_DOT__io_in_ready_T_1 & npc_DOT_exu_io_in_valid_REG);
      npc_DOT__exu_io_in_valid_T_2 = ((!npc_DOT__exu_io_in_valid_T_1) & npc_DOT_exu_io_in_valid_REG);
      npc_DOT__idu_io_in_valid_T_1 = (npc_DOT_lsu_DOT__io_in_ready_T_1 & npc_DOT_idu_DOT__io_out_valid_T);
      uint8_t npc_DOT__exu_io_in_valid_T_DOT_old_DOT_1103 = npc_DOT__exu_io_in_valid_T;
      npc_DOT__exu_io_in_valid_T = (npc_DOT_idu_DOT__io_out_valid_T & npc_DOT_lsu_DOT__io_in_ready_T_1);
      bool cond_npc_DOT__exu_io_in_valid_T = npc_DOT__exu_io_in_valid_T ^ npc_DOT__exu_io_in_valid_T_DOT_old_DOT_1103;
      activeFlags[3] |= cond_npc_DOT__exu_io_in_valid_T << 2; // 26
      npc_DOT__exu_io_in_valid_T_3 = (npc_DOT__exu_io_in_valid_T | npc_DOT__exu_io_in_valid_T_2);
      npc_DOT__exu_io_in_valid_T_4 = ((!npc_DOT_lsu_DOT__io_redirect_valid_T_2) & npc_DOT__exu_io_in_valid_T_3);
      uint8_t npc_DOT_exu_io_in_valid_REG_DOT_NEXT_DOT_old_DOT_1109 = npc_DOT_exu_io_in_valid_REG_DOT_NEXT;
      npc_DOT_exu_io_in_valid_REG_DOT_NEXT = npc_DOT__exu_io_in_valid_T_4;
      bool cond_npc_DOT_exu_io_in_valid_REG_DOT_NEXT =
          npc_DOT_exu_io_in_valid_REG_DOT_NEXT ^ npc_DOT_exu_io_in_valid_REG_DOT_NEXT_DOT_old_DOT_1109;
      activeFlags[5] |= cond_npc_DOT_exu_io_in_valid_REG_DOT_NEXT << 2; // 42
      npc_DOT__idu_io_in_valid_T_2 = ((!npc_DOT__idu_io_in_valid_T_1) & npc_DOT_idu_io_in_valid_REG);
      npc_DOT_idu_DOT__io_in_ready_T_2 = (npc_DOT_idu_DOT__io_in_ready_T | npc_DOT_idu_DOT__io_in_ready_T_1);
      if (npc_DOT_deq_q_DOT__empty_T) {
        if (npc_DOT_idu_DOT__io_in_ready_T_2) {
          npc_DOT_deq_q_DOT_do_enq = 0x0;
        } else {
          npc_DOT_deq_q_DOT_do_enq = npc_DOT_deq_q_DOT__do_enq_T;
        }
      } else {
        npc_DOT_deq_q_DOT_do_enq = npc_DOT_deq_q_DOT__do_enq_T;
      }
      if (npc_DOT_lsu_DOT__io_redirect_valid_T_2) {
        uint8_t npc_DOT_deq_q_DOT_maybe_full_DOT_old_DOT_1004 = npc_DOT_deq_q_DOT_maybe_full;
        npc_DOT_deq_q_DOT_maybe_full = 0x0;
        bool cond_npc_DOT_deq_q_DOT_maybe_full =
            npc_DOT_deq_q_DOT_maybe_full ^ npc_DOT_deq_q_DOT_maybe_full_DOT_old_DOT_1004;
        activeFlags[0] |= cond_npc_DOT_deq_q_DOT_maybe_full << 3; // 3
      } else {
        npc_DOT_deq_q_DOT__do_deq_T =
            (npc_DOT_idu_DOT__io_in_ready_T_2 & npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid);
        npc_DOT_deq_q_DOT_do_deq = ((!npc_DOT_deq_q_DOT__empty_T) & npc_DOT_deq_q_DOT__do_deq_T);
        npc_DOT_deq_q_DOT__T = (npc_DOT_deq_q_DOT_do_enq != npc_DOT_deq_q_DOT_do_deq);
        if (npc_DOT_deq_q_DOT__T) {
          uint8_t npc_DOT_deq_q_DOT_maybe_full_DOT_old_DOT_1004 = npc_DOT_deq_q_DOT_maybe_full;
          npc_DOT_deq_q_DOT_maybe_full = npc_DOT_deq_q_DOT_do_enq;
          bool cond_npc_DOT_deq_q_DOT_maybe_full =
              npc_DOT_deq_q_DOT_maybe_full ^ npc_DOT_deq_q_DOT_maybe_full_DOT_old_DOT_1004;
          activeFlags[0] |= cond_npc_DOT_deq_q_DOT_maybe_full << 3; // 3
        } else {
        }
      }
      npc_DOT__idu_io_in_valid_T =
          (npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_valid & npc_DOT_idu_DOT__io_in_ready_T_2);
      if (npc_DOT__idu_io_in_valid_T) {
        npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_pc =
            ((-(uint32_t)npc_DOT_deq_q_DOT__empty_T & npc_DOT_ifu_DOT_pc_s2) |
             ((-(uint32_t)!npc_DOT_deq_q_DOT__empty_T) & npc_DOT_deq_q_DOT_ram_DOT__DOT_pc));
        npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_inst =
            ((-(uint32_t)npc_DOT_deq_q_DOT__empty_T & npc_DOT_icache_DOT__res_T_3) |
             ((-(uint32_t)!npc_DOT_deq_q_DOT__empty_T) & npc_DOT_deq_q_DOT_ram_DOT__DOT_inst));
        uint32_t npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT_DOT_old_DOT_1036 =
            npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT;
        npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT = npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_inst;
        bool cond_npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT =
            npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT !=
            npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT_DOT_old_DOT_1036;
        activeFlags[5] |= cond_npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT << 2; // 42
        uint32_t npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT_DOT_old_DOT_1035 =
            npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT;
        npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT = npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_pc;
        bool cond_npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT =
            npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT !=
            npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT_DOT_old_DOT_1035;
        activeFlags[5] |= cond_npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT << 2; // 42
      } else {
      }
      npc_DOT__idu_io_in_valid_T_3 = (npc_DOT__idu_io_in_valid_T | npc_DOT__idu_io_in_valid_T_2);
      npc_DOT__idu_io_in_valid_T_4 = ((!npc_DOT_lsu_DOT__io_redirect_valid_T_2) & npc_DOT__idu_io_in_valid_T_3);
      uint8_t npc_DOT_idu_io_in_valid_REG_DOT_NEXT_DOT_old_DOT_1044 = npc_DOT_idu_io_in_valid_REG_DOT_NEXT;
      npc_DOT_idu_io_in_valid_REG_DOT_NEXT = npc_DOT__idu_io_in_valid_T_4;
      bool cond_npc_DOT_idu_io_in_valid_REG_DOT_NEXT =
          npc_DOT_idu_io_in_valid_REG_DOT_NEXT ^ npc_DOT_idu_io_in_valid_REG_DOT_NEXT_DOT_old_DOT_1044;
      activeFlags[5] |= cond_npc_DOT_idu_io_in_valid_REG_DOT_NEXT << 2; // 42
      if (npc_DOT_deq_q_DOT_do_enq) {
        uint32_t npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT_DOT_old_DOT_2270 =
            npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT;
        npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT = npc_DOT_ifu_DOT_pc_s2;
        bool cond_npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT =
            npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT != npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT_DOT_old_DOT_2270;
        activeFlags[5] |= cond_npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT << 2; // 42
        uint32_t npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT_DOT_old_DOT_2272 =
            npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT;
        npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT = npc_DOT_icache_DOT__res_T_3;
        bool cond_npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT =
            npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT !=
            npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT_DOT_old_DOT_2272;
        activeFlags[5] |= cond_npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT << 2; // 42
      } else {
      }
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_idu_DOT__io_in_ready_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_in_ready_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_idu_DOT__io_in_ready_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_in_ready_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_idu_DOT__io_out_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT__do_enq_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT__do_enq_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__exu_io_in_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__exu_io_in_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_ram_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_ram_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_ram_DOT__DOT_inst: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_ram_DOT__DOT_inst);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__exu_io_in_valid_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__exu_io_in_valid_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__idu_io_in_valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__idu_io_in_valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__exu_io_in_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__exu_io_in_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__exu_io_in_valid_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__exu_io_in_valid_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__exu_io_in_valid_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__exu_io_in_valid_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_exu_io_in_valid_REG_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_valid_REG_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__idu_io_in_valid_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__idu_io_in_valid_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_idu_DOT__io_in_ready_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_in_ready_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_do_enq: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_do_enq);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT__do_deq_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT__do_deq_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__idu_io_in_valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__idu_io_in_valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_inst: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_io_DOT__DOT_deq_DOT__DOT_bits_DOT__DOT_inst);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__idu_io_in_valid_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__idu_io_in_valid_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT__idu_io_in_valid_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT__idu_io_in_valid_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_idu_io_in_valid_REG_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_io_in_valid_REG_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_do_deq: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_do_deq);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT__T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT__T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 22 npc_DOT_deq_q_DOT_maybe_full: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_maybe_full);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x80)) { // id=23
      uint32_t npc_DOT_exu_DOT__adderRes_T = 0;
      uint8_t npc_DOT_exu_DOT__slt_T = 0;
      uint8_t npc_DOT_exu_DOT_isSub = 0;
      uint32_t npc_DOT_exu_DOT__adderRes_T_1 = 0;
      uint64_t npc_DOT_exu_DOT__adderRes_T_2 = 0;
      uint64_t npc_DOT_exu_DOT__adderRes_T_3 = 0;
      uint8_t npc_DOT_exu_DOT_carry = 0;
      npc_DOT_exu_DOT__adderRes_T = (npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 ^ 0xffffffff);
      npc_DOT_exu_DOT__slt_T = ((npc_DOT_exu_DOT_xor >> 31) & 0x1);
      npc_DOT_exu_DOT_isSub = (npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd == 0x0);
      npc_DOT_exu_DOT__adderRes_T_1 = ((-(uint32_t)npc_DOT_exu_DOT_isSub & npc_DOT_exu_DOT__adderRes_T) |
                                       ((-(uint32_t)!npc_DOT_exu_DOT_isSub) & npc_DOT_exu_io_in_bits_r_DOT__DOT_src2));
      npc_DOT_exu_DOT__adderRes_T_2 =
          ((uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 + npc_DOT_exu_DOT__adderRes_T_1);
      npc_DOT_exu_DOT__adderRes_T_3 =
          ((npc_DOT_exu_DOT__adderRes_T_2 + ((uint64_t)npc_DOT_exu_DOT_isSub)) & 0x1ffffffff);
      npc_DOT_exu_DOT_carry = ((npc_DOT_exu_DOT__adderRes_T_3 >> 32) & 0x1);
      uint32_t npc_DOT_exu_DOT_sum_DOT_old_DOT_526 = npc_DOT_exu_DOT_sum;
      npc_DOT_exu_DOT_sum = (npc_DOT_exu_DOT__adderRes_T_3 & 0xffffffff);
      bool cond_npc_DOT_exu_DOT_sum = npc_DOT_exu_DOT_sum != npc_DOT_exu_DOT_sum_DOT_old_DOT_526;
      activeFlags[3] |= -(uint8_t)cond_npc_DOT_exu_DOT_sum & 0x3; // 24 25
      uint8_t npc_DOT_exu_DOT_sltu_DOT_old_DOT_528 = npc_DOT_exu_DOT_sltu;
      npc_DOT_exu_DOT_sltu = (npc_DOT_exu_DOT_carry ^ 0x1);
      bool cond_npc_DOT_exu_DOT_sltu = npc_DOT_exu_DOT_sltu ^ npc_DOT_exu_DOT_sltu_DOT_old_DOT_528;
      activeFlags[3] |= -(uint8_t)cond_npc_DOT_exu_DOT_sltu & 0x3; // 24 25
      uint8_t npc_DOT_exu_DOT_slt_DOT_old_DOT_530 = npc_DOT_exu_DOT_slt;
      npc_DOT_exu_DOT_slt = (npc_DOT_exu_DOT__slt_T ^ npc_DOT_exu_DOT_sltu);
      bool cond_npc_DOT_exu_DOT_slt = npc_DOT_exu_DOT_slt ^ npc_DOT_exu_DOT_slt_DOT_old_DOT_530;
      activeFlags[3] |= -(uint8_t)cond_npc_DOT_exu_DOT_slt & 0x3; // 24 25
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT__adderRes_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__adderRes_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT__slt_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__slt_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT_isSub: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_isSub);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT__adderRes_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__adderRes_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT__adderRes_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__adderRes_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT__adderRes_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__adderRes_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT_carry: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_carry);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT_sum: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_sum);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT_sltu: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_sltu);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 23 npc_DOT_exu_DOT_slt: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_slt);
        printf("\n");
      }
#endif
    }
  }
  if (unlikely(activeFlags[3] != 0)) {
    uint8_t oldFlag = activeFlags[3];
    activeFlags[3] = 0;
    if (unlikely(oldFlag & 0x1)) { // id=24
      uint32_t npc_DOT_exu_DOT__shiftRes_T_3 = 0;
      uint8_t npc_DOT_exu_DOT__shiftRes_T_4 = 0;
      uint8_t npc_DOT_exu_DOT__shiftRes_T_6 = 0;
      uint8_t npc_DOT_exu_DOT__shiftRes_T_12 = 0;
      uint8_t npc_DOT_exu_DOT__shiftRes_T_14 = 0;
      uint8_t npc_DOT_exu_DOT_aluOP = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_2 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_5 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_6 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_3 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_4 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_7 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_8 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_9 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_10 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_11 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_12 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_13 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_14 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_22 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_21 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_19 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_18 = 0;
      uint8_t npc_DOT_exu_DOT__aluOut_T_17 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_16 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_15 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_23 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_24 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_25 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_26 = 0;
      uint8_t npc_DOT_exu_DOT__shiftRes_T_15 = 0;
      uint32_t npc_DOT_exu_DOT__shiftRes_T_16 = 0;
      uint8_t npc_DOT_exu_DOT__shiftRes_T_7 = 0;
      uint32_t npc_DOT_exu_DOT__shiftRes_T_8 = 0;
      uint32_t npc_DOT_exu_DOT__shiftRes_T_9 = 0;
      uint32_t npc_DOT_exu_DOT_shiftRes = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_20 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_27 = 0;
      uint32_t npc_DOT_exu_DOT__aluOut_T_28 = 0;
      npc_DOT_exu_DOT__shiftRes_T_3 = ((int32_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src1);
      npc_DOT_exu_DOT__shiftRes_T_4 = ((npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 >> 4) & 0x1);
      npc_DOT_exu_DOT__shiftRes_T_6 = (npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 & 0xf);
      npc_DOT_exu_DOT__shiftRes_T_12 = ((npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 >> 4) & 0x1);
      npc_DOT_exu_DOT__shiftRes_T_14 = (npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 & 0xf);
      npc_DOT_exu_DOT_aluOP = ((-(uint8_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd & 0x0) |
                               ((-(uint8_t)!npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd) &
                                npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3));
      npc_DOT_exu_DOT__aluOut_T = ((npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 >> 4) & 0x1);
      npc_DOT_exu_DOT__aluOut_T_2 = (npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 & 0xf);
      npc_DOT_exu_DOT__aluOut_T_5 = (npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 | npc_DOT_exu_io_in_bits_r_DOT__DOT_src2);
      npc_DOT_exu_DOT__aluOut_T_6 = (npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 & npc_DOT_exu_io_in_bits_r_DOT__DOT_src2);
      npc_DOT_exu_DOT__aluOut_T_3 = ((npc_DOT_exu_DOT__aluOut_T << 4) | (uint8_t)npc_DOT_exu_DOT__aluOut_T_2);
      npc_DOT_exu_DOT__aluOut_T_4 =
          ((uint32_t)((uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 << npc_DOT_exu_DOT__aluOut_T_3) & 0xffffffff);
      npc_DOT_exu_DOT__aluOut_T_7 = (0x0 == npc_DOT_exu_DOT_aluOP);
      npc_DOT_exu_DOT__aluOut_T_8 = (0x1 == npc_DOT_exu_DOT_aluOP);
      npc_DOT_exu_DOT__aluOut_T_9 = (0x2 == npc_DOT_exu_DOT_aluOP);
      npc_DOT_exu_DOT__aluOut_T_10 = (0x3 == npc_DOT_exu_DOT_aluOP);
      npc_DOT_exu_DOT__aluOut_T_11 = (0x4 == npc_DOT_exu_DOT_aluOP);
      npc_DOT_exu_DOT__aluOut_T_12 = (0x5 == npc_DOT_exu_DOT_aluOP);
      npc_DOT_exu_DOT__aluOut_T_13 = (0x6 == npc_DOT_exu_DOT_aluOP);
      npc_DOT_exu_DOT__aluOut_T_14 = (0x7 == npc_DOT_exu_DOT_aluOP);
      npc_DOT_exu_DOT__aluOut_T_22 = ((-(uint32_t)npc_DOT_exu_DOT__aluOut_T_14 & npc_DOT_exu_DOT__aluOut_T_6) |
                                      ((-(uint32_t)!npc_DOT_exu_DOT__aluOut_T_14) & 0x0));
      npc_DOT_exu_DOT__aluOut_T_21 = ((-(uint32_t)npc_DOT_exu_DOT__aluOut_T_13 & npc_DOT_exu_DOT__aluOut_T_5) |
                                      ((-(uint32_t)!npc_DOT_exu_DOT__aluOut_T_13) & 0x0));
      npc_DOT_exu_DOT__aluOut_T_19 = ((-(uint32_t)npc_DOT_exu_DOT__aluOut_T_11 & npc_DOT_exu_DOT_xor) |
                                      ((-(uint32_t)!npc_DOT_exu_DOT__aluOut_T_11) & 0x0));
      npc_DOT_exu_DOT__aluOut_T_18 = (npc_DOT_exu_DOT__aluOut_T_10 & npc_DOT_exu_DOT_sltu);
      npc_DOT_exu_DOT__aluOut_T_17 = (npc_DOT_exu_DOT__aluOut_T_9 & npc_DOT_exu_DOT_slt);
      npc_DOT_exu_DOT__aluOut_T_16 = ((-(uint32_t)npc_DOT_exu_DOT__aluOut_T_8 & npc_DOT_exu_DOT__aluOut_T_4) |
                                      ((-(uint32_t)!npc_DOT_exu_DOT__aluOut_T_8) & 0x0));
      npc_DOT_exu_DOT__aluOut_T_15 = ((-(uint32_t)npc_DOT_exu_DOT__aluOut_T_7 & npc_DOT_exu_DOT_sum) |
                                      ((-(uint32_t)!npc_DOT_exu_DOT__aluOut_T_7) & 0x0));
      npc_DOT_exu_DOT__aluOut_T_23 = (npc_DOT_exu_DOT__aluOut_T_15 | npc_DOT_exu_DOT__aluOut_T_16);
      npc_DOT_exu_DOT__aluOut_T_24 = (npc_DOT_exu_DOT__aluOut_T_23 | ((uint32_t)npc_DOT_exu_DOT__aluOut_T_17));
      npc_DOT_exu_DOT__aluOut_T_25 = (npc_DOT_exu_DOT__aluOut_T_24 | ((uint32_t)npc_DOT_exu_DOT__aluOut_T_18));
      npc_DOT_exu_DOT__aluOut_T_26 = (npc_DOT_exu_DOT__aluOut_T_25 | npc_DOT_exu_DOT__aluOut_T_19);
      npc_DOT_exu_DOT__shiftRes_T_15 =
          ((npc_DOT_exu_DOT__shiftRes_T_12 << 4) | (uint8_t)npc_DOT_exu_DOT__shiftRes_T_14);
      npc_DOT_exu_DOT__shiftRes_T_16 =
          (((uint32_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 >> npc_DOT_exu_DOT__shiftRes_T_15) & 0xffffffff);
      npc_DOT_exu_DOT__shiftRes_T_7 = ((npc_DOT_exu_DOT__shiftRes_T_4 << 4) | (uint8_t)npc_DOT_exu_DOT__shiftRes_T_6);
      npc_DOT_exu_DOT__shiftRes_T_8 =
          (((int32_t)((int32_t)npc_DOT_exu_DOT__shiftRes_T_3) >> npc_DOT_exu_DOT__shiftRes_T_7) & 0xffffffff);
      npc_DOT_exu_DOT__shiftRes_T_9 = ((uint32_t)((int32_t)npc_DOT_exu_DOT__shiftRes_T_8) & 0xffffffff);
      npc_DOT_exu_DOT_shiftRes =
          ((-(uint32_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift & npc_DOT_exu_DOT__shiftRes_T_9) |
           ((-(uint32_t)!npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift) &
            npc_DOT_exu_DOT__shiftRes_T_16));
      npc_DOT_exu_DOT__aluOut_T_20 = ((-(uint32_t)npc_DOT_exu_DOT__aluOut_T_12 & npc_DOT_exu_DOT_shiftRes) |
                                      ((-(uint32_t)!npc_DOT_exu_DOT__aluOut_T_12) & 0x0));
      npc_DOT_exu_DOT__aluOut_T_27 = (npc_DOT_exu_DOT__aluOut_T_26 | npc_DOT_exu_DOT__aluOut_T_20);
      npc_DOT_exu_DOT__aluOut_T_28 = (npc_DOT_exu_DOT__aluOut_T_27 | npc_DOT_exu_DOT__aluOut_T_21);
      uint32_t npc_DOT_exu_DOT__aluOut_T_29_DOT_old_DOT_563 = npc_DOT_exu_DOT__aluOut_T_29;
      npc_DOT_exu_DOT__aluOut_T_29 = (npc_DOT_exu_DOT__aluOut_T_28 | npc_DOT_exu_DOT__aluOut_T_22);
      bool cond_npc_DOT_exu_DOT__aluOut_T_29 =
          npc_DOT_exu_DOT__aluOut_T_29 != npc_DOT_exu_DOT__aluOut_T_29_DOT_old_DOT_563;
      oldFlag |= -(uint8_t)cond_npc_DOT_exu_DOT__aluOut_T_29 & 0x6; // 25 26
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT_aluOP: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_aluOP);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_22: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_22);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_21: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_21);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_19: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_19);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_18: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_18);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_17: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_17);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_16: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_15: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_23: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_23);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_24: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_24);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_25: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_25);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_26: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_26);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_15: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_16: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__shiftRes_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__shiftRes_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT_shiftRes: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_shiftRes);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_20: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_20);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_27: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_27);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_28: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_28);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 24 npc_DOT_exu_DOT__aluOut_T_29: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__aluOut_T_29);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x2)) { // id=25
      uint8_t npc_DOT_exu_DOT_branchResInv = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_2 = 0;
      uint16_t npc_DOT_exu_DOT__io_out_bits_res2_T = 0;
      uint8_t npc_DOT_exu_DOT__io_out_bits_res_T = 0;
      uint8_t npc_DOT_exu_DOT__io_out_bits_res_T_1 = 0;
      uint32_t npc_DOT_exu_DOT__io_out_bits_res_T_4 = 0;
      uint32_t npc_DOT_exu_DOT__io_out_bits_res_T_3 = 0;
      uint32_t npc_DOT_exu_DOT__io_out_bits_res_T_6 = 0;
      uint8_t npc_DOT_exu_DOT__io_out_bits_res_T_2 = 0;
      uint32_t npc_DOT_exu_DOT__io_out_bits_res_T_5 = 0;
      uint32_t npc_DOT_exu_DOT__io_out_bits_res_T_7 = 0;
      uint32_t npc_DOT_exu_DOT__io_out_bits_res2_T_1 = 0;
      uint32_t npc_DOT_exu_DOT__io_out_bits_res2_T_2 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_3 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_1 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_4 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_5 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_6 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_9 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_8 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_7 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_10 = 0;
      uint8_t npc_DOT_exu_DOT__branchTaken_T_11 = 0;
      uint8_t npc_DOT_exu_DOT_branchTaken = 0;
      uint8_t npc_DOT_exu_DOT__io_out_bits_redirect_T = 0;
      uint8_t npc_DOT_exu_DOT__io_out_bits_redirect_T_1 = 0;
      if (npc_DOT__lsu_io_in_valid_T) {
        npc_DOT_exu_DOT_branchResInv = (npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 & 0x1);
        npc_DOT_exu_DOT__branchTaken_T_2 = (npc_DOT_exu_DOT_xor != 0);
        npc_DOT_exu_DOT__io_out_bits_res2_T = (npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 & 0xfff);
        npc_DOT_exu_DOT__io_out_bits_res_T = (npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp == 0x0);
        npc_DOT_exu_DOT__io_out_bits_res_T_1 = (npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR == 0x0);
        npc_DOT_exu_DOT__io_out_bits_res_T_4 =
            ((-(uint32_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR &
              npc_DOT_exu_io_in_bits_r_DOT__DOT_src1) |
             ((-(uint32_t)!npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR) & 0x0));
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen_DOT_old_DOT_1140 = npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen = npc_DOT_exu_io_in_bits_r_DOT__DOT_wen;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen ^ npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen_DOT_old_DOT_1140;
        *(uint16_t *)&activeFlags[0] |= -(uint16_t)cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen & 0x8080; // 15 7
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd_DOT_old_DOT_1141 = npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd = npc_DOT_exu_io_in_bits_r_DOT__DOT_rd;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd != npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd_DOT_old_DOT_1141;
        *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd & 0x18000; // 16 15
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3_DOT_old_DOT_1143 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 !=
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3_DOT_old_DOT_1143;
        activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 & 0x50; // 12 14
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad_DOT_old_DOT_1146 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad_DOT_old_DOT_1146;
        *(uint32_t *)&activeFlags[0] |=
            -(uint32_t)cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad & 0x204800; // 21 11 14
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR_DOT_old_DOT_1153 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR_DOT_old_DOT_1153;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR << 6; // 14
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip_DOT_old_DOT_1166 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip_DOT_old_DOT_1166;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip << 7; // 15
        uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code_DOT_old_DOT_1163 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code !=
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code_DOT_old_DOT_1163;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code << 7; // 15
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak_DOT_old_DOT_1162 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak_DOT_old_DOT_1162;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak << 7; // 15
        uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc_DOT_old_DOT_1161 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc !=
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc_DOT_old_DOT_1161;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc << 7; // 15
        uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc_DOT_old_DOT_1160 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc = npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc !=
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc_DOT_old_DOT_1160;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc << 7; // 15
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen_DOT_old_DOT_1157 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen_DOT_old_DOT_1157;
        activeFlags[0] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen << 3; // 3
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal_DOT_old_DOT_1155 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal_DOT_old_DOT_1155;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal << 3; // 11
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret_DOT_old_DOT_1152 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret_DOT_old_DOT_1152;
        activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret & 0x28; // 11 13
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall_DOT_old_DOT_1151 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall_DOT_old_DOT_1151;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall << 3; // 11
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore_DOT_old_DOT_1147 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore ^
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore_DOT_old_DOT_1147;
        activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore & 0xa; // 9 11
        npc_DOT_exu_DOT__io_out_bits_res_T_3 =
            ((-(uint32_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp &
              npc_DOT_exu_io_in_bits_r_DOT__DOT_src3) |
             ((-(uint32_t)!npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp) & 0x0));
        npc_DOT_exu_DOT__io_out_bits_res_T_6 =
            (npc_DOT_exu_DOT__io_out_bits_res_T_3 | npc_DOT_exu_DOT__io_out_bits_res_T_4);
        npc_DOT_exu_DOT__io_out_bits_res_T_2 =
            (npc_DOT_exu_DOT__io_out_bits_res_T & npc_DOT_exu_DOT__io_out_bits_res_T_1);
        npc_DOT_exu_DOT__io_out_bits_res_T_5 =
            ((-(uint32_t)npc_DOT_exu_DOT__io_out_bits_res_T_2 & npc_DOT_exu_DOT__aluOut_T_29) |
             ((-(uint32_t)!npc_DOT_exu_DOT__io_out_bits_res_T_2) & 0x0));
        npc_DOT_exu_DOT__io_out_bits_res_T_7 =
            (npc_DOT_exu_DOT__io_out_bits_res_T_6 | npc_DOT_exu_DOT__io_out_bits_res_T_5);
        uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_res_DOT_old_DOT_1139 = npc_DOT_lsu_io_in_bits_r_DOT__DOT_res;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_res = npc_DOT_exu_DOT__io_out_bits_res_T_7;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_res =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_res != npc_DOT_lsu_io_in_bits_r_DOT__DOT_res_DOT_old_DOT_1139;
        *(uint32_t *)&activeFlags[0] |=
            -(uint32_t)cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_res & 0x4eb00; // 18 8 9 11 13 14 15
        npc_DOT_exu_DOT__io_out_bits_res2_T_1 =
            ((-(uint32_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR &
              ((uint32_t)npc_DOT_exu_DOT__io_out_bits_res2_T)) |
             ((-(uint32_t)!npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR) &
              npc_DOT_exu_io_in_bits_r_DOT__DOT_src3));
        npc_DOT_exu_DOT__io_out_bits_res2_T_2 =
            ((-(uint32_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp & npc_DOT_exu_DOT_sum) |
             ((-(uint32_t)!npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp) &
              npc_DOT_exu_DOT__io_out_bits_res2_T_1));
        uint32_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2_DOT_old_DOT_1142 = npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2 = npc_DOT_exu_DOT__io_out_bits_res2_T_2;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2 != npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2_DOT_old_DOT_1142;
        *(uint16_t *)&activeFlags[0] |= -(uint16_t)cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2 & 0x2880; // 13 11 7
        npc_DOT_exu_DOT__branchTaken_T_3 = (npc_DOT_exu_DOT__branchTaken_T_2 == 0x0);
      } else {
      }
      npc_DOT_exu_DOT__branchTaken_T = ((npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 >> 1) & 0x3);
      npc_DOT_exu_DOT__branchTaken_T_1 = (npc_DOT_exu_DOT__branchTaken_T << 1);
      if (npc_DOT__lsu_io_in_valid_T) {
        npc_DOT_exu_DOT__branchTaken_T_4 = (0x0 == npc_DOT_exu_DOT__branchTaken_T_1);
        npc_DOT_exu_DOT__branchTaken_T_5 = (0x4 == npc_DOT_exu_DOT__branchTaken_T_1);
        npc_DOT_exu_DOT__branchTaken_T_6 = (0x6 == npc_DOT_exu_DOT__branchTaken_T_1);
        npc_DOT_exu_DOT__branchTaken_T_9 = (npc_DOT_exu_DOT__branchTaken_T_6 & npc_DOT_exu_DOT_sltu);
        npc_DOT_exu_DOT__branchTaken_T_8 = (npc_DOT_exu_DOT__branchTaken_T_5 & npc_DOT_exu_DOT_slt);
        npc_DOT_exu_DOT__branchTaken_T_7 = (npc_DOT_exu_DOT__branchTaken_T_4 & npc_DOT_exu_DOT__branchTaken_T_3);
        npc_DOT_exu_DOT__branchTaken_T_10 = (npc_DOT_exu_DOT__branchTaken_T_7 | npc_DOT_exu_DOT__branchTaken_T_8);
        npc_DOT_exu_DOT__branchTaken_T_11 = (npc_DOT_exu_DOT__branchTaken_T_10 | npc_DOT_exu_DOT__branchTaken_T_9);
        npc_DOT_exu_DOT_branchTaken = (npc_DOT_exu_DOT__branchTaken_T_11 ^ npc_DOT_exu_DOT_branchResInv);
        npc_DOT_exu_DOT__io_out_bits_redirect_T =
            ((npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch & npc_DOT_exu_DOT_branchTaken) |
             ((!npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch) &
              npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp));
        npc_DOT_exu_DOT__io_out_bits_redirect_T_1 =
            (npc_DOT_exu_DOT__io_out_bits_redirect_T | npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei);
        uint8_t npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect_DOT_old_DOT_1158 =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect;
        npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect = npc_DOT_exu_DOT__io_out_bits_redirect_T_1;
        bool cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect =
            npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect ^ npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect_DOT_old_DOT_1158;
        activeFlags[1] |= cond_npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect << 3; // 11
      } else {
      }
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT_branchResInv: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_branchResInv);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res2_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res2_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_src3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_wen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_rd);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_res: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_res);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res2_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res2_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_res2_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_res2_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_res2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__branchTaken_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__branchTaken_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT_branchTaken: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT_branchTaken);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_redirect_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_redirect_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_exu_DOT__io_out_bits_redirect_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_out_bits_redirect_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 25 npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_io_in_bits_r_DOT__DOT_redirect);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x4)) { // id=26
      uint8_t npc_DOT_idu_DOT_funct3 = 0;
      uint8_t npc_DOT_idu_DOT_isLui = 0;
      uint8_t npc_DOT_idu_DOT__isCSR_T_1 = 0;
      uint8_t npc_DOT_idu_DOT_isLoad = 0;
      uint8_t npc_DOT_idu_DOT_isJalr = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_isEcall_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_isMret_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_isFencei_T_1 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_38 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_40 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_42 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_79 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_81 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_85 = 0;
      uint16_t npc_DOT_idu_DOT__immI_T = 0;
      uint8_t npc_DOT_idu_DOT__immJ_T = 0;
      uint8_t npc_DOT_idu_DOT__immJ_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__immJ_T_2 = 0;
      uint16_t npc_DOT_idu_DOT__immJ_T_3 = 0;
      uint32_t npc_DOT_idu_DOT__immU_T = 0;
      uint8_t npc_DOT_idu_DOT__immB_T = 0;
      uint8_t npc_DOT_idu_DOT__immB_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__immB_T_2 = 0;
      uint8_t npc_DOT_idu_DOT__immB_T_3 = 0;
      uint8_t npc_DOT_idu_DOT__immS_T = 0;
      uint8_t npc_DOT_idu_DOT__immS_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_rd_T = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_wen_T = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_isArithShift_T = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_6 = 0;
      uint8_t npc_DOT_idu_DOT__T_4 = 0;
      uint8_t npc_DOT_idu_DOT__T_5 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src2_T = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src2_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src2_T_2 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src2_T_3 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_npctrap_isEbreak_T = 0;
      uint32_t npc_DOT_idu_DOT__pc_T = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_npctrap_dnpc_T = 0;
      uint32_t npc_DOT_idu_DOT_pc = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src2_T_4 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src2_T_5 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src2_T_6 = 0;
      uint8_t npc_DOT_idu_DOT_wbCanFwRs2 = 0;
      uint32_t npc_DOT_idu_DOT__T_10 = 0;
      uint32_t npc_DOT_idu_DOT__T_11 = 0;
      uint32_t npc_DOT_idu_DOT_rs2Val = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_7 = 0;
      uint8_t npc_DOT_idu_DOT_wbCanFwRs1 = 0;
      uint32_t npc_DOT_idu_DOT__T_6 = 0;
      uint32_t npc_DOT_idu_DOT__T_7 = 0;
      uint32_t npc_DOT_idu_DOT_rs1Val = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_7 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_8 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_wen_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_wen_T_2 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_wen_T_3 = 0;
      uint16_t npc_DOT_idu_DOT__immS_T_2 = 0;
      uint8_t npc_DOT_idu_DOT__immS_T_3 = 0;
      uint32_t npc_DOT_idu_DOT__immS_T_4 = 0;
      uint32_t npc_DOT_idu_DOT_immS = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_8 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_12 = 0;
      uint8_t npc_DOT_idu_DOT_immB_lo = 0;
      uint8_t npc_DOT_idu_DOT_immB_hi_hi = 0;
      uint8_t npc_DOT_idu_DOT_immB_hi = 0;
      uint16_t npc_DOT_idu_DOT__immB_T_4 = 0;
      uint8_t npc_DOT_idu_DOT__immB_T_5 = 0;
      uint32_t npc_DOT_idu_DOT__immB_T_6 = 0;
      uint32_t npc_DOT_idu_DOT_immB = 0;
      uint32_t npc_DOT_idu_DOT_immU = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_10 = 0;
      uint16_t npc_DOT_idu_DOT_immJ_lo = 0;
      uint16_t npc_DOT_idu_DOT_immJ_hi_hi = 0;
      uint16_t npc_DOT_idu_DOT_immJ_hi = 0;
      uint32_t npc_DOT_idu_DOT__immJ_T_4 = 0;
      uint8_t npc_DOT_idu_DOT__immJ_T_5 = 0;
      uint16_t npc_DOT_idu_DOT__immJ_T_6 = 0;
      uint32_t npc_DOT_idu_DOT_immJ = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_9 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_13 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_14 = 0;
      uint8_t npc_DOT_idu_DOT__immI_T_1 = 0;
      uint32_t npc_DOT_idu_DOT__immI_T_2 = 0;
      uint32_t npc_DOT_idu_DOT_immI = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_11 = 0;
      uint16_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T = 0;
      uint16_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_2 = 0;
      uint16_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_4 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_5 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_3 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_6 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_7 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src2_T_15 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_86 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_43 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_41 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_39 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_3 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_11 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_17 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_19 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_21 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_23 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_25 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_27 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_29 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_31 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_33 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_35 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_37 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_5 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_7 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_9 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_13 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_15 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_45 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_47 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_49 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_51 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_53 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_55 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_57 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_59 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_61 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_63 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_65 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_67 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_69 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_71 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_73 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_75 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_77 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_87 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_88 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_89 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_90 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_91 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_92 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_93 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_94 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_95 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_96 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_97 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_98 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_99 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_100 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_101 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_102 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_103 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_104 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_105 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_106 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_107 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_108 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_109 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_110 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_111 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_112 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_113 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_114 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_115 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_116 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_117 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_118 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_119 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_120 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_121 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_122 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_123 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_124 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_125 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_126 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_127 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_128 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_isJmp_T = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src3_T = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_src3_T_1 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src3_T_2 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src3_T_3 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src3_T_5 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_2 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_3 = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src1_T = 0;
      uint32_t npc_DOT_idu_DOT__io_out_bits_src1_T_1 = 0;
      uint8_t npc_DOT_idu_DOT__isCSR_T_2 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_4 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_2 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_3 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_5 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_9 = 0;
      uint8_t npc_DOT_idu_DOT_isCSR = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_4 = 0;
      uint8_t npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_8 = 0;
      npc_DOT_idu_DOT_funct3 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 12) & 0x7);
      npc_DOT_idu_DOT_isLui = (npc_DOT_idu_DOT__isStype_T == 0xd);
      npc_DOT_idu_DOT__isCSR_T_1 = (npc_DOT_idu_DOT__isStype_T == 0x1c);
      npc_DOT_idu_DOT_isLoad = (npc_DOT_idu_DOT__isStype_T == 0x0);
      npc_DOT_idu_DOT_isJalr = (npc_DOT_idu_DOT__isStype_T == 0x19);
      if (npc_DOT__exu_io_in_valid_T) {
        npc_DOT_idu_DOT__io_out_bits_decode_isEcall_T_1 = (0x73 == npc_DOT_idu_io_in_bits_r_DOT__DOT_inst);
        npc_DOT_idu_DOT__io_out_bits_decode_isMret_T_1 = (0x30200073 == npc_DOT_idu_io_in_bits_r_DOT__DOT_inst);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_38 = (npc_DOT_idu_io_in_bits_r_DOT__DOT_inst & 0x7f);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_40 = (npc_DOT_idu_io_in_bits_r_DOT__DOT_inst & 0x7f);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_42 = (npc_DOT_idu_io_in_bits_r_DOT__DOT_inst & 0x7f);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_79 = (0x73 == npc_DOT_idu_io_in_bits_r_DOT__DOT_inst);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_81 = (0x100073 == npc_DOT_idu_io_in_bits_r_DOT__DOT_inst);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_85 = (0x30200073 == npc_DOT_idu_io_in_bits_r_DOT__DOT_inst);
        npc_DOT_idu_DOT__immU_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 12) & 0xfffff);
        npc_DOT_idu_DOT__io_out_bits_wen_T = (npc_DOT_idu_DOT_isStype | npc_DOT_idu_DOT_isBtype);
        npc_DOT_idu_DOT__io_out_bits_decode_isArithShift_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 30) & 0x1);
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T = (npc_DOT_idu_DOT_isUtype | npc_DOT_idu_DOT_isStype);
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_6 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 30) & 0x1);
        npc_DOT_idu_DOT__io_out_bits_src2_T = (npc_DOT_idu_DOT_src2UseReg == 0x0);
        npc_DOT_idu_DOT__io_out_bits_src2_T_1 = (npc_DOT_idu_DOT_isStype == 0x0);
        npc_DOT_idu_DOT__io_out_bits_src2_T_2 = (npc_DOT_idu_DOT_isJtype == 0x0);
        npc_DOT_idu_DOT__io_out_bits_src2_T_3 = (npc_DOT_idu_DOT_isUtype == 0x0);
        npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_1 = (npc_DOT_idu_DOT__rs1_T_1 == 0x0);
        npc_DOT_idu_DOT__io_out_bits_npctrap_isEbreak_T = (npc_DOT_idu_DOT_isEbreak & npc_DOT_idu_io_in_valid_REG);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore_DOT_old_DOT_1083 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore = npc_DOT_idu_DOT_isStype;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore_DOT_old_DOT_1083;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore << 1; // 25
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch_DOT_old_DOT_1085 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch = npc_DOT_idu_DOT_isBtype;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch_DOT_old_DOT_1085;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch << 1; // 25
        npc_DOT_idu_DOT__io_out_bits_npctrap_dnpc_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_pc + 0x4) & 0xffffffff);
        uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc_DOT_old_DOT_1095 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc = npc_DOT_idu_io_in_bits_r_DOT__DOT_pc;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc !=
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc_DOT_old_DOT_1095;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc << 1; // 25
        uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc_DOT_old_DOT_1096 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc = npc_DOT_idu_DOT__io_out_bits_npctrap_dnpc_T;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc !=
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc_DOT_old_DOT_1096;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc << 1; // 25
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak_DOT_old_DOT_1097 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak = npc_DOT_idu_DOT__io_out_bits_npctrap_isEbreak_T;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak_DOT_old_DOT_1097;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak << 1; // 25
        npc_DOT_idu_DOT__io_out_bits_src2_T_4 =
            (npc_DOT_idu_DOT__io_out_bits_src2_T & npc_DOT_idu_DOT__io_out_bits_src2_T_1);
        npc_DOT_idu_DOT__io_out_bits_src2_T_5 =
            (npc_DOT_idu_DOT__io_out_bits_src2_T_4 & npc_DOT_idu_DOT__io_out_bits_src2_T_2);
        npc_DOT_idu_DOT__io_out_bits_src2_T_6 =
            (npc_DOT_idu_DOT__io_out_bits_src2_T_5 & npc_DOT_idu_DOT__io_out_bits_src2_T_3);
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_7 =
            (npc_DOT_idu_DOT_isRtype & npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_6);
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_8 =
            (npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_7 == 0x0);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift_DOT_old_DOT_1081 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift =
            npc_DOT_idu_DOT__io_out_bits_decode_isArithShift_T;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift_DOT_old_DOT_1081;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift; // 24
        npc_DOT_idu_DOT__io_out_bits_wen_T_1 = (npc_DOT_idu_DOT__io_out_bits_wen_T == 0x0);
        npc_DOT_idu_DOT_immU = (npc_DOT_idu_DOT__immU_T << 12);
        npc_DOT_idu_DOT__io_out_bits_src2_T_10 = ((-(uint32_t)npc_DOT_idu_DOT_isUtype & npc_DOT_idu_DOT_immU) |
                                                  ((-(uint32_t)!npc_DOT_idu_DOT_isUtype) & 0x0));
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_86 = (!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_85);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_43 = (0x6f == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_42);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_41 = (0x37 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_40);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_39 = (0x17 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_38);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret_DOT_old_DOT_1088 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret = npc_DOT_idu_DOT__io_out_bits_decode_isMret_T_1;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret_DOT_old_DOT_1088;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret << 1; // 25
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall_DOT_old_DOT_1087 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall = npc_DOT_idu_DOT__io_out_bits_decode_isEcall_T_1;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall_DOT_old_DOT_1087;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall << 1; // 25
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_1 =
            (npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T | npc_DOT_idu_DOT_isLoad);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad_DOT_old_DOT_1082 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad = npc_DOT_idu_DOT_isLoad;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad_DOT_old_DOT_1082;
        *(uint32_t *)&activeFlags[0] |=
            -(uint32_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad & 0x2200000; // 25 21
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_2 =
            (npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_1 | npc_DOT_idu_DOT_isJtype);
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_3 =
            (npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_2 | npc_DOT_idu_DOT_isJalr);
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_4 = (npc_DOT_idu_DOT_funct3 == 0x0);
        npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T = (npc_DOT_idu_DOT_funct3 != 0x1);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3_DOT_old_DOT_1079 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 = npc_DOT_idu_DOT_funct3;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 !=
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3_DOT_old_DOT_1079;
        activeFlags[3] |= -(uint8_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3 & 0x3; // 24 25
        npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_2 =
            (npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T & npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_1);
        npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_3 = (npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_2 == 0x0);
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_5 =
            (npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_3 | npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_4);
        npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_9 =
            (npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_5 & npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_8);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd_DOT_old_DOT_1080 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd =
            npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_9;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd_DOT_old_DOT_1080;
        *(uint32_t *)&activeFlags[0] |=
            -(uint32_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd & 0x1800000; // 24 23
      } else {
      }
      npc_DOT_idu_DOT__io_out_bits_decode_isFencei_T_1 = (0x100f == npc_DOT_idu_io_in_bits_r_DOT__DOT_inst);
      npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8 = (npc_DOT_idu_io_in_bits_r_DOT__DOT_inst & 0x707f);
      npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36 = (npc_DOT_idu_io_in_bits_r_DOT__DOT_inst & 0xfe00707f);
      npc_DOT_idu_DOT__immI_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 20) & 0xfff);
      npc_DOT_idu_DOT__immJ_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 31) & 0x1);
      npc_DOT_idu_DOT__immJ_T_1 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 12) & 0xff);
      npc_DOT_idu_DOT__immJ_T_2 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 20) & 0x1);
      npc_DOT_idu_DOT__immJ_T_3 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 21) & 0x3ff);
      npc_DOT_idu_DOT__immB_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 31) & 0x1);
      npc_DOT_idu_DOT__immB_T_1 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 7) & 0x1);
      npc_DOT_idu_DOT__immB_T_2 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 25) & 0x3f);
      npc_DOT_idu_DOT__immB_T_3 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 8) & 0xf);
      npc_DOT_idu_DOT__immS_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 25) & 0x7f);
      npc_DOT_idu_DOT__immS_T_1 = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 7) & 0x1f);
      npc_DOT_idu_DOT__io_out_bits_rd_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_inst >> 7) & 0xf);
      npc_DOT_idu_DOT__T_4 = (npc_DOT_idu_DOT__rs1_T_1 == npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd);
      npc_DOT_idu_DOT__T_5 = (npc_DOT_idu_DOT__rs2_T_1 == npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd);
      npc_DOT_idu_DOT__pc_T = ((npc_DOT_idu_io_in_bits_r_DOT__DOT_pc >> 2) & 0x3fffffff);
      npc_DOT_idu_DOT_pc = (npc_DOT_idu_DOT__pc_T << 2);
      npc_DOT_idu_DOT_wbCanFwRs2 = (npc_DOT_wbu_DOT__io_wb_wen_T & npc_DOT_idu_DOT__T_5);
      npc_DOT_idu_DOT__T_10 = ((-(uint32_t)npc_DOT_idu_DOT_wbCanFwRs2 & npc_DOT_wbu_io_in_bits_r_DOT__DOT_res) |
                               ((-(uint32_t)!npc_DOT_idu_DOT_wbCanFwRs2) & npc_DOT_idu_DOT_MPORT_1));
      npc_DOT_idu_DOT__T_11 = ((-(uint32_t)npc_DOT_idu_DOT_lsCanFwRs2 & npc_DOT_lsu_DOT__io_out_bits_res_T_1) |
                               ((-(uint32_t)!npc_DOT_idu_DOT_lsCanFwRs2) & npc_DOT_idu_DOT__T_10));
      npc_DOT_idu_DOT_rs2Val = ((-(uint32_t)npc_DOT_idu_DOT_exCanFwRs2 & npc_DOT_exu_DOT__aluOut_T_29) |
                                ((-(uint32_t)!npc_DOT_idu_DOT_exCanFwRs2) & npc_DOT_idu_DOT__T_11));
      if (npc_DOT__exu_io_in_valid_T) {
        npc_DOT_idu_DOT__io_out_bits_src2_T_7 = ((-(uint32_t)npc_DOT_idu_DOT_src2UseReg & npc_DOT_idu_DOT_rs2Val) |
                                                 ((-(uint32_t)!npc_DOT_idu_DOT_src2UseReg) & 0x0));
        npc_DOT_idu_DOT__io_out_bits_wen_T_2 = (npc_DOT_idu_DOT__io_out_bits_rd_T != 0x0);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_rd_DOT_old_DOT_1078 = npc_DOT_exu_io_in_bits_r_DOT__DOT_rd;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_rd = npc_DOT_idu_DOT__io_out_bits_rd_T;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_rd =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_rd != npc_DOT_exu_io_in_bits_r_DOT__DOT_rd_DOT_old_DOT_1078;
        *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_rd & 0x2200000; // 25 21
        npc_DOT_idu_DOT__io_out_bits_wen_T_3 =
            (npc_DOT_idu_DOT__io_out_bits_wen_T_1 & npc_DOT_idu_DOT__io_out_bits_wen_T_2);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_wen_DOT_old_DOT_1077 = npc_DOT_exu_io_in_bits_r_DOT__DOT_wen;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_wen = npc_DOT_idu_DOT__io_out_bits_wen_T_3;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_wen =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_wen ^ npc_DOT_exu_io_in_bits_r_DOT__DOT_wen_DOT_old_DOT_1077;
        *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_wen & 0x2200000; // 25 21
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_3 = (0x1013 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_11 = (0x5013 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_17 =
            (0x40005013 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_19 = (0x33 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_21 = (0x1033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_23 = (0x2033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_25 = (0x3033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_27 = (0x4033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_29 = (0x5033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_31 = (0x6033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_33 = (0x7033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_35 =
            (0x40000033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_37 =
            (0x40005033 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_1 = (0x13 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_5 = (0x2013 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_7 = (0x3013 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_9 = (0x4013 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_13 = (0x6013 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_15 = (0x7013 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_45 = (0x67 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_47 = (0x63 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_49 = (0x1063 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_51 = (0x4063 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_53 = (0x5063 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_55 = (0x6063 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_57 = (0x7063 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_59 = (0x3 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_61 = (0x1003 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_63 = (0x2003 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_65 = (0x4003 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_67 = (0x5003 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_69 = (0x23 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_71 = (0x1023 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_73 = (0x2023 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_75 = (0x1073 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_77 = (0x2073 == npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_87 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_isFencei_T_1) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_86);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT_DOT_old_DOT_1090 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT =
            npc_DOT_idu_DOT__io_out_bits_decode_isFencei_T_1;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT_DOT_old_DOT_1090;
        activeFlags[5] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT << 3; // 43
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_88 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_81) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_87);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_89 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_79) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_88);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_90 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_77) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_89);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_91 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_75) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_90);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_92 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_73) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_91);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_93 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_71) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_92);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_94 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_69) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_93);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_95 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_67) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_94);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_96 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_65) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_95);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_97 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_63) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_96);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_98 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_61) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_97);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_99 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_59) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_98);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_100 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_57) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_99);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_101 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_55) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_100);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_102 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_53) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_101);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_103 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_51) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_102);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_104 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_49) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_103);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_105 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_47) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_104);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_106 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_45) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_105);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_107 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_43) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_106);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_108 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_41) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_107);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_109 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_39) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_108);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_110 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_37) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_109);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_111 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_35) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_110);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_112 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_33) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_111);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_113 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_31) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_112);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_114 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_29) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_113);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_115 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_27) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_114);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_116 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_25) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_115);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_117 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_23) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_116);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_118 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_21) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_117);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_119 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_19) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_118);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_120 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_17) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_119);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_121 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_15) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_120);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_122 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_13) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_121);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_123 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_11) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_122);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_124 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_9) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_123);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_125 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_7) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_124);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_126 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_5) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_125);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_127 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_3) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_126);
        npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_128 =
            ((!npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_1) & npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_127);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal_DOT_old_DOT_1091 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal = npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_128;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal_DOT_old_DOT_1091;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal << 1; // 25
      } else {
      }
      npc_DOT_idu_DOT_wbCanFwRs1 = (npc_DOT_wbu_DOT__io_wb_wen_T & npc_DOT_idu_DOT__T_4);
      npc_DOT_idu_DOT__T_6 = ((-(uint32_t)npc_DOT_idu_DOT_wbCanFwRs1 & npc_DOT_wbu_io_in_bits_r_DOT__DOT_res) |
                              ((-(uint32_t)!npc_DOT_idu_DOT_wbCanFwRs1) & npc_DOT_idu_DOT_MPORT));
      npc_DOT_idu_DOT__T_7 = ((-(uint32_t)npc_DOT_idu_DOT_lsCanFwRs1 & npc_DOT_lsu_DOT__io_out_bits_res_T_1) |
                              ((-(uint32_t)!npc_DOT_idu_DOT_lsCanFwRs1) & npc_DOT_idu_DOT__T_6));
      npc_DOT_idu_DOT_rs1Val = ((-(uint32_t)npc_DOT_idu_DOT_exCanFwRs1 & npc_DOT_exu_DOT__aluOut_T_29) |
                                ((-(uint32_t)!npc_DOT_idu_DOT_exCanFwRs1) & npc_DOT_idu_DOT__T_7));
      npc_DOT_idu_DOT__immS_T_2 = (((uint16_t)npc_DOT_idu_DOT__immS_T << 5) | (uint8_t)npc_DOT_idu_DOT__immS_T_1);
      if (npc_DOT__exu_io_in_valid_T) {
        npc_DOT_idu_DOT__immS_T_3 = ((npc_DOT_idu_DOT__immS_T_2 >> 11) & 0x1);
        npc_DOT_idu_DOT__immS_T_4 =
            ((-(uint32_t)npc_DOT_idu_DOT__immS_T_3 & 0xfffff) | ((-(uint32_t)!npc_DOT_idu_DOT__immS_T_3) & 0x0));
        npc_DOT_idu_DOT_immS = ((npc_DOT_idu_DOT__immS_T_4 << 12) | (uint16_t)npc_DOT_idu_DOT__immS_T_2);
        npc_DOT_idu_DOT__io_out_bits_src2_T_8 = ((-(uint32_t)npc_DOT_idu_DOT_isStype & npc_DOT_idu_DOT_immS) |
                                                 ((-(uint32_t)!npc_DOT_idu_DOT_isStype) & 0x0));
        npc_DOT_idu_DOT__io_out_bits_src2_T_12 =
            (npc_DOT_idu_DOT__io_out_bits_src2_T_7 | npc_DOT_idu_DOT__io_out_bits_src2_T_8);
      } else {
      }
      npc_DOT_idu_DOT_immB_lo = (npc_DOT_idu_DOT__immB_T_3 << 1);
      npc_DOT_idu_DOT_immB_hi_hi = ((npc_DOT_idu_DOT__immB_T << 1) | (uint8_t)npc_DOT_idu_DOT__immB_T_1);
      npc_DOT_idu_DOT_immB_hi = ((npc_DOT_idu_DOT_immB_hi_hi << 6) | (uint8_t)npc_DOT_idu_DOT__immB_T_2);
      npc_DOT_idu_DOT__immB_T_4 = (((uint16_t)npc_DOT_idu_DOT_immB_hi << 5) | (uint8_t)npc_DOT_idu_DOT_immB_lo);
      if (npc_DOT__exu_io_in_valid_T) {
        npc_DOT_idu_DOT__immB_T_5 = ((npc_DOT_idu_DOT__immB_T_4 >> 12) & 0x1);
        npc_DOT_idu_DOT__immB_T_6 =
            ((-(uint32_t)npc_DOT_idu_DOT__immB_T_5 & 0x7ffff) | ((-(uint32_t)!npc_DOT_idu_DOT__immB_T_5) & 0x0));
        npc_DOT_idu_DOT_immB = ((npc_DOT_idu_DOT__immB_T_6 << 13) | (uint16_t)npc_DOT_idu_DOT__immB_T_4);
      } else {
      }
      npc_DOT_idu_DOT_immJ_lo = (npc_DOT_idu_DOT__immJ_T_3 << 1);
      npc_DOT_idu_DOT_immJ_hi_hi = (((uint16_t)npc_DOT_idu_DOT__immJ_T << 8) | (uint8_t)npc_DOT_idu_DOT__immJ_T_1);
      npc_DOT_idu_DOT_immJ_hi = ((npc_DOT_idu_DOT_immJ_hi_hi << 1) | (uint8_t)npc_DOT_idu_DOT__immJ_T_2);
      npc_DOT_idu_DOT__immJ_T_4 = (((uint32_t)npc_DOT_idu_DOT_immJ_hi << 11) | (uint16_t)npc_DOT_idu_DOT_immJ_lo);
      if (npc_DOT__exu_io_in_valid_T) {
        npc_DOT_idu_DOT__immJ_T_5 = ((npc_DOT_idu_DOT__immJ_T_4 >> 20) & 0x1);
        npc_DOT_idu_DOT__immJ_T_6 =
            ((-(uint16_t)npc_DOT_idu_DOT__immJ_T_5 & 0x7ff) | ((-(uint16_t)!npc_DOT_idu_DOT__immJ_T_5) & 0x0));
        npc_DOT_idu_DOT_immJ = (((uint32_t)npc_DOT_idu_DOT__immJ_T_6 << 21) | (uint32_t)npc_DOT_idu_DOT__immJ_T_4);
        npc_DOT_idu_DOT__io_out_bits_src2_T_9 = ((-(uint32_t)npc_DOT_idu_DOT_isJtype & npc_DOT_idu_DOT_immJ) |
                                                 ((-(uint32_t)!npc_DOT_idu_DOT_isJtype) & 0x0));
        npc_DOT_idu_DOT__io_out_bits_src2_T_13 =
            (npc_DOT_idu_DOT__io_out_bits_src2_T_12 | npc_DOT_idu_DOT__io_out_bits_src2_T_9);
        npc_DOT_idu_DOT__io_out_bits_src2_T_14 =
            (npc_DOT_idu_DOT__io_out_bits_src2_T_13 | npc_DOT_idu_DOT__io_out_bits_src2_T_10);
      } else {
      }
      npc_DOT_idu_DOT__immI_T_1 = ((npc_DOT_idu_DOT__immI_T >> 11) & 0x1);
      npc_DOT_idu_DOT__immI_T_2 =
          ((-(uint32_t)npc_DOT_idu_DOT__immI_T_1 & 0xfffff) | ((-(uint32_t)!npc_DOT_idu_DOT__immI_T_1) & 0x0));
      npc_DOT_idu_DOT_immI = ((npc_DOT_idu_DOT__immI_T_2 << 12) | (uint16_t)npc_DOT_idu_DOT__immI_T);
      if (npc_DOT__exu_io_in_valid_T) {
        npc_DOT_idu_DOT__io_out_bits_src2_T_11 =
            ((-(uint32_t)npc_DOT_idu_DOT__io_out_bits_src2_T_6 & npc_DOT_idu_DOT_immI) |
             ((-(uint32_t)!npc_DOT_idu_DOT__io_out_bits_src2_T_6) & 0x0));
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T = (npc_DOT_idu_DOT_immI & 0xfff);
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_2 = (npc_DOT_idu_DOT_immI & 0xfff);
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_4 = (npc_DOT_idu_DOT_immI & 0xfff);
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_5 = (npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_4 == 0xf12);
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_3 = (npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_2 == 0xf11);
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_1 = (npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T == 0xc00);
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_6 =
            (npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_1 | npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_3);
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_7 =
            (npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_6 | npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_5);
        npc_DOT_idu_DOT__io_out_bits_src2_T_15 =
            (npc_DOT_idu_DOT__io_out_bits_src2_T_14 | npc_DOT_idu_DOT__io_out_bits_src2_T_11);
        uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_src2_DOT_old_DOT_1075 = npc_DOT_exu_io_in_bits_r_DOT__DOT_src2;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 = npc_DOT_idu_DOT__io_out_bits_src2_T_15;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 != npc_DOT_exu_io_in_bits_r_DOT__DOT_src2_DOT_old_DOT_1075;
        *(uint32_t *)&activeFlags[0] |=
            -(uint32_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_src2 & 0x3a00000; // 25 24 21 23
      } else {
      }
      npc_DOT_idu_DOT__io_out_bits_decode_isJmp_T = (npc_DOT_idu_DOT_isJalr | npc_DOT_idu_DOT_isJtype);
      if (npc_DOT__exu_io_in_valid_T) {
        npc_DOT_idu_DOT__io_out_bits_src3_T =
            (npc_DOT_idu_DOT__io_out_bits_decode_isJmp_T | npc_DOT_idu_DOT__io_out_bits_decode_isFencei_T_1);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp_DOT_old_DOT_1084 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp = npc_DOT_idu_DOT__io_out_bits_decode_isJmp_T;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp_DOT_old_DOT_1084;
        *(uint32_t *)&activeFlags[0] |=
            -(uint32_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp & 0x2200000; // 25 21
        npc_DOT_idu_DOT__io_out_bits_src3_T_1 = ((-(uint8_t)npc_DOT_idu_DOT__io_out_bits_src3_T & 0x4) |
                                                 ((-(uint8_t)!npc_DOT_idu_DOT__io_out_bits_src3_T) & 0x0));
        npc_DOT_idu_DOT__io_out_bits_src3_T_2 =
            ((-(uint32_t)npc_DOT_idu_DOT_isBtype & npc_DOT_idu_DOT_immB) |
             ((-(uint32_t)!npc_DOT_idu_DOT_isBtype) & ((uint32_t)npc_DOT_idu_DOT__io_out_bits_src3_T_1)));
        npc_DOT_idu_DOT__io_out_bits_src3_T_3 =
            ((npc_DOT_idu_DOT_pc + npc_DOT_idu_DOT__io_out_bits_src3_T_2) & 0xffffffff);
        npc_DOT_idu_DOT__io_out_bits_src3_T_5 =
            ((-(uint32_t)npc_DOT_idu_DOT_isStype & npc_DOT_idu_DOT_rs2Val) |
             ((-(uint32_t)!npc_DOT_idu_DOT_isStype) & npc_DOT_idu_DOT__io_out_bits_src3_T_3));
        uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_src3_DOT_old_DOT_1076 = npc_DOT_exu_io_in_bits_r_DOT__DOT_src3;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_src3 = npc_DOT_idu_DOT__io_out_bits_src3_T_5;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_src3 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_src3 != npc_DOT_exu_io_in_bits_r_DOT__DOT_src3_DOT_old_DOT_1076;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_src3 << 1; // 25
      } else {
      }
      npc_DOT_idu_DOT__io_out_bits_src1_T =
          ((-(uint32_t)npc_DOT_idu_DOT_isLui & 0x0) | ((-(uint32_t)!npc_DOT_idu_DOT_isLui) & npc_DOT_idu_DOT_pc));
      npc_DOT_idu_DOT__io_out_bits_src1_T_1 =
          ((-(uint32_t)npc_DOT_idu_DOT_src1UseReg & npc_DOT_idu_DOT_rs1Val) |
           ((-(uint32_t)!npc_DOT_idu_DOT_src1UseReg) & npc_DOT_idu_DOT__io_out_bits_src1_T));
      if (npc_DOT__exu_io_in_valid_T) {
        uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_src1_DOT_old_DOT_1074 = npc_DOT_exu_io_in_bits_r_DOT__DOT_src1;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 = npc_DOT_idu_DOT__io_out_bits_src1_T_1;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 != npc_DOT_exu_io_in_bits_r_DOT__DOT_src1_DOT_old_DOT_1074;
        *(uint32_t *)&activeFlags[0] |=
            -(uint32_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_src1 & 0x3a00000; // 25 24 21 23
        uint32_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code_DOT_old_DOT_1098 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code = npc_DOT_idu_DOT__io_out_bits_src1_T_1;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code !=
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code_DOT_old_DOT_1098;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code << 1; // 25
      } else {
      }
      npc_DOT_idu_DOT__isCSR_T_2 = (npc_DOT_idu_DOT_funct3 != 0x0);
      npc_DOT_idu_DOT_isCSR = (npc_DOT_idu_DOT__isCSR_T_1 & npc_DOT_idu_DOT__isCSR_T_2);
      if (npc_DOT__exu_io_in_valid_T) {
        npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_4 =
            (npc_DOT_idu_DOT_isCSR & npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_3);
        npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_8 =
            (npc_DOT_idu_DOT_isCSR & npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_7);
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR_DOT_old_DOT_1089 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR = npc_DOT_idu_DOT_isCSR;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR_DOT_old_DOT_1089;
        *(uint32_t *)&activeFlags[0] |=
            -(uint32_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR & 0x2200000; // 25 21
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip_DOT_old_DOT_1101 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip = npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_8;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip_DOT_old_DOT_1101;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip << 1; // 25
        uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen_DOT_old_DOT_1093 =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen;
        npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen = npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_4;
        bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen =
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen ^
            npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen_DOT_old_DOT_1093;
        activeFlags[3] |= cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen << 1; // 25
      } else {
      }
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_funct3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_funct3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_isLui: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isLui);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__isCSR_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__isCSR_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_isLoad: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isLoad);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_isJalr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isJalr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_isEcall_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_isEcall_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_isMret_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_isMret_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_isFencei_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_isFencei_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_36);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_38: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_38);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_40: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_40);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_42: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_42);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_79: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_79);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_81: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_81);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_85: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_85);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immI_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immI_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immJ_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immJ_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immJ_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immJ_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immJ_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immJ_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immJ_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immJ_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immU_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immU_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immB_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immB_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immB_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immB_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immB_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immB_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immB_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immB_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immS_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immS_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immS_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immS_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_rd_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_rd_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_wen_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_wen_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_isArithShift_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_isArithShift_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_isEbreak_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_isEbreak_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_io_in_bits_r_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_io_in_bits_r_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isStore);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isBranch);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__pc_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__pc_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_dnpc_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_dnpc_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_dnpc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_isEbreak);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_wbCanFwRs2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_wbCanFwRs2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_rs2Val: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_rs2Val);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_wbCanFwRs1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_wbCanFwRs1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_rs1Val: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_rs1Val);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isArithShift);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_wen_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_wen_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_wen_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_wen_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_rd: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_rd);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_wen_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_wen_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_wen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_wen);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immS_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immS_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immS_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immS_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immS_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immS_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immS: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immS);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immB_lo: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immB_lo);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immB_hi_hi: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immB_hi_hi);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immB_hi: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immB_hi);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immB_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immB_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immB_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immB_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immB_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immB_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immB: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immB);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immU: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immU);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immJ_lo: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immJ_lo);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immJ_hi_hi: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immJ_hi_hi);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immJ_hi: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immJ_hi);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immJ_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immJ_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immJ_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immJ_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immJ_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immJ_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immJ: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immJ);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immI_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immI_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__immI_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__immI_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_immI: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_immI);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src2_T_15: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src2_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_src2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_86: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_86);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_43: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_43);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_41: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_41);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_39: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_39);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_17: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_17);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_19: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_19);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_21: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_21);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_23: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_23);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_25: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_25);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_27: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_27);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_29: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_29);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_31: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_31);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_33: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_33);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_35: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_35);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_37: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_37);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_15: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_45: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_45);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_47: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_47);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_49: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_49);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_51: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_51);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_53: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_53);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_55: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_55);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_57: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_57);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_59: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_59);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_61: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_61);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_63: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_63);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_65: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_65);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_67: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_67);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_69: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_69);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_71: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_71);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_73: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_73);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_75: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_75);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_77: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_77);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_87: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_87);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_88: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_88);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_89: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_89);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_90: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_90);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_91: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_91);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_92: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_92);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_93: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_93);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_94: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_94);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_95: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_95);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_96: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_96);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_97: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_97);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_98: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_98);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_99: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_99);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_100: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_100);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_101: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_101);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_102: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_102);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_103: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_103);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_104: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_104);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_105: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_105);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_106: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_106);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_107: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_107);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_108: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_108);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_109: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_109);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_110: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_110);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_111: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_111);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_112: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_112);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_113: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_113);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_114: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_114);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_115: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_115);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_116: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_116);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_117: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_117);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_118: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_118);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_119: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_119);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_120: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_120);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_121: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_121);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_122: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_122);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_123: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_123);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_124: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_124);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_125: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_125);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_126: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_126);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_127: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_127);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_128: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_illegal_T_128);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_illegal);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isMret);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isEcall);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_isJmp_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_isJmp_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src3_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src3_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isJmp);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src3_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src3_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src3_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src3_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src3_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src3_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src3_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src3_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_src3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isLoad);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src1_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src1_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_src1_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_src1_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_src1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_src1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_code);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__isCSR_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__isCSR_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_funct3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_aluop_isAdd_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_aluop_isAdd);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT_isCSR: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT_isCSR);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_decode_csrWen_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_DOT__io_out_bits_npctrap_skip_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isCSR);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_npctrap_DOT__DOT_skip);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 26 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_csrWen);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x8)) { // id=27
      uint8_t mem_DOT_axi4memctrl_DOT__awaddrReg_T = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_1 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_2 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_3 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__T_2 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__awaddrReg_T_2 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__awaddrReg_T_3 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__awaddrReg_T_4 = 0;
      uint32_t mem_DOT_axi4memctrl_DOT__awaddrReg_T_1 = 0;
      uint32_t mem_DOT_axi4memctrl_DOT__io_dmem_waddr_T = 0;
      uint32_t mem_DOT_axi4memctrl_DOT__awaddrReg_T_5 = 0;
      mem_DOT_axi4memctrl_DOT__awaddrReg_T =
          (mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T & npc_DOT_lsu_DOT__io_mem_aw_valid_T_1);
      mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_1 = (mem_DOT_axi4memctrl_DOT_state_w == 0x1);
      mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_2 =
          ((mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_1 << 1) | (uint8_t)mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T);
      mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_3 = (mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_2 != 0);
      mem_DOT_axi4memctrl_DOT__T_2 =
          (mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_3 & npc_DOT_lsu_DOT__io_mem_aw_valid_T_1);
      if (mem_DOT_axi4memctrl_DOT__T_2) {
        mem_DOT_axi4memctrl_DOT__awaddrReg_T_2 =
            (mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T & npc_DOT_lsu_DOT__io_mem_aw_valid_T_1);
        mem_DOT_axi4memctrl_DOT__awaddrReg_T_3 =
            ((-(uint8_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T_2 &
              npc_DOT_lsu_DOT_io_DOT__DOT_mem_DOT__DOT_aw_DOT__DOT_bits_DOT__DOT_size) |
             ((-(uint8_t)!mem_DOT_axi4memctrl_DOT__awaddrReg_T_2) & mem_DOT_axi4memctrl_DOT_awsizeReg));
        mem_DOT_axi4memctrl_DOT__awaddrReg_T_4 =
            ((uint8_t)((uint16_t)0x1 << mem_DOT_axi4memctrl_DOT__awaddrReg_T_3) & 0xff);
      } else {
      }
      mem_DOT_axi4memctrl_DOT__awaddrReg_T_1 =
          ((-(uint32_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T & npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr) |
           ((-(uint32_t)!mem_DOT_axi4memctrl_DOT__awaddrReg_T) & mem_DOT_axi4memctrl_DOT_awaddrReg));
      mem_DOT_axi4memctrl_DOT__io_dmem_waddr_T =
          ((-(uint32_t)npc_DOT_lsu_DOT__io_mem_aw_valid_T_1 & npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr) |
           ((-(uint32_t)!npc_DOT_lsu_DOT__io_mem_aw_valid_T_1) & mem_DOT_axi4memctrl_DOT_awaddrReg));
      uint32_t mem_DOT_dmem_DOT_waddr_DOT_old_DOT_2266 = mem_DOT_dmem_DOT_waddr;
      mem_DOT_dmem_DOT_waddr = mem_DOT_axi4memctrl_DOT__io_dmem_waddr_T;
      if (mem_DOT_axi4memctrl_DOT__T_2) {
        mem_DOT_axi4memctrl_DOT__awaddrReg_T_5 =
            ((mem_DOT_axi4memctrl_DOT__awaddrReg_T_1 + ((uint32_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T_4)) &
             0xffffffff);
        uint32_t mem_DOT_axi4memctrl_DOT_awaddrReg_DOT_old_DOT_2202 = mem_DOT_axi4memctrl_DOT_awaddrReg;
        mem_DOT_axi4memctrl_DOT_awaddrReg = mem_DOT_axi4memctrl_DOT__awaddrReg_T_5;
        bool cond_mem_DOT_axi4memctrl_DOT_awaddrReg =
            mem_DOT_axi4memctrl_DOT_awaddrReg != mem_DOT_axi4memctrl_DOT_awaddrReg_DOT_old_DOT_2202;
        activeFlags[3] |= cond_mem_DOT_axi4memctrl_DOT_awaddrReg << 3; // 27
      } else {
        if (npc_DOT_lsu_DOT__io_mem_aw_valid_T_1) {
          uint32_t mem_DOT_axi4memctrl_DOT_awaddrReg_DOT_old_DOT_2202 = mem_DOT_axi4memctrl_DOT_awaddrReg;
          mem_DOT_axi4memctrl_DOT_awaddrReg = npc_DOT_lsu_DOT_sbuf_DOT__DOT_addr;
          bool cond_mem_DOT_axi4memctrl_DOT_awaddrReg =
              mem_DOT_axi4memctrl_DOT_awaddrReg != mem_DOT_axi4memctrl_DOT_awaddrReg_DOT_old_DOT_2202;
          activeFlags[3] |= cond_mem_DOT_axi4memctrl_DOT_awaddrReg << 3; // 27
        } else {
        }
      }
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT_awaddrReg: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_awaddrReg);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT_awsizeReg: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_awsizeReg);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__awaddrReg_T: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_1: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_2: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_3: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_axi_w_ready_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__T_2: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__awaddrReg_T_2: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__awaddrReg_T_3: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__awaddrReg_T_4: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__awaddrReg_T_1: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__io_dmem_waddr_T: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_dmem_waddr_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_dmem_DOT_waddr: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_dmem_DOT_waddr);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT__awaddrReg_T_5: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__awaddrReg_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 27 mem_DOT_axi4memctrl_DOT_awaddrReg: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_awaddrReg);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x10)) { // id=28
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_1 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_6 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_7 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_8 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_9 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_10 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_11 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_4 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_5 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_14 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_15 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_18 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_19 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_16 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_17 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_2 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_3 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_12 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_13 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_20 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_21 = 0;
      uint8_t npc_DOT_xbar2_DOT__stateRead_T_22 = 0;
      npc_DOT_xbar2_DOT__stateRead_T_1 =
          ((-(uint8_t)npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[1] & 0x3) |
           ((-(uint8_t)!npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[1]) & 0x2));
      npc_DOT_xbar2_DOT__stateRead_T_6 = ((-(uint8_t)npc_DOT_xbar2_DOT__io_in_ar_ready_T_4 & 0x3) |
                                          ((-(uint8_t)!npc_DOT_xbar2_DOT__io_in_ar_ready_T_4) & 0x2));
      npc_DOT_xbar2_DOT__stateRead_T_7 =
          ((-(uint8_t)npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[npc_DOT_xbar2_DOT_arSelIdx_s1] &
            0x1) |
           ((-(uint8_t)!npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[npc_DOT_xbar2_DOT_arSelIdx_s1]) &
            0x3));
      npc_DOT_xbar2_DOT__stateRead_T_8 = (0x0 == npc_DOT_xbar2_DOT_stateRead);
      npc_DOT_xbar2_DOT__stateRead_T_9 = (0x1 == npc_DOT_xbar2_DOT_stateRead);
      npc_DOT_xbar2_DOT__stateRead_T_10 = (0x2 == npc_DOT_xbar2_DOT_stateRead);
      npc_DOT_xbar2_DOT__stateRead_T_11 = (0x3 == npc_DOT_xbar2_DOT_stateRead);
      uint8_t mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T_DOT_old_DOT_2195 =
          mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T;
      mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T = (mem_DOT_axi4memctrl_DOT_arburstCnt == 0x0);
      bool cond_mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T =
          mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T ^
          mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T_DOT_old_DOT_2195;
      oldFlag |= -(uint8_t)cond_mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T & 0x80; // 31
      npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last[0] = 0x1;
      oldFlag |= 0x20; // 29
      npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last[1] =
          mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T;
      oldFlag |= 0x20; // 29
      npc_DOT_xbar2_DOT__stateRead_T_4 =
          (npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_valid[npc_DOT_xbar2_DOT_arSelIdx_s1] &
           npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last[npc_DOT_xbar2_DOT_arSelIdx_s1]);
      npc_DOT_xbar2_DOT__stateRead_T_5 = (!npc_DOT_xbar2_DOT__stateRead_T_4);
      npc_DOT_xbar2_DOT__stateRead_T_14 = ((uint8_t)npc_DOT_xbar2_DOT__stateRead_T_5 & 0x1);
      npc_DOT_xbar2_DOT__stateRead_T_15 = (npc_DOT_xbar2_DOT__stateRead_T_9 & npc_DOT_xbar2_DOT__stateRead_T_14);
      npc_DOT_xbar2_DOT__stateRead_T_18 = ((uint8_t)npc_DOT_xbar2_DOT__stateRead_T_7 & 0x3);
      npc_DOT_xbar2_DOT__stateRead_T_19 =
          ((-(uint8_t)npc_DOT_xbar2_DOT__stateRead_T_11 & npc_DOT_xbar2_DOT__stateRead_T_18) |
           ((-(uint8_t)!npc_DOT_xbar2_DOT__stateRead_T_11) & 0x0));
      npc_DOT_xbar2_DOT__stateRead_T_16 = ((uint8_t)npc_DOT_xbar2_DOT__stateRead_T_6 & 0x3);
      npc_DOT_xbar2_DOT__stateRead_T_17 =
          ((-(uint8_t)npc_DOT_xbar2_DOT__stateRead_T_10 & npc_DOT_xbar2_DOT__stateRead_T_16) |
           ((-(uint8_t)!npc_DOT_xbar2_DOT__stateRead_T_10) & 0x0));
      npc_DOT_xbar2_DOT__stateRead_T_2 =
          ((-(uint8_t)npc_DOT_xbar2_DOT__arSel_1_T_6 &
            npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_ready[1]) |
           ((-(uint8_t)!npc_DOT_xbar2_DOT__arSel_1_T_6) & npc_DOT_xbar2_DOT__stateRead_T_1));
      npc_DOT_xbar2_DOT__stateRead_T_3 =
          ((-(uint8_t)npc_DOT_xbar_DOT__io_out_ar_valid_T_1 & npc_DOT_xbar2_DOT__stateRead_T_2) |
           ((-(uint8_t)!npc_DOT_xbar_DOT__io_out_ar_valid_T_1) & 0x0));
      npc_DOT_xbar2_DOT__stateRead_T_12 = ((uint8_t)npc_DOT_xbar2_DOT__stateRead_T_3 & 0x3);
      npc_DOT_xbar2_DOT__stateRead_T_13 =
          ((-(uint8_t)npc_DOT_xbar2_DOT__stateRead_T_8 & npc_DOT_xbar2_DOT__stateRead_T_12) |
           ((-(uint8_t)!npc_DOT_xbar2_DOT__stateRead_T_8) & 0x0));
      npc_DOT_xbar2_DOT__stateRead_T_20 = (npc_DOT_xbar2_DOT__stateRead_T_13 | npc_DOT_xbar2_DOT__stateRead_T_15);
      npc_DOT_xbar2_DOT__stateRead_T_21 = (npc_DOT_xbar2_DOT__stateRead_T_20 | npc_DOT_xbar2_DOT__stateRead_T_17);
      npc_DOT_xbar2_DOT__stateRead_T_22 = (npc_DOT_xbar2_DOT__stateRead_T_21 | npc_DOT_xbar2_DOT__stateRead_T_19);
      uint8_t npc_DOT_xbar2_DOT_stateRead_DOT_old_DOT_1879 = npc_DOT_xbar2_DOT_stateRead;
      npc_DOT_xbar2_DOT_stateRead = npc_DOT_xbar2_DOT__stateRead_T_22;
      bool cond_npc_DOT_xbar2_DOT_stateRead =
          npc_DOT_xbar2_DOT_stateRead != npc_DOT_xbar2_DOT_stateRead_DOT_old_DOT_1879;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_xbar2_DOT_stateRead & 0x10040014; // 28 18 2 4
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 mem_DOT_axi4memctrl_DOT_arburstCnt: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_arburstCnt);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_15: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_18: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_18);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_19: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_19);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_16: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_17: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_17);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_20: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_20);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_21: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_21);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT__stateRead_T_22: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT__stateRead_T_22);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 28 npc_DOT_xbar2_DOT_stateRead: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_stateRead);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x20)) { // id=29
      uint8_t npc_DOT_lsu_DOT__io_mem_r_ready_T = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_2 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_6 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_7 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_8 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_11 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_12 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_1 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_9 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_10 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_15 = 0;
      uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_ready = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_3 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_4 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_5 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_13 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_14 = 0;
      uint8_t npc_DOT_xbar_DOT__stateRead_T_16 = 0;
      npc_DOT_lsu_DOT__io_mem_r_ready_T = (npc_DOT_lsu_DOT_state == 0x1);
      npc_DOT_xbar_DOT__stateRead_T = ((-(uint8_t)npc_DOT_xbar2_DOT__io_in_ar_ready_T_4 & 0x2) |
                                       ((-(uint8_t)!npc_DOT_xbar2_DOT__io_in_ar_ready_T_4) & 0x1));
      npc_DOT_xbar_DOT__stateRead_T_2 = ((-(uint8_t)npc_DOT_xbar2_DOT__io_in_ar_ready_T_4 & 0x2) |
                                         ((-(uint8_t)!npc_DOT_xbar2_DOT__io_in_ar_ready_T_4) & 0x1));
      npc_DOT_xbar_DOT__stateRead_T_6 = (0x0 == npc_DOT_xbar_DOT_stateRead);
      npc_DOT_xbar_DOT__stateRead_T_7 = (0x1 == npc_DOT_xbar_DOT_stateRead);
      npc_DOT_xbar_DOT__stateRead_T_8 = (0x2 == npc_DOT_xbar_DOT_stateRead);
      uint8_t npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last_DOT_old_DOT_1833 =
          npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last;
      npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last =
          npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last[npc_DOT_xbar2_DOT_arSelIdx_s1];
      bool cond_npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last =
          npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last ^
          npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last_DOT_old_DOT_1833;
      oldFlag |= -(uint8_t)cond_npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last & 0xc0; // 30 31
      npc_DOT_xbar_DOT__stateRead_T_11 = ((uint8_t)npc_DOT_xbar_DOT__stateRead_T_2 & 0x3);
      npc_DOT_xbar_DOT__stateRead_T_12 =
          ((-(uint8_t)npc_DOT_xbar_DOT__stateRead_T_7 & npc_DOT_xbar_DOT__stateRead_T_11) |
           ((-(uint8_t)!npc_DOT_xbar_DOT__stateRead_T_7) & 0x0));
      npc_DOT_xbar_DOT__stateRead_T_1 = ((-(uint8_t)npc_DOT_xbar_DOT_hasReadValid & npc_DOT_xbar_DOT__stateRead_T) |
                                         ((-(uint8_t)!npc_DOT_xbar_DOT_hasReadValid) & 0x0));
      npc_DOT_xbar_DOT__stateRead_T_9 = ((uint8_t)npc_DOT_xbar_DOT__stateRead_T_1 & 0x3);
      npc_DOT_xbar_DOT__stateRead_T_10 =
          ((-(uint8_t)npc_DOT_xbar_DOT__stateRead_T_6 & npc_DOT_xbar_DOT__stateRead_T_9) |
           ((-(uint8_t)!npc_DOT_xbar_DOT__stateRead_T_6) & 0x0));
      npc_DOT_xbar_DOT__stateRead_T_15 = (npc_DOT_xbar_DOT__stateRead_T_10 | npc_DOT_xbar_DOT__stateRead_T_12);
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_ready[0] = npc_DOT_lsu_DOT__io_mem_r_ready_T;
      npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_ready[1] = npc_DOT_icache_DOT__io_mem_r_ready_T;
      npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_ready =
          npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_ready[npc_DOT_xbar_DOT_chosenReadIdxReg_s1];
      npc_DOT_xbar_DOT__stateRead_T_3 =
          (npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_ready & npc_DOT_xbar2_DOT__io_in_r_valid_T_1);
      npc_DOT_xbar_DOT__stateRead_T_4 =
          (npc_DOT_xbar_DOT__stateRead_T_3 & npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last);
      npc_DOT_xbar_DOT__stateRead_T_5 =
          ((-(uint8_t)npc_DOT_xbar_DOT__stateRead_T_4 & 0x0) | ((-(uint8_t)!npc_DOT_xbar_DOT__stateRead_T_4) & 0x2));
      npc_DOT_xbar_DOT__stateRead_T_13 = ((uint8_t)npc_DOT_xbar_DOT__stateRead_T_5 & 0x3);
      npc_DOT_xbar_DOT__stateRead_T_14 =
          ((-(uint8_t)npc_DOT_xbar_DOT__stateRead_T_8 & npc_DOT_xbar_DOT__stateRead_T_13) |
           ((-(uint8_t)!npc_DOT_xbar_DOT__stateRead_T_8) & 0x0));
      npc_DOT_xbar_DOT__stateRead_T_16 = (npc_DOT_xbar_DOT__stateRead_T_15 | npc_DOT_xbar_DOT__stateRead_T_14);
      uint8_t npc_DOT_xbar_DOT_stateRead_DOT_old_DOT_1713 = npc_DOT_xbar_DOT_stateRead;
      npc_DOT_xbar_DOT_stateRead = npc_DOT_xbar_DOT__stateRead_T_16;
      bool cond_npc_DOT_xbar_DOT_stateRead = npc_DOT_xbar_DOT_stateRead != npc_DOT_xbar_DOT_stateRead_DOT_old_DOT_1713;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_xbar_DOT_stateRead & 0x200c0000; // 29 18 19
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_lsu_DOT__io_mem_r_ready_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT__io_mem_r_ready_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_15: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_15);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_ready: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_ready[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_ready: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_ready);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT__stateRead_T_16: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT__stateRead_T_16);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 29 npc_DOT_xbar_DOT_stateRead: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_stateRead);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x40)) { // id=30
      uint8_t npc_DOT_icache_DOT__T_2 = 0;
      uint8_t npc_DOT_icache_DOT__T_4 = 0;
      uint8_t npc_DOT_icache_DOT__T_9 = 0;
      uint8_t npc_DOT_icache_DOT__T_11 = 0;
      uint8_t npc_DOT_icache_DOT__T_12 = 0;
      uint8_t npc_DOT_icache_DOT__state_T = 0;
      uint8_t npc_DOT_icache_DOT__state_T_1 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_2 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_3 = 0;
      uint8_t npc_DOT_icache_DOT__T_13 = 0;
      uint8_t npc_DOT_icache_DOT__T_14 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_10 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_11 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_8 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_9 = 0;
      uint8_t npc_DOT_icache_DOT__T_10 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_6 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_7 = 0;
      uint8_t npc_DOT_icache_DOT__T_5 = 0;
      uint8_t npc_DOT_icache_DOT__T_6 = 0;
      uint8_t npc_DOT_icache_DOT__T_3 = 0;
      uint8_t npc_DOT_icache_DOT__T_7 = 0;
      uint8_t npc_DOT_icache_DOT__T_8 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_4 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_5 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_12 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_13 = 0;
      uint8_t npc_DOT_icache_DOT__state_T_14 = 0;
      npc_DOT_icache_DOT__T_2 = ((-(uint8_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[1] & 0x3) |
                                 ((-(uint8_t)!npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[1]) & 0x2));
      npc_DOT_icache_DOT__T_4 = ((-(uint8_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[1] & 0x3) |
                                 ((-(uint8_t)!npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[1]) & 0x2));
      npc_DOT_icache_DOT__T_9 = (npc_DOT_deq_q_DOT__empty_T | npc_DOT_icache_DOT_flushReg);
      npc_DOT_icache_DOT__T_11 = ((-(uint8_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[1] & 0x3) |
                                  ((-(uint8_t)!npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_ready[1]) & 0x2));
      npc_DOT_icache_DOT__T_12 = (npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last |
                                  npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio);
      npc_DOT_icache_DOT__state_T = (0x0 == npc_DOT_icache_DOT_state);
      npc_DOT_icache_DOT__state_T_1 = (0x1 == npc_DOT_icache_DOT_state);
      npc_DOT_icache_DOT__state_T_2 = (0x2 == npc_DOT_icache_DOT_state);
      npc_DOT_icache_DOT__state_T_3 = (0x3 == npc_DOT_icache_DOT_state);
      npc_DOT_icache_DOT__T_13 =
          (npc_DOT_icache_DOT__T_12 & npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_valid[1]);
      npc_DOT_icache_DOT__T_14 =
          ((-(uint8_t)npc_DOT_icache_DOT__T_13 & 0x1) | ((-(uint8_t)!npc_DOT_icache_DOT__T_13) & 0x3));
      npc_DOT_icache_DOT__state_T_10 = ((uint8_t)npc_DOT_icache_DOT__T_14 & 0x3);
      npc_DOT_icache_DOT__state_T_11 = ((-(uint8_t)npc_DOT_icache_DOT__state_T_3 & npc_DOT_icache_DOT__state_T_10) |
                                        ((-(uint8_t)!npc_DOT_icache_DOT__state_T_3) & 0x0));
      npc_DOT_icache_DOT__state_T_8 = ((uint8_t)npc_DOT_icache_DOT__T_11 & 0x3);
      npc_DOT_icache_DOT__state_T_9 = ((-(uint8_t)npc_DOT_icache_DOT__state_T_2 & npc_DOT_icache_DOT__state_T_8) |
                                       ((-(uint8_t)!npc_DOT_icache_DOT__state_T_2) & 0x0));
      npc_DOT_icache_DOT__T_10 = (!npc_DOT_icache_DOT__T_9);
      npc_DOT_icache_DOT__state_T_6 = ((uint8_t)npc_DOT_icache_DOT__T_10 & 0x1);
      npc_DOT_icache_DOT__state_T_7 = (npc_DOT_icache_DOT__state_T_1 & npc_DOT_icache_DOT__state_T_6);
      npc_DOT_icache_DOT__T_5 = npc_DOT_icache_DOT__T_4;
      npc_DOT_icache_DOT__T_6 = ((-(uint8_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit & 0x0) |
                                 ((-(uint8_t)!npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit) & npc_DOT_icache_DOT__T_5));
      npc_DOT_icache_DOT__T_3 = npc_DOT_icache_DOT__T_2;
      npc_DOT_icache_DOT__T_7 =
          ((-(uint8_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio & npc_DOT_icache_DOT__T_3) |
           ((-(uint8_t)!npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio) & npc_DOT_icache_DOT__T_6));
      npc_DOT_icache_DOT__T_8 = ((-(uint8_t)npc_DOT_icache_DOT_reqValid & npc_DOT_icache_DOT__T_7) |
                                 ((-(uint8_t)!npc_DOT_icache_DOT_reqValid) & 0x0));
      npc_DOT_icache_DOT__state_T_4 = ((uint8_t)npc_DOT_icache_DOT__T_8 & 0x7);
      npc_DOT_icache_DOT__state_T_5 = ((-(uint8_t)npc_DOT_icache_DOT__state_T & npc_DOT_icache_DOT__state_T_4) |
                                       ((-(uint8_t)!npc_DOT_icache_DOT__state_T) & 0x0));
      npc_DOT_icache_DOT__state_T_12 = (npc_DOT_icache_DOT__state_T_5 | npc_DOT_icache_DOT__state_T_7);
      npc_DOT_icache_DOT__state_T_13 = (npc_DOT_icache_DOT__state_T_12 | npc_DOT_icache_DOT__state_T_9);
      npc_DOT_icache_DOT__state_T_14 = (npc_DOT_icache_DOT__state_T_13 | npc_DOT_icache_DOT__state_T_11);
      uint8_t npc_DOT_icache_DOT_state_DOT_old_DOT_1402 = npc_DOT_icache_DOT_state;
      npc_DOT_icache_DOT_state = npc_DOT_icache_DOT__state_T_14;
      bool cond_npc_DOT_icache_DOT_state = npc_DOT_icache_DOT_state != npc_DOT_icache_DOT_state_DOT_old_DOT_1402;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_state & 0x401a1008; // 30 20 19 17 12 3
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_2: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_11: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_11);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_9: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_10: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_6: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_3: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_7: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__T_8: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_5: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_12: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_12);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_13: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_13);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT__state_T_14: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__state_T_14);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 30 npc_DOT_icache_DOT_state: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_state);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x80)) { // id=31
      uint8_t npc_DOT_exu_DOT__io_fence_i_T = 0;
      uint8_t npc_DOT_icache_DOT__T_56 = 0;
      uint8_t npc_DOT_icache_DOT__T_57 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__T_1 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_1 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_4 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_5 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_6 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_7 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_2 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_3 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_8 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_9 = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__state_r_T_10 = 0;
      uint8_t npc_DOT_icache_DOT__io_mem_ar_bits_len_T = 0;
      uint8_t mem_DOT_axi4memctrl_DOT__arburstCnt_T = 0;
      uint8_t npc_DOT_icache_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len = 0;
      uint8_t npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len = 0;
      uint8_t npc_DOT_icache_DOT__T_58 = 0;
      uint8_t npc_DOT_icache_DOT__valid_T = 0;
      uint8_t npc_DOT_icache_DOT__valid_T_1 = 0;
      npc_DOT_exu_DOT__io_fence_i_T =
          (npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei & npc_DOT_exu_io_in_valid_REG);
      npc_DOT_icache_DOT__T_56 =
          (npc_DOT_icache_DOT__resFromMem_T & npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_last);
      npc_DOT_icache_DOT__T_57 = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio == 0x0);
      mem_DOT_axi4memctrl_DOT__T_1 = (npc_DOT_xbar2_DOT_arSel_s1_1 & mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T);
      mem_DOT_axi4memctrl_DOT__state_r_T_1 = (npc_DOT_xbar2_DOT_arSel_s1_1 & mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T);
      mem_DOT_axi4memctrl_DOT__state_r_T_4 = (0x0 == mem_DOT_axi4memctrl_DOT_state_r);
      mem_DOT_axi4memctrl_DOT__state_r_T_5 = mem_DOT_axi4memctrl_DOT_state_r;
      mem_DOT_axi4memctrl_DOT__state_r_T_6 = ((uint8_t)npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1 & 0x1);
      mem_DOT_axi4memctrl_DOT__state_r_T_7 =
          (mem_DOT_axi4memctrl_DOT__state_r_T_4 & mem_DOT_axi4memctrl_DOT__state_r_T_6);
      mem_DOT_axi4memctrl_DOT__state_r_T_2 =
          (mem_DOT_axi4memctrl_DOT__state_r_T_1 & mem_DOT_axi4memctrl_DOT__io_axi_r_bits_last_T);
      mem_DOT_axi4memctrl_DOT__state_r_T_3 = (!mem_DOT_axi4memctrl_DOT__state_r_T_2);
      mem_DOT_axi4memctrl_DOT__state_r_T_8 = ((uint8_t)mem_DOT_axi4memctrl_DOT__state_r_T_3 & 0x1);
      mem_DOT_axi4memctrl_DOT__state_r_T_9 =
          (mem_DOT_axi4memctrl_DOT__state_r_T_5 & mem_DOT_axi4memctrl_DOT__state_r_T_8);
      mem_DOT_axi4memctrl_DOT__state_r_T_10 =
          (mem_DOT_axi4memctrl_DOT__state_r_T_7 | mem_DOT_axi4memctrl_DOT__state_r_T_9);
      uint8_t mem_DOT_axi4memctrl_DOT_state_r_DOT_old_DOT_2180 = mem_DOT_axi4memctrl_DOT_state_r;
      mem_DOT_axi4memctrl_DOT_state_r = mem_DOT_axi4memctrl_DOT__state_r_T_10;
      bool cond_mem_DOT_axi4memctrl_DOT_state_r =
          mem_DOT_axi4memctrl_DOT_state_r ^ mem_DOT_axi4memctrl_DOT_state_r_DOT_old_DOT_2180;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_mem_DOT_axi4memctrl_DOT_state_r & 0x80040008; // 31 18 3
      if (mem_DOT_axi4memctrl_DOT__T_1) {
        mem_DOT_axi4memctrl_DOT__arburstCnt_T = ((mem_DOT_axi4memctrl_DOT_arburstCnt - 0x1) & 0xff);
        uint8_t mem_DOT_axi4memctrl_DOT_arburstCnt_DOT_old_DOT_2168 = mem_DOT_axi4memctrl_DOT_arburstCnt;
        mem_DOT_axi4memctrl_DOT_arburstCnt = mem_DOT_axi4memctrl_DOT__arburstCnt_T;
        bool cond_mem_DOT_axi4memctrl_DOT_arburstCnt =
            mem_DOT_axi4memctrl_DOT_arburstCnt != mem_DOT_axi4memctrl_DOT_arburstCnt_DOT_old_DOT_2168;
        activeFlags[3] |= -(uint8_t)cond_mem_DOT_axi4memctrl_DOT_arburstCnt & 0x90; // 28 31
      } else {
        if (npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1) {
          npc_DOT_icache_DOT__io_mem_ar_bits_len_T =
              ((-(uint8_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio & 0x0) |
               ((-(uint8_t)!npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio) & 0x3));
          npc_DOT_icache_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len =
              npc_DOT_icache_DOT__io_mem_ar_bits_len_T;
          npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len[0] = 0x0;
          npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len[1] =
              npc_DOT_icache_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len;
          npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len =
              npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len
                  [npc_DOT_xbar_DOT_chosenReadIdxReg_s0];
          uint8_t mem_DOT_axi4memctrl_DOT_arburstCnt_DOT_old_DOT_2168 = mem_DOT_axi4memctrl_DOT_arburstCnt;
          mem_DOT_axi4memctrl_DOT_arburstCnt = npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len;
          bool cond_mem_DOT_axi4memctrl_DOT_arburstCnt =
              mem_DOT_axi4memctrl_DOT_arburstCnt != mem_DOT_axi4memctrl_DOT_arburstCnt_DOT_old_DOT_2168;
          activeFlags[3] |= -(uint8_t)cond_mem_DOT_axi4memctrl_DOT_arburstCnt & 0x90; // 28 31
        } else {
        }
      }
      npc_DOT_icache_DOT__T_58 = (npc_DOT_icache_DOT__T_56 & npc_DOT_icache_DOT__T_57);
      if (npc_DOT_icache_DOT__T_58) {
        npc_DOT_icache_DOT_tag[npc_DOT_icache_DOT__idx_s1_T_2] = npc_DOT_icache_DOT__tag_s1_T_3;
        activeFlags[0] |= 0x8; // 3
      } else {
      }
      if (npc_DOT_exu_DOT__io_fence_i_T) {
        uint8_t npc_DOT_icache_DOT_valid_DOT_old_DOT_1251 = npc_DOT_icache_DOT_valid;
        npc_DOT_icache_DOT_valid = 0x0;
        bool cond_npc_DOT_icache_DOT_valid = npc_DOT_icache_DOT_valid != npc_DOT_icache_DOT_valid_DOT_old_DOT_1251;
        *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_valid & 0x80080000; // 31 19
      } else {
        if (npc_DOT_icache_DOT__T_58) {
          npc_DOT_icache_DOT__valid_T = ((uint8_t)(0x1 << npc_DOT_icache_DOT__idx_s1_T_2) & 0xf);
          npc_DOT_icache_DOT__valid_T_1 = (npc_DOT_icache_DOT_valid | npc_DOT_icache_DOT__valid_T);
          uint8_t npc_DOT_icache_DOT_valid_DOT_old_DOT_1251 = npc_DOT_icache_DOT_valid;
          npc_DOT_icache_DOT_valid = npc_DOT_icache_DOT__valid_T_1;
          bool cond_npc_DOT_icache_DOT_valid = npc_DOT_icache_DOT_valid != npc_DOT_icache_DOT_valid_DOT_old_DOT_1251;
          *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_valid & 0x80080000; // 31 19
        } else {
        }
      }
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_exu_DOT__io_fence_i_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_DOT__io_fence_i_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT__T_56: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_56);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT__T_57: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_57);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__T_1: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_1: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_4: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_5: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_5);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_6: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_6);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_7: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_7);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_2: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_2);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_3: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_3);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_8: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_8);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_9: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_9);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__state_r_T_10: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__state_r_T_10);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT_state_r: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_state_r);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT__io_mem_ar_bits_len_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__io_mem_ar_bits_len_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT__arburstCnt_T: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__arburstCnt_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_io_DOT__DOT_mem_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len: ", cycles);
        for (int i0 = 0; i0 < 2; i0++) {
          printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_in_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len[i0]);
          printf(" ");
        }
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_len);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 mem_DOT_axi4memctrl_DOT_arburstCnt: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_arburstCnt);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT__T_58: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_58);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT_MPORT_4: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_MPORT_4);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT__valid_T: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__valid_T);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT__valid_T_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT__valid_T_1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 31 npc_DOT_icache_DOT_valid: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_valid);
        printf("\n");
      }
#endif
    }
  }
  if (unlikely(activeFlags[4] & 0x1)) { // id=32
    uint32_t mem_DOT_axi4memctrl_DOT__io_dmem_raddr_T = 0;
    mem_DOT_axi4memctrl_DOT__io_dmem_raddr_T =
        ((-(uint32_t)npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1 &
          npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr) |
         ((-(uint32_t)!npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1) & mem_DOT_axi4memctrl_DOT_araddrReg));
    uint32_t mem_DOT_dmem_DOT_raddr_DOT_old_DOT_2263 = mem_DOT_dmem_DOT_raddr;
    mem_DOT_dmem_DOT_raddr = mem_DOT_axi4memctrl_DOT__io_dmem_raddr_T;
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 32 mem_DOT_axi4memctrl_DOT_araddrReg: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_araddrReg);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 32 mem_DOT_axi4memctrl_DOT__io_dmem_raddr_T: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__io_dmem_raddr_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 32 mem_DOT_dmem_DOT_raddr: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_dmem_DOT_raddr);
      printf("\n");
    }
#endif
  }
  uint32_t mem_DOT_dmem_DOT_rdata_DOT_old_DOT_2264 = mem_DOT_dmem_DOT_rdata;
  SimDMEM(mem_DOT_dmem_DOT_ren, mem_DOT_dmem_DOT_raddr, &mem_DOT_dmem_DOT_rdata, mem_DOT_dmem_DOT_wen,
          mem_DOT_dmem_DOT_waddr, mem_DOT_dmem_DOT_wdata, mem_DOT_dmem_DOT_wmask);
  bool cond_mem_DOT_dmem_DOT_rdata = mem_DOT_dmem_DOT_rdata != mem_DOT_dmem_DOT_rdata_DOT_old_DOT_2264;
  activeFlags[4] |= -(uint8_t)cond_mem_DOT_dmem_DOT_rdata & 0x4; // 34
  if (unlikely(activeFlags[4] & 0x4)) {                          // id=34
    uint8_t npc_DOT_icache_DOT__resFromMem_T_1 = 0;
    uint8_t npc_DOT_icache_DOT__T_29 = 0;
    uint32_t npc_DOT_clint_DOT__io_r_bits_data_T_1 = 0;
    uint32_t npc_DOT_clint_DOT__io_r_bits_data_T_4 = 0;
    uint32_t npc_DOT_clint_DOT__io_r_bits_data_T_3 = 0;
    uint32_t npc_DOT_clint_DOT__io_r_bits_data_T_5 = 0;
    uint32_t npc_DOT_clint_DOT__io_r_bits_data_T = 0;
    uint32_t npc_DOT_clint_DOT__io_r_bits_data_T_2 = 0;
    uint32_t npc_DOT_clint_DOT__io_r_bits_data_T_6 = 0;
    uint32_t npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data = 0;
    uint8_t npc_DOT_icache_DOT__T_30 = 0;
    uint8_t npc_DOT_icache_DOT__T_32 = 0;
    uint8_t npc_DOT_icache_DOT__T_38 = 0;
    uint8_t npc_DOT_icache_DOT__T_44 = 0;
    uint8_t npc_DOT_icache_DOT__T_50 = 0;
    uint8_t npc_DOT_icache_DOT__T_51 = 0;
    uint8_t npc_DOT_icache_DOT__T_45 = 0;
    uint8_t npc_DOT_icache_DOT__T_39 = 0;
    uint8_t npc_DOT_icache_DOT__T_33 = 0;
    uint8_t npc_DOT_icache_DOT__resFromMem_T_2 = 0;
    uint8_t npc_DOT_icache_DOT__resFromMem_T_3 = 0;
    npc_DOT_icache_DOT__resFromMem_T_1 = (npc_DOT_icache_DOT_beatCnt_value == npc_DOT_icache_DOT__wordIdx_s1_T_1);
    npc_DOT_icache_DOT__T_29 = (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio == 0x0);
    npc_DOT_clint_DOT__io_r_bits_data_T_1 = (npc_DOT_clint_DOT_cnt & 0xffffffff);
    npc_DOT_clint_DOT__io_r_bits_data_T_4 = ((npc_DOT_clint_DOT_cnt >> 32) & 0xffffffff);
    npc_DOT_clint_DOT__io_r_bits_data_T_3 =
        ((-(uint32_t)npc_DOT_clint_DOT_isMtimehReg & 0xffffffff) | ((-(uint32_t)!npc_DOT_clint_DOT_isMtimehReg) & 0x0));
    npc_DOT_clint_DOT__io_r_bits_data_T_5 =
        (npc_DOT_clint_DOT__io_r_bits_data_T_3 & npc_DOT_clint_DOT__io_r_bits_data_T_4);
    npc_DOT_clint_DOT__io_r_bits_data_T =
        ((-(uint32_t)npc_DOT_clint_DOT_isMtimeReg & 0xffffffff) | ((-(uint32_t)!npc_DOT_clint_DOT_isMtimeReg) & 0x0));
    npc_DOT_clint_DOT__io_r_bits_data_T_2 =
        (npc_DOT_clint_DOT__io_r_bits_data_T & npc_DOT_clint_DOT__io_r_bits_data_T_1);
    npc_DOT_clint_DOT__io_r_bits_data_T_6 =
        (npc_DOT_clint_DOT__io_r_bits_data_T_2 | npc_DOT_clint_DOT__io_r_bits_data_T_5);
    npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data[0] = npc_DOT_clint_DOT__io_r_bits_data_T_6;
    npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data[1] = mem_DOT_dmem_DOT_rdata;
    npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data =
        npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data[npc_DOT_xbar2_DOT_arSelIdx_s1];
    uint32_t npc_DOT_lsu_DOT_rdataMuxS2_DOT_old_DOT_699 = npc_DOT_lsu_DOT_rdataMuxS2;
    npc_DOT_lsu_DOT_rdataMuxS2 = npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data;
    bool cond_npc_DOT_lsu_DOT_rdataMuxS2 = npc_DOT_lsu_DOT_rdataMuxS2 != npc_DOT_lsu_DOT_rdataMuxS2_DOT_old_DOT_699;
    activeFlags[1] |= cond_npc_DOT_lsu_DOT_rdataMuxS2 << 6; // 14
    npc_DOT_icache_DOT__T_30 = (npc_DOT_icache_DOT__resFromMem_T & npc_DOT_icache_DOT__T_29);
    if (npc_DOT_icache_DOT__T_30) {
      npc_DOT_icache_DOT__T_32 = (0x0 == npc_DOT_icache_DOT_beatCnt_value);
      npc_DOT_icache_DOT__T_38 = (0x1 == npc_DOT_icache_DOT_beatCnt_value);
      npc_DOT_icache_DOT__T_44 = (0x2 == npc_DOT_icache_DOT_beatCnt_value);
      npc_DOT_icache_DOT__T_50 = (0x3 == npc_DOT_icache_DOT_beatCnt_value);
      npc_DOT_icache_DOT__T_51 = (npc_DOT_icache_DOT__resFromMem_T & npc_DOT_icache_DOT__T_50);
      if (npc_DOT_icache_DOT__T_51) {
        npc_DOT_icache_DOT_data_3[npc_DOT_icache_DOT__idx_s1_T_2] =
            npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data;
        activeFlags[2] |= 0x2; // 17
      } else {
      }
      npc_DOT_icache_DOT__T_45 = (npc_DOT_icache_DOT__resFromMem_T & npc_DOT_icache_DOT__T_44);
      if (npc_DOT_icache_DOT__T_45) {
        npc_DOT_icache_DOT_data_2[npc_DOT_icache_DOT__idx_s1_T_2] =
            npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data;
        activeFlags[2] |= 0x2; // 17
      } else {
      }
      npc_DOT_icache_DOT__T_39 = (npc_DOT_icache_DOT__resFromMem_T & npc_DOT_icache_DOT__T_38);
      if (npc_DOT_icache_DOT__T_39) {
        npc_DOT_icache_DOT_data_1[npc_DOT_icache_DOT__idx_s1_T_2] =
            npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data;
        activeFlags[2] |= 0x2; // 17
      } else {
      }
      npc_DOT_icache_DOT__T_33 = (npc_DOT_icache_DOT__resFromMem_T & npc_DOT_icache_DOT__T_32);
      if (npc_DOT_icache_DOT__T_33) {
        npc_DOT_icache_DOT_data_0[npc_DOT_icache_DOT__idx_s1_T_2] =
            npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data;
        activeFlags[2] |= 0x2; // 17
      } else {
      }
    } else {
    }
    npc_DOT_icache_DOT__resFromMem_T_2 =
        (npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio | npc_DOT_icache_DOT__resFromMem_T_1);
    npc_DOT_icache_DOT__resFromMem_T_3 = (npc_DOT_icache_DOT__resFromMem_T & npc_DOT_icache_DOT__resFromMem_T_2);
    if (npc_DOT_icache_DOT__resFromMem_T_3) {
      uint32_t npc_DOT_icache_DOT_resFromMem_DOT_old_DOT_1493 = npc_DOT_icache_DOT_resFromMem;
      npc_DOT_icache_DOT_resFromMem = npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data;
      bool cond_npc_DOT_icache_DOT_resFromMem =
          npc_DOT_icache_DOT_resFromMem != npc_DOT_icache_DOT_resFromMem_DOT_old_DOT_1493;
      activeFlags[2] |= cond_npc_DOT_icache_DOT_resFromMem << 4; // 20
    } else {
    }
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__resFromMem_T_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__resFromMem_T_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_29: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_29);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT_isMtimeReg: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_isMtimeReg);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT_isMtimehReg: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT_isMtimehReg);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT__io_r_bits_data_T_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_r_bits_data_T_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT__io_r_bits_data_T_4: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_r_bits_data_T_4);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT__io_r_bits_data_T_3: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_r_bits_data_T_3);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT__io_r_bits_data_T_5: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_r_bits_data_T_5);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT__io_r_bits_data_T: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_r_bits_data_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT__io_r_bits_data_T_2: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_r_bits_data_T_2);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_clint_DOT__io_r_bits_data_T_6: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_clint_DOT__io_r_bits_data_T_6);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data: ", cycles);
      for (int i0 = 0; i0 < 2; i0++) {
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_io_DOT__DOT_out_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data[i0]);
        printf(" ");
      }
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_io_DOT__DOT_in_DOT__DOT_r_DOT__DOT_bits_DOT__DOT_data);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_lsu_DOT_rdataMuxS2: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_rdataMuxS2);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_30: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_30);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_32: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_32);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_38: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_38);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_44: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_44);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_50: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_50);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_51: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_51);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT_MPORT_3: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_MPORT_3);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_45: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_45);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT_MPORT_2: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_MPORT_2);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_39: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_39);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT_MPORT_1: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_MPORT_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__T_33: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__T_33);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT_MPORT: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_MPORT);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__resFromMem_T_2: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__resFromMem_T_2);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT__resFromMem_T_3: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT__resFromMem_T_3);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 34 npc_DOT_icache_DOT_resFromMem: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_resFromMem);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[4] & 0x8)) { // id=35
    uint8_t mem_DOT_axi4memctrl_DOT__T = 0;
    uint8_t mem_DOT_axi4memctrl_DOT__araddrReg_T = 0;
    uint32_t mem_DOT_axi4memctrl_DOT__araddrReg_T_1 = 0;
    mem_DOT_axi4memctrl_DOT__T = (npc_DOT_xbar2_DOT_arSel_s1_1 & mem_DOT_axi4memctrl_DOT__io_axi_r_valid_T);
    if (mem_DOT_axi4memctrl_DOT__T) {
      mem_DOT_axi4memctrl_DOT__araddrReg_T = ((uint8_t)((uint16_t)0x1 << mem_DOT_axi4memctrl_DOT_arsizeReg) & 0xff);
      mem_DOT_axi4memctrl_DOT__araddrReg_T_1 =
          ((mem_DOT_axi4memctrl_DOT_araddrReg + ((uint32_t)mem_DOT_axi4memctrl_DOT__araddrReg_T)) & 0xffffffff);
      uint32_t mem_DOT_axi4memctrl_DOT_araddrReg_DOT_old_DOT_2162 = mem_DOT_axi4memctrl_DOT_araddrReg;
      mem_DOT_axi4memctrl_DOT_araddrReg = mem_DOT_axi4memctrl_DOT__araddrReg_T_1;
      bool cond_mem_DOT_axi4memctrl_DOT_araddrReg =
          mem_DOT_axi4memctrl_DOT_araddrReg != mem_DOT_axi4memctrl_DOT_araddrReg_DOT_old_DOT_2162;
      activeFlags[4] |= -(uint8_t)cond_mem_DOT_axi4memctrl_DOT_araddrReg & 0x9; // 32 35
    } else {
      if (npc_DOT_xbar2_DOT__io_out_1_ar_valid_T_1) {
        uint32_t mem_DOT_axi4memctrl_DOT_araddrReg_DOT_old_DOT_2162 = mem_DOT_axi4memctrl_DOT_araddrReg;
        mem_DOT_axi4memctrl_DOT_araddrReg = npc_DOT_xbar_DOT_io_DOT__DOT_out_DOT__DOT_ar_DOT__DOT_bits_DOT__DOT_addr;
        bool cond_mem_DOT_axi4memctrl_DOT_araddrReg =
            mem_DOT_axi4memctrl_DOT_araddrReg != mem_DOT_axi4memctrl_DOT_araddrReg_DOT_old_DOT_2162;
        activeFlags[4] |= -(uint8_t)cond_mem_DOT_axi4memctrl_DOT_araddrReg & 0x9; // 32 35
      } else {
      }
    }
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 35 clock: ", cycles);
      printf("%lx", (uint64_t)clock);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 35 mem_DOT_axi4memctrl_DOT_arsizeReg: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_arsizeReg);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 35 mem_DOT_axi4memctrl_DOT__T: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 35 mem_DOT_axi4memctrl_DOT__araddrReg_T: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__araddrReg_T);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 35 mem_DOT_axi4memctrl_DOT__araddrReg_T_1: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT__araddrReg_T_1);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 35 mem_DOT_axi4memctrl_DOT_araddrReg: ", cycles);
      printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_araddrReg);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[4] & 0x10)) { // id=36
    uint8_t npc_DOT_lsu_DOT_state_DOT_old_DOT_2403 = npc_DOT_lsu_DOT_state;
    npc_DOT_lsu_DOT_state = npc_DOT_lsu_DOT_state_DOT_NEXT;
    bool cond_npc_DOT_lsu_DOT_state = npc_DOT_lsu_DOT_state != npc_DOT_lsu_DOT_state_DOT_old_DOT_2403;
    *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_lsu_DOT_state & 0x20080808; // 29 19 11 3
    uint8_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_old_DOT_2419 =
        npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit;
    npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit = npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_NEXT;
    bool cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit =
        npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit ^ npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit_DOT_old_DOT_2419;
    *(uint32_t *)&activeFlags[0] |=
        -(uint32_t)cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit & 0x401a0000; // 30 17 19 20
    uint8_t npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_old_DOT_2420 =
        npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio;
    npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio = npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_NEXT;
    bool cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio =
        npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio ^ npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio_DOT_old_DOT_2420;
    *(uint64_t *)&activeFlags[0] |=
        -(uint64_t)cond_npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio & 0x4c0060000; // 34 31 30 17 18
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 36 npc_DOT_lsu_DOT_state: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_state);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 36 npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_hit);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 36 npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_icache_DOT_s1_in_bits_r_DOT__DOT_mmio);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[4] & 0x20)) { // id=37
    uint32_t npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_old_DOT_2404 = npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata;
    npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata = npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_NEXT;
    bool cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata =
        npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata != npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata_DOT_old_DOT_2404;
    activeFlags[1] |= cond_npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata << 5; // 13
    uint32_t npc_DOT_lsu_DOT_mstatus_DOT_old_DOT_2407 = npc_DOT_lsu_DOT_mstatus;
    npc_DOT_lsu_DOT_mstatus = npc_DOT_lsu_DOT_mstatus_DOT_NEXT;
    bool cond_npc_DOT_lsu_DOT_mstatus = npc_DOT_lsu_DOT_mstatus != npc_DOT_lsu_DOT_mstatus_DOT_old_DOT_2407;
    activeFlags[1] |= cond_npc_DOT_lsu_DOT_mstatus << 6; // 14
    uint32_t npc_DOT_lsu_DOT_mvendorid_DOT_old_DOT_2410 = npc_DOT_lsu_DOT_mvendorid;
    npc_DOT_lsu_DOT_mvendorid = npc_DOT_lsu_DOT_mvendorid_DOT_NEXT;
    bool cond_npc_DOT_lsu_DOT_mvendorid = npc_DOT_lsu_DOT_mvendorid != npc_DOT_lsu_DOT_mvendorid_DOT_old_DOT_2410;
    activeFlags[1] |= cond_npc_DOT_lsu_DOT_mvendorid << 6; // 14
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 37 npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_sbuf_r_DOT__DOT_wdata);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 37 npc_DOT_lsu_DOT_mstatus: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mstatus);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 37 npc_DOT_lsu_DOT_mvendorid: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mvendorid);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[4] & 0x40)) { // id=38
    uint32_t npc_DOT_lsu_DOT_mtvec_DOT_old_DOT_2405 = npc_DOT_lsu_DOT_mtvec;
    npc_DOT_lsu_DOT_mtvec = npc_DOT_lsu_DOT_mtvec_DOT_NEXT;
    bool cond_npc_DOT_lsu_DOT_mtvec = npc_DOT_lsu_DOT_mtvec != npc_DOT_lsu_DOT_mtvec_DOT_old_DOT_2405;
    activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT_mtvec & 0x60; // 13 14
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 38 npc_DOT_lsu_DOT_mtvec: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mtvec);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[4] & 0x80)) { // id=39
    uint32_t npc_DOT_lsu_DOT_mcause_DOT_old_DOT_2406 = npc_DOT_lsu_DOT_mcause;
    npc_DOT_lsu_DOT_mcause = npc_DOT_lsu_DOT_mcause_DOT_NEXT;
    bool cond_npc_DOT_lsu_DOT_mcause = npc_DOT_lsu_DOT_mcause != npc_DOT_lsu_DOT_mcause_DOT_old_DOT_2406;
    activeFlags[1] |= cond_npc_DOT_lsu_DOT_mcause << 6; // 14
    uint32_t npc_DOT_lsu_DOT_mepc_DOT_old_DOT_2408 = npc_DOT_lsu_DOT_mepc;
    npc_DOT_lsu_DOT_mepc = npc_DOT_lsu_DOT_mepc_DOT_NEXT;
    bool cond_npc_DOT_lsu_DOT_mepc = npc_DOT_lsu_DOT_mepc != npc_DOT_lsu_DOT_mepc_DOT_old_DOT_2408;
    activeFlags[1] |= -(uint8_t)cond_npc_DOT_lsu_DOT_mepc & 0x60; // 13 14
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 39 npc_DOT_lsu_DOT_mcause: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mcause);
      printf("\n");
    }
#endif
#ifdef ENABLE_LOG
    if (cycles >= LOG_START && cycles <= LOG_END) {
      printf("%ld 39 npc_DOT_lsu_DOT_mepc: ", cycles);
      printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mepc);
      printf("\n");
    }
#endif
  }
  if (unlikely(activeFlags[5] != 0)) {
    uint8_t oldFlag = activeFlags[5];
    activeFlags[5] = 0;
    if (unlikely(oldFlag & 0x1)) { // id=40
      uint32_t npc_DOT_lsu_DOT_mcycle_DOT_old_DOT_2409 = npc_DOT_lsu_DOT_mcycle;
      npc_DOT_lsu_DOT_mcycle = npc_DOT_lsu_DOT_mcycle_DOT_NEXT;
      bool cond_npc_DOT_lsu_DOT_mcycle = npc_DOT_lsu_DOT_mcycle != npc_DOT_lsu_DOT_mcycle_DOT_old_DOT_2409;
      *(uint16_t *)&activeFlags[0] |= -(uint16_t)cond_npc_DOT_lsu_DOT_mcycle & 0x4008; // 14 3
      uint64_t npc_DOT_clint_DOT_cnt_DOT_old_DOT_2425 = npc_DOT_clint_DOT_cnt;
      npc_DOT_clint_DOT_cnt = npc_DOT_clint_DOT_cnt_DOT_NEXT;
      bool cond_npc_DOT_clint_DOT_cnt = npc_DOT_clint_DOT_cnt != npc_DOT_clint_DOT_cnt_DOT_old_DOT_2425;
      *(uint64_t *)&activeFlags[0] |= -(uint64_t)cond_npc_DOT_clint_DOT_cnt & 0x400000008; // 34 3
      uint8_t npc_DOT_npctrap_io_valid_REG_DOT_old_DOT_2436 = npc_DOT_npctrap_io_valid_REG;
      npc_DOT_npctrap_io_valid_REG = npc_DOT_npctrap_io_valid_REG_DOT_NEXT;
      bool cond_npc_DOT_npctrap_io_valid_REG =
          npc_DOT_npctrap_io_valid_REG ^ npc_DOT_npctrap_io_valid_REG_DOT_old_DOT_2436;
      activeFlags[0] |= cond_npc_DOT_npctrap_io_valid_REG << 5; // 5
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 40 npc_DOT_lsu_DOT_mcycle: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_mcycle);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 40 npc_DOT_clint_DOT_cnt: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_clint_DOT_cnt);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 40 npc_DOT_npctrap_io_valid_REG: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_npctrap_io_valid_REG);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x2)) { // id=41
      uint32_t npc_DOT_lsu_DOT_marchid_DOT_old_DOT_2411 = npc_DOT_lsu_DOT_marchid;
      npc_DOT_lsu_DOT_marchid = npc_DOT_lsu_DOT_marchid_DOT_NEXT;
      bool cond_npc_DOT_lsu_DOT_marchid = npc_DOT_lsu_DOT_marchid != npc_DOT_lsu_DOT_marchid_DOT_old_DOT_2411;
      activeFlags[1] |= cond_npc_DOT_lsu_DOT_marchid << 6; // 14
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 41 npc_DOT_lsu_DOT_marchid: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_lsu_DOT_marchid);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x4)) { // id=42
      uint32_t npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_old_DOT_2412 = npc_DOT_idu_io_in_bits_r_DOT__DOT_pc;
      npc_DOT_idu_io_in_bits_r_DOT__DOT_pc = npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_NEXT;
      bool cond_npc_DOT_idu_io_in_bits_r_DOT__DOT_pc =
          npc_DOT_idu_io_in_bits_r_DOT__DOT_pc != npc_DOT_idu_io_in_bits_r_DOT__DOT_pc_DOT_old_DOT_2412;
      activeFlags[3] |= cond_npc_DOT_idu_io_in_bits_r_DOT__DOT_pc << 2; // 26
      uint32_t npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_old_DOT_2413 = npc_DOT_idu_io_in_bits_r_DOT__DOT_inst;
      npc_DOT_idu_io_in_bits_r_DOT__DOT_inst = npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_NEXT;
      bool cond_npc_DOT_idu_io_in_bits_r_DOT__DOT_inst =
          npc_DOT_idu_io_in_bits_r_DOT__DOT_inst != npc_DOT_idu_io_in_bits_r_DOT__DOT_inst_DOT_old_DOT_2413;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_idu_io_in_bits_r_DOT__DOT_inst & 0x4010000; // 26 16
      uint8_t npc_DOT_idu_io_in_valid_REG_DOT_old_DOT_2414 = npc_DOT_idu_io_in_valid_REG;
      npc_DOT_idu_io_in_valid_REG = npc_DOT_idu_io_in_valid_REG_DOT_NEXT;
      bool cond_npc_DOT_idu_io_in_valid_REG =
          npc_DOT_idu_io_in_valid_REG ^ npc_DOT_idu_io_in_valid_REG_DOT_old_DOT_2414;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_idu_io_in_valid_REG & 0x4400000; // 26 22
      uint8_t npc_DOT_exu_io_in_valid_REG_DOT_old_DOT_2416 = npc_DOT_exu_io_in_valid_REG;
      npc_DOT_exu_io_in_valid_REG = npc_DOT_exu_io_in_valid_REG_DOT_NEXT;
      bool cond_npc_DOT_exu_io_in_valid_REG =
          npc_DOT_exu_io_in_valid_REG ^ npc_DOT_exu_io_in_valid_REG_DOT_old_DOT_2416;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_exu_io_in_valid_REG & 0x80600800; // 31 22 21 11
      uint32_t npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_old_DOT_2440 = npc_DOT_deq_q_DOT_ram_DOT__DOT_pc;
      npc_DOT_deq_q_DOT_ram_DOT__DOT_pc = npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_NEXT;
      bool cond_npc_DOT_deq_q_DOT_ram_DOT__DOT_pc =
          npc_DOT_deq_q_DOT_ram_DOT__DOT_pc != npc_DOT_deq_q_DOT_ram_DOT__DOT_pc_DOT_old_DOT_2440;
      activeFlags[2] |= cond_npc_DOT_deq_q_DOT_ram_DOT__DOT_pc << 6; // 22
      uint32_t npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_old_DOT_2441 = npc_DOT_deq_q_DOT_ram_DOT__DOT_inst;
      npc_DOT_deq_q_DOT_ram_DOT__DOT_inst = npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_NEXT;
      bool cond_npc_DOT_deq_q_DOT_ram_DOT__DOT_inst =
          npc_DOT_deq_q_DOT_ram_DOT__DOT_inst != npc_DOT_deq_q_DOT_ram_DOT__DOT_inst_DOT_old_DOT_2441;
      activeFlags[2] |= cond_npc_DOT_deq_q_DOT_ram_DOT__DOT_inst << 6; // 22
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 42 npc_DOT_idu_io_in_bits_r_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_io_in_bits_r_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 42 npc_DOT_idu_io_in_bits_r_DOT__DOT_inst: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_io_in_bits_r_DOT__DOT_inst);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 42 npc_DOT_idu_io_in_valid_REG: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_idu_io_in_valid_REG);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 42 npc_DOT_exu_io_in_valid_REG: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_valid_REG);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 42 npc_DOT_deq_q_DOT_ram_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_ram_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 42 npc_DOT_deq_q_DOT_ram_DOT__DOT_inst: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_deq_q_DOT_ram_DOT__DOT_inst);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x8)) { // id=43
      uint8_t npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_old_DOT_2415 =
          npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei;
      npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei =
          npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_NEXT;
      bool cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei =
          npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei ^
          npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei_DOT_old_DOT_2415;
      activeFlags[3] |= -(uint8_t)cond_npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei & 0x82; // 25 31
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 43 npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_exu_io_in_bits_r_DOT__DOT_decode_DOT__DOT_isFencei);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x10)) { // id=44
      uint32_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_old_DOT_2417 = npc_DOT_wbu_io_in_bits_r_DOT__DOT_res;
      npc_DOT_wbu_io_in_bits_r_DOT__DOT_res = npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_NEXT;
      bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_res =
          npc_DOT_wbu_io_in_bits_r_DOT__DOT_res != npc_DOT_wbu_io_in_bits_r_DOT__DOT_res_DOT_old_DOT_2417;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_res & 0x4010000; // 26 16
      uint8_t npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_old_DOT_2418 = npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd;
      npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd = npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_NEXT;
      bool cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd =
          npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd != npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd_DOT_old_DOT_2418;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd & 0x4010000; // 26 16
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 44 npc_DOT_wbu_io_in_bits_r_DOT__DOT_res: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_res);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 44 npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_wbu_io_in_bits_r_DOT__DOT_rd);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x20)) { // id=45
      uint8_t npc_DOT_icache_DOT_beatCnt_value_DOT_old_DOT_2421 = npc_DOT_icache_DOT_beatCnt_value;
      npc_DOT_icache_DOT_beatCnt_value = npc_DOT_icache_DOT_beatCnt_value_DOT_NEXT;
      bool cond_npc_DOT_icache_DOT_beatCnt_value =
          npc_DOT_icache_DOT_beatCnt_value != npc_DOT_icache_DOT_beatCnt_value_DOT_old_DOT_2421;
      *(uint64_t *)&activeFlags[0] |= -(uint64_t)cond_npc_DOT_icache_DOT_beatCnt_value & 0x400120000; // 34 17 20
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 45 npc_DOT_icache_DOT_beatCnt_value: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_beatCnt_value);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x40)) { // id=46
      uint8_t npc_DOT_icache_DOT_flushReg_DOT_old_DOT_2422 = npc_DOT_icache_DOT_flushReg;
      npc_DOT_icache_DOT_flushReg = npc_DOT_icache_DOT_flushReg_DOT_NEXT;
      bool cond_npc_DOT_icache_DOT_flushReg =
          npc_DOT_icache_DOT_flushReg ^ npc_DOT_icache_DOT_flushReg_DOT_old_DOT_2422;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_icache_DOT_flushReg & 0x40100000; // 30 20
      uint8_t mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_old_DOT_2438 = mem_DOT_axi4memctrl_DOT_awsizeReg;
      mem_DOT_axi4memctrl_DOT_awsizeReg = mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_NEXT;
      bool cond_mem_DOT_axi4memctrl_DOT_awsizeReg =
          mem_DOT_axi4memctrl_DOT_awsizeReg != mem_DOT_axi4memctrl_DOT_awsizeReg_DOT_old_DOT_2438;
      activeFlags[3] |= cond_mem_DOT_axi4memctrl_DOT_awsizeReg << 3; // 27
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 46 npc_DOT_icache_DOT_flushReg: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_icache_DOT_flushReg);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 46 mem_DOT_axi4memctrl_DOT_awsizeReg: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_awsizeReg);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x80)) { // id=47
      uint8_t npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_old_DOT_2423 = npc_DOT_xbar_DOT_chosenReadIdxReg_s1;
      npc_DOT_xbar_DOT_chosenReadIdxReg_s1 = npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_NEXT;
      bool cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s1 =
          npc_DOT_xbar_DOT_chosenReadIdxReg_s1 ^ npc_DOT_xbar_DOT_chosenReadIdxReg_s1_DOT_old_DOT_2423;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_npc_DOT_xbar_DOT_chosenReadIdxReg_s1 & 0x20040010; // 29 18 4
      uint8_t npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_old_DOT_2424 = npc_DOT_xbar2_DOT_arSelIdx_s1;
      npc_DOT_xbar2_DOT_arSelIdx_s1 = npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_NEXT;
      bool cond_npc_DOT_xbar2_DOT_arSelIdx_s1 =
          npc_DOT_xbar2_DOT_arSelIdx_s1 ^ npc_DOT_xbar2_DOT_arSelIdx_s1_DOT_old_DOT_2424;
      *(uint64_t *)&activeFlags[0] |= -(uint64_t)cond_npc_DOT_xbar2_DOT_arSelIdx_s1 & 0x430000010; // 34 29 28 4
      uint8_t mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_old_DOT_2437 = mem_DOT_axi4memctrl_DOT_arsizeReg;
      mem_DOT_axi4memctrl_DOT_arsizeReg = mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_NEXT;
      bool cond_mem_DOT_axi4memctrl_DOT_arsizeReg =
          mem_DOT_axi4memctrl_DOT_arsizeReg != mem_DOT_axi4memctrl_DOT_arsizeReg_DOT_old_DOT_2437;
      activeFlags[4] |= cond_mem_DOT_axi4memctrl_DOT_arsizeReg << 3; // 35
      uint8_t npc_DOT_xbar2_DOT_arSel_s1_1_DOT_old_DOT_2442 = npc_DOT_xbar2_DOT_arSel_s1_1;
      npc_DOT_xbar2_DOT_arSel_s1_1 = npc_DOT_xbar2_DOT_arSel_s1_DOT_NEXT_1;
      bool cond_npc_DOT_xbar2_DOT_arSel_s1_1 =
          npc_DOT_xbar2_DOT_arSel_s1_1 ^ npc_DOT_xbar2_DOT_arSel_s1_1_DOT_old_DOT_2442;
      *(uint64_t *)&activeFlags[0] |= -(uint64_t)cond_npc_DOT_xbar2_DOT_arSel_s1_1 & 0x880000000; // 35 31
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 47 npc_DOT_xbar_DOT_chosenReadIdxReg_s1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar_DOT_chosenReadIdxReg_s1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 47 npc_DOT_xbar2_DOT_arSelIdx_s1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSelIdx_s1);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 47 mem_DOT_axi4memctrl_DOT_arsizeReg: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_arsizeReg);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 47 npc_DOT_xbar2_DOT_arSel_s1_1: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_xbar2_DOT_arSel_s1_1);
        printf("\n");
      }
#endif
    }
  }
  if (unlikely(activeFlags[6] != 0)) {
    uint8_t oldFlag = activeFlags[6];
    activeFlags[6] = 0;
    if (unlikely(oldFlag & 0x1)) { // id=48
      uint8_t npc_DOT_clint_DOT_state_DOT_old_DOT_2426 = npc_DOT_clint_DOT_state;
      npc_DOT_clint_DOT_state = npc_DOT_clint_DOT_state_DOT_NEXT;
      bool cond_npc_DOT_clint_DOT_state = npc_DOT_clint_DOT_state ^ npc_DOT_clint_DOT_state_DOT_old_DOT_2426;
      activeFlags[0] |= -(uint8_t)cond_npc_DOT_clint_DOT_state & 0xc; // 2 3
      uint8_t npc_DOT_clint_DOT_isMtimeReg_DOT_old_DOT_2427 = npc_DOT_clint_DOT_isMtimeReg;
      npc_DOT_clint_DOT_isMtimeReg = npc_DOT_clint_DOT_isMtimeReg_DOT_NEXT;
      bool cond_npc_DOT_clint_DOT_isMtimeReg =
          npc_DOT_clint_DOT_isMtimeReg ^ npc_DOT_clint_DOT_isMtimeReg_DOT_old_DOT_2427;
      activeFlags[4] |= cond_npc_DOT_clint_DOT_isMtimeReg << 2; // 34
      uint8_t npc_DOT_clint_DOT_isMtimehReg_DOT_old_DOT_2428 = npc_DOT_clint_DOT_isMtimehReg;
      npc_DOT_clint_DOT_isMtimehReg = npc_DOT_clint_DOT_isMtimehReg_DOT_NEXT;
      bool cond_npc_DOT_clint_DOT_isMtimehReg =
          npc_DOT_clint_DOT_isMtimehReg ^ npc_DOT_clint_DOT_isMtimehReg_DOT_old_DOT_2428;
      activeFlags[4] |= cond_npc_DOT_clint_DOT_isMtimehReg << 2; // 34
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 48 npc_DOT_clint_DOT_state: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_clint_DOT_state);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 48 npc_DOT_clint_DOT_isMtimeReg: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_clint_DOT_isMtimeReg);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 48 npc_DOT_clint_DOT_isMtimehReg: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_clint_DOT_isMtimehReg);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x2)) { // id=49
      uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_old_DOT_2429 = npc_DOT_npctrap_io_REG_DOT__DOT_pc;
      npc_DOT_npctrap_io_REG_DOT__DOT_pc = npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_NEXT;
      bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_pc =
          npc_DOT_npctrap_io_REG_DOT__DOT_pc != npc_DOT_npctrap_io_REG_DOT__DOT_pc_DOT_old_DOT_2429;
      activeFlags[0] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_pc << 5; // 5
      uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_old_DOT_2435 = npc_DOT_npctrap_io_REG_DOT__DOT_skip;
      npc_DOT_npctrap_io_REG_DOT__DOT_skip = npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_NEXT;
      bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_skip =
          npc_DOT_npctrap_io_REG_DOT__DOT_skip ^ npc_DOT_npctrap_io_REG_DOT__DOT_skip_DOT_old_DOT_2435;
      activeFlags[0] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_skip << 5; // 5
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 49 npc_DOT_npctrap_io_REG_DOT__DOT_pc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_pc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 49 npc_DOT_npctrap_io_REG_DOT__DOT_skip: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_skip);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x4)) { // id=50
      uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_old_DOT_2430 = npc_DOT_npctrap_io_REG_DOT__DOT_dnpc;
      npc_DOT_npctrap_io_REG_DOT__DOT_dnpc = npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_NEXT;
      bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_dnpc =
          npc_DOT_npctrap_io_REG_DOT__DOT_dnpc != npc_DOT_npctrap_io_REG_DOT__DOT_dnpc_DOT_old_DOT_2430;
      activeFlags[0] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_dnpc << 5; // 5
      uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_old_DOT_2431 = npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak;
      npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak = npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_NEXT;
      bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak =
          npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak ^ npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak_DOT_old_DOT_2431;
      activeFlags[0] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak << 5; // 5
      uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_old_DOT_2432 = npc_DOT_npctrap_io_REG_DOT__DOT_code;
      npc_DOT_npctrap_io_REG_DOT__DOT_code = npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_NEXT;
      bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_code =
          npc_DOT_npctrap_io_REG_DOT__DOT_code != npc_DOT_npctrap_io_REG_DOT__DOT_code_DOT_old_DOT_2432;
      activeFlags[0] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_code << 5; // 5
      uint8_t npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_old_DOT_2433 = npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO;
      npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO = npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_NEXT;
      bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO =
          npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO ^ npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO_DOT_old_DOT_2433;
      activeFlags[0] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO << 5; // 5
      uint32_t npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_old_DOT_2434 = npc_DOT_npctrap_io_REG_DOT__DOT_memAddr;
      npc_DOT_npctrap_io_REG_DOT__DOT_memAddr = npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_NEXT;
      bool cond_npc_DOT_npctrap_io_REG_DOT__DOT_memAddr =
          npc_DOT_npctrap_io_REG_DOT__DOT_memAddr != npc_DOT_npctrap_io_REG_DOT__DOT_memAddr_DOT_old_DOT_2434;
      activeFlags[0] |= cond_npc_DOT_npctrap_io_REG_DOT__DOT_memAddr << 5; // 5
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 50 npc_DOT_npctrap_io_REG_DOT__DOT_dnpc: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_dnpc);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 50 npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_isEbreak);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 50 npc_DOT_npctrap_io_REG_DOT__DOT_code: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_code);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 50 npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_isMMIO);
        printf("\n");
      }
#endif
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 50 npc_DOT_npctrap_io_REG_DOT__DOT_memAddr: ", cycles);
        printf("%lx", (uint64_t)npc_DOT_npctrap_io_REG_DOT__DOT_memAddr);
        printf("\n");
      }
#endif
    }
    if (unlikely(oldFlag & 0x8)) { // id=51
      uint8_t mem_DOT_axi4memctrl_DOT_state_w_DOT_old_DOT_2439 = mem_DOT_axi4memctrl_DOT_state_w;
      mem_DOT_axi4memctrl_DOT_state_w = mem_DOT_axi4memctrl_DOT_state_w_DOT_NEXT;
      bool cond_mem_DOT_axi4memctrl_DOT_state_w =
          mem_DOT_axi4memctrl_DOT_state_w != mem_DOT_axi4memctrl_DOT_state_w_DOT_old_DOT_2439;
      *(uint32_t *)&activeFlags[0] |= -(uint32_t)cond_mem_DOT_axi4memctrl_DOT_state_w & 0x8000408; // 27 10 3
#ifdef ENABLE_LOG
      if (cycles >= LOG_START && cycles <= LOG_END) {
        printf("%ld 51 mem_DOT_axi4memctrl_DOT_state_w: ", cycles);
        printf("%lx", (uint64_t)mem_DOT_axi4memctrl_DOT_state_w);
        printf("\n");
      }
#endif
    }
  }
}
void step() {
  subStep0();
  resetAll();
  cycles++;
}
