// Generated by vsg 01042

`timescale 100ps / 100ps
module cy7c04314bv_mx(
  clkp1,
  clkp2,
  clkp3,
  clkp4,
  oep1_n,
  oep2_n,
  oep3_n,
  oep4_n,
  r_w_np1,
  r_w_np2,
  r_w_np3,
  r_w_np4,
  ce0p1_n,
  ce0p2_n,
  ce0p3_n,
  ce0p4_n,
  ce1p1,
  ce1p2,
  ce1p3,
  ce1p4,
  intp1_n,
  intp2_n,
  intp3_n,
  intp4_n,
  mrst_n,
  iop1_0,
  iop1_1,
  iop1_2,
  iop1_3,
  iop1_4,
  iop1_5,
  iop1_6,
  iop1_7,
  iop1_8,
  iop1_9,
  iop1_10,
  iop1_11,
  iop1_12,
  iop1_13,
  iop1_14,
  iop1_15,
  iop1_16,
  iop1_17,
  iop2_0,
  iop2_1,
  iop2_2,
  iop2_3,
  iop2_4,
  iop2_5,
  iop2_6,
  iop2_7,
  iop2_8,
  iop2_9,
  iop2_10,
  iop2_11,
  iop2_12,
  iop2_13,
  iop2_14,
  iop2_15,
  iop2_16,
  iop2_17,
  iop3_0,
  iop3_1,
  iop3_2,
  iop3_3,
  iop3_4,
  iop3_5,
  iop3_6,
  iop3_7,
  iop3_8,
  iop3_9,
  iop3_10,
  iop3_11,
  iop3_12,
  iop3_13,
  iop3_14,
  iop3_15,
  iop3_16,
  iop3_17,
  iop4_0,
  iop4_1,
  iop4_2,
  iop4_3,
  iop4_4,
  iop4_5,
  iop4_6,
  iop4_7,
  iop4_8,
  iop4_9,
  iop4_10,
  iop4_11,
  iop4_12,
  iop4_13,
  iop4_14,
  iop4_15,
  iop4_16,
  iop4_17,
  bep1_n_0,
  bep1_n_1,
  bep2_n_0,
  bep2_n_1,
  bep3_n_0,
  bep3_n_1,
  bep4_n_0,
  bep4_n_1,
  ap1_0,
  ap1_1,
  ap1_2,
  ap1_3,
  ap1_4,
  ap1_5,
  ap1_6,
  ap1_7,
  ap1_8,
  ap1_9,
  ap1_10,
  ap1_11,
  ap1_12,
  ap1_13,
  ap2_0,
  ap2_1,
  ap2_2,
  ap2_3,
  ap2_4,
  ap2_5,
  ap2_6,
  ap2_7,
  ap2_8,
  ap2_9,
  ap2_10,
  ap2_11,
  ap2_12,
  ap2_13,
  ap3_0,
  ap3_1,
  ap3_2,
  ap3_3,
  ap3_4,
  ap3_5,
  ap3_6,
  ap3_7,
  ap3_8,
  ap3_9,
  ap3_10,
  ap3_11,
  ap3_12,
  ap3_13,
  ap4_0,
  ap4_1,
  ap4_2,
  ap4_3,
  ap4_4,
  ap4_5,
  ap4_6,
  ap4_7,
  ap4_8,
  ap4_9,
  ap4_10,
  ap4_11,
  ap4_12,
  ap4_13 );

  // Pin declarations 
  input  clkp1;
  input  clkp2;
  input  clkp3;
  input  clkp4;
  input  oep1_n;
  input  oep2_n;
  input  oep3_n;
  input  oep4_n;
  input  r_w_np1;
  input  r_w_np2;
  input  r_w_np3;
  input  r_w_np4;
  input  ce0p1_n;
  input  ce0p2_n;
  input  ce0p3_n;
  input  ce0p4_n;
  input  ce1p1;
  input  ce1p2;
  input  ce1p3;
  input  ce1p4;
  output intp1_n;
  reg    intp1_n__PULL;
  reg    intp1_n__STRONG;
  assign (pull0, pull1) intp1_n = intp1_n__PULL;
  assign intp1_n = intp1_n__STRONG;
  output intp2_n;
  reg    intp2_n__PULL;
  reg    intp2_n__STRONG;
  assign (pull0, pull1) intp2_n = intp2_n__PULL;
  assign intp2_n = intp2_n__STRONG;
  output intp3_n;
  reg    intp3_n__PULL;
  reg    intp3_n__STRONG;
  assign (pull0, pull1) intp3_n = intp3_n__PULL;
  assign intp3_n = intp3_n__STRONG;
  output intp4_n;
  reg    intp4_n__PULL;
  reg    intp4_n__STRONG;
  assign (pull0, pull1) intp4_n = intp4_n__PULL;
  assign intp4_n = intp4_n__STRONG;
  input  mrst_n;
  inout  iop1_0;
  reg    iop1_0__PULL;
  reg    iop1_0__STRONG;
  assign (pull0, pull1) iop1_0 = iop1_0__PULL;
  assign iop1_0 = iop1_0__STRONG;
  inout  iop1_1;
  reg    iop1_1__PULL;
  reg    iop1_1__STRONG;
  assign (pull0, pull1) iop1_1 = iop1_1__PULL;
  assign iop1_1 = iop1_1__STRONG;
  inout  iop1_2;
  reg    iop1_2__PULL;
  reg    iop1_2__STRONG;
  assign (pull0, pull1) iop1_2 = iop1_2__PULL;
  assign iop1_2 = iop1_2__STRONG;
  inout  iop1_3;
  reg    iop1_3__PULL;
  reg    iop1_3__STRONG;
  assign (pull0, pull1) iop1_3 = iop1_3__PULL;
  assign iop1_3 = iop1_3__STRONG;
  inout  iop1_4;
  reg    iop1_4__PULL;
  reg    iop1_4__STRONG;
  assign (pull0, pull1) iop1_4 = iop1_4__PULL;
  assign iop1_4 = iop1_4__STRONG;
  inout  iop1_5;
  reg    iop1_5__PULL;
  reg    iop1_5__STRONG;
  assign (pull0, pull1) iop1_5 = iop1_5__PULL;
  assign iop1_5 = iop1_5__STRONG;
  inout  iop1_6;
  reg    iop1_6__PULL;
  reg    iop1_6__STRONG;
  assign (pull0, pull1) iop1_6 = iop1_6__PULL;
  assign iop1_6 = iop1_6__STRONG;
  inout  iop1_7;
  reg    iop1_7__PULL;
  reg    iop1_7__STRONG;
  assign (pull0, pull1) iop1_7 = iop1_7__PULL;
  assign iop1_7 = iop1_7__STRONG;
  inout  iop1_8;
  reg    iop1_8__PULL;
  reg    iop1_8__STRONG;
  assign (pull0, pull1) iop1_8 = iop1_8__PULL;
  assign iop1_8 = iop1_8__STRONG;
  inout  iop1_9;
  reg    iop1_9__PULL;
  reg    iop1_9__STRONG;
  assign (pull0, pull1) iop1_9 = iop1_9__PULL;
  assign iop1_9 = iop1_9__STRONG;
  inout  iop1_10;
  reg    iop1_10__PULL;
  reg    iop1_10__STRONG;
  assign (pull0, pull1) iop1_10 = iop1_10__PULL;
  assign iop1_10 = iop1_10__STRONG;
  inout  iop1_11;
  reg    iop1_11__PULL;
  reg    iop1_11__STRONG;
  assign (pull0, pull1) iop1_11 = iop1_11__PULL;
  assign iop1_11 = iop1_11__STRONG;
  inout  iop1_12;
  reg    iop1_12__PULL;
  reg    iop1_12__STRONG;
  assign (pull0, pull1) iop1_12 = iop1_12__PULL;
  assign iop1_12 = iop1_12__STRONG;
  inout  iop1_13;
  reg    iop1_13__PULL;
  reg    iop1_13__STRONG;
  assign (pull0, pull1) iop1_13 = iop1_13__PULL;
  assign iop1_13 = iop1_13__STRONG;
  inout  iop1_14;
  reg    iop1_14__PULL;
  reg    iop1_14__STRONG;
  assign (pull0, pull1) iop1_14 = iop1_14__PULL;
  assign iop1_14 = iop1_14__STRONG;
  inout  iop1_15;
  reg    iop1_15__PULL;
  reg    iop1_15__STRONG;
  assign (pull0, pull1) iop1_15 = iop1_15__PULL;
  assign iop1_15 = iop1_15__STRONG;
  inout  iop1_16;
  reg    iop1_16__PULL;
  reg    iop1_16__STRONG;
  assign (pull0, pull1) iop1_16 = iop1_16__PULL;
  assign iop1_16 = iop1_16__STRONG;
  inout  iop1_17;
  reg    iop1_17__PULL;
  reg    iop1_17__STRONG;
  assign (pull0, pull1) iop1_17 = iop1_17__PULL;
  assign iop1_17 = iop1_17__STRONG;
  inout  iop2_0;
  reg    iop2_0__PULL;
  reg    iop2_0__STRONG;
  assign (pull0, pull1) iop2_0 = iop2_0__PULL;
  assign iop2_0 = iop2_0__STRONG;
  inout  iop2_1;
  reg    iop2_1__PULL;
  reg    iop2_1__STRONG;
  assign (pull0, pull1) iop2_1 = iop2_1__PULL;
  assign iop2_1 = iop2_1__STRONG;
  inout  iop2_2;
  reg    iop2_2__PULL;
  reg    iop2_2__STRONG;
  assign (pull0, pull1) iop2_2 = iop2_2__PULL;
  assign iop2_2 = iop2_2__STRONG;
  inout  iop2_3;
  reg    iop2_3__PULL;
  reg    iop2_3__STRONG;
  assign (pull0, pull1) iop2_3 = iop2_3__PULL;
  assign iop2_3 = iop2_3__STRONG;
  inout  iop2_4;
  reg    iop2_4__PULL;
  reg    iop2_4__STRONG;
  assign (pull0, pull1) iop2_4 = iop2_4__PULL;
  assign iop2_4 = iop2_4__STRONG;
  inout  iop2_5;
  reg    iop2_5__PULL;
  reg    iop2_5__STRONG;
  assign (pull0, pull1) iop2_5 = iop2_5__PULL;
  assign iop2_5 = iop2_5__STRONG;
  inout  iop2_6;
  reg    iop2_6__PULL;
  reg    iop2_6__STRONG;
  assign (pull0, pull1) iop2_6 = iop2_6__PULL;
  assign iop2_6 = iop2_6__STRONG;
  inout  iop2_7;
  reg    iop2_7__PULL;
  reg    iop2_7__STRONG;
  assign (pull0, pull1) iop2_7 = iop2_7__PULL;
  assign iop2_7 = iop2_7__STRONG;
  inout  iop2_8;
  reg    iop2_8__PULL;
  reg    iop2_8__STRONG;
  assign (pull0, pull1) iop2_8 = iop2_8__PULL;
  assign iop2_8 = iop2_8__STRONG;
  inout  iop2_9;
  reg    iop2_9__PULL;
  reg    iop2_9__STRONG;
  assign (pull0, pull1) iop2_9 = iop2_9__PULL;
  assign iop2_9 = iop2_9__STRONG;
  inout  iop2_10;
  reg    iop2_10__PULL;
  reg    iop2_10__STRONG;
  assign (pull0, pull1) iop2_10 = iop2_10__PULL;
  assign iop2_10 = iop2_10__STRONG;
  inout  iop2_11;
  reg    iop2_11__PULL;
  reg    iop2_11__STRONG;
  assign (pull0, pull1) iop2_11 = iop2_11__PULL;
  assign iop2_11 = iop2_11__STRONG;
  inout  iop2_12;
  reg    iop2_12__PULL;
  reg    iop2_12__STRONG;
  assign (pull0, pull1) iop2_12 = iop2_12__PULL;
  assign iop2_12 = iop2_12__STRONG;
  inout  iop2_13;
  reg    iop2_13__PULL;
  reg    iop2_13__STRONG;
  assign (pull0, pull1) iop2_13 = iop2_13__PULL;
  assign iop2_13 = iop2_13__STRONG;
  inout  iop2_14;
  reg    iop2_14__PULL;
  reg    iop2_14__STRONG;
  assign (pull0, pull1) iop2_14 = iop2_14__PULL;
  assign iop2_14 = iop2_14__STRONG;
  inout  iop2_15;
  reg    iop2_15__PULL;
  reg    iop2_15__STRONG;
  assign (pull0, pull1) iop2_15 = iop2_15__PULL;
  assign iop2_15 = iop2_15__STRONG;
  inout  iop2_16;
  reg    iop2_16__PULL;
  reg    iop2_16__STRONG;
  assign (pull0, pull1) iop2_16 = iop2_16__PULL;
  assign iop2_16 = iop2_16__STRONG;
  inout  iop2_17;
  reg    iop2_17__PULL;
  reg    iop2_17__STRONG;
  assign (pull0, pull1) iop2_17 = iop2_17__PULL;
  assign iop2_17 = iop2_17__STRONG;
  inout  iop3_0;
  reg    iop3_0__PULL;
  reg    iop3_0__STRONG;
  assign (pull0, pull1) iop3_0 = iop3_0__PULL;
  assign iop3_0 = iop3_0__STRONG;
  inout  iop3_1;
  reg    iop3_1__PULL;
  reg    iop3_1__STRONG;
  assign (pull0, pull1) iop3_1 = iop3_1__PULL;
  assign iop3_1 = iop3_1__STRONG;
  inout  iop3_2;
  reg    iop3_2__PULL;
  reg    iop3_2__STRONG;
  assign (pull0, pull1) iop3_2 = iop3_2__PULL;
  assign iop3_2 = iop3_2__STRONG;
  inout  iop3_3;
  reg    iop3_3__PULL;
  reg    iop3_3__STRONG;
  assign (pull0, pull1) iop3_3 = iop3_3__PULL;
  assign iop3_3 = iop3_3__STRONG;
  inout  iop3_4;
  reg    iop3_4__PULL;
  reg    iop3_4__STRONG;
  assign (pull0, pull1) iop3_4 = iop3_4__PULL;
  assign iop3_4 = iop3_4__STRONG;
  inout  iop3_5;
  reg    iop3_5__PULL;
  reg    iop3_5__STRONG;
  assign (pull0, pull1) iop3_5 = iop3_5__PULL;
  assign iop3_5 = iop3_5__STRONG;
  inout  iop3_6;
  reg    iop3_6__PULL;
  reg    iop3_6__STRONG;
  assign (pull0, pull1) iop3_6 = iop3_6__PULL;
  assign iop3_6 = iop3_6__STRONG;
  inout  iop3_7;
  reg    iop3_7__PULL;
  reg    iop3_7__STRONG;
  assign (pull0, pull1) iop3_7 = iop3_7__PULL;
  assign iop3_7 = iop3_7__STRONG;
  inout  iop3_8;
  reg    iop3_8__PULL;
  reg    iop3_8__STRONG;
  assign (pull0, pull1) iop3_8 = iop3_8__PULL;
  assign iop3_8 = iop3_8__STRONG;
  inout  iop3_9;
  reg    iop3_9__PULL;
  reg    iop3_9__STRONG;
  assign (pull0, pull1) iop3_9 = iop3_9__PULL;
  assign iop3_9 = iop3_9__STRONG;
  inout  iop3_10;
  reg    iop3_10__PULL;
  reg    iop3_10__STRONG;
  assign (pull0, pull1) iop3_10 = iop3_10__PULL;
  assign iop3_10 = iop3_10__STRONG;
  inout  iop3_11;
  reg    iop3_11__PULL;
  reg    iop3_11__STRONG;
  assign (pull0, pull1) iop3_11 = iop3_11__PULL;
  assign iop3_11 = iop3_11__STRONG;
  inout  iop3_12;
  reg    iop3_12__PULL;
  reg    iop3_12__STRONG;
  assign (pull0, pull1) iop3_12 = iop3_12__PULL;
  assign iop3_12 = iop3_12__STRONG;
  inout  iop3_13;
  reg    iop3_13__PULL;
  reg    iop3_13__STRONG;
  assign (pull0, pull1) iop3_13 = iop3_13__PULL;
  assign iop3_13 = iop3_13__STRONG;
  inout  iop3_14;
  reg    iop3_14__PULL;
  reg    iop3_14__STRONG;
  assign (pull0, pull1) iop3_14 = iop3_14__PULL;
  assign iop3_14 = iop3_14__STRONG;
  inout  iop3_15;
  reg    iop3_15__PULL;
  reg    iop3_15__STRONG;
  assign (pull0, pull1) iop3_15 = iop3_15__PULL;
  assign iop3_15 = iop3_15__STRONG;
  inout  iop3_16;
  reg    iop3_16__PULL;
  reg    iop3_16__STRONG;
  assign (pull0, pull1) iop3_16 = iop3_16__PULL;
  assign iop3_16 = iop3_16__STRONG;
  inout  iop3_17;
  reg    iop3_17__PULL;
  reg    iop3_17__STRONG;
  assign (pull0, pull1) iop3_17 = iop3_17__PULL;
  assign iop3_17 = iop3_17__STRONG;
  inout  iop4_0;
  reg    iop4_0__PULL;
  reg    iop4_0__STRONG;
  assign (pull0, pull1) iop4_0 = iop4_0__PULL;
  assign iop4_0 = iop4_0__STRONG;
  inout  iop4_1;
  reg    iop4_1__PULL;
  reg    iop4_1__STRONG;
  assign (pull0, pull1) iop4_1 = iop4_1__PULL;
  assign iop4_1 = iop4_1__STRONG;
  inout  iop4_2;
  reg    iop4_2__PULL;
  reg    iop4_2__STRONG;
  assign (pull0, pull1) iop4_2 = iop4_2__PULL;
  assign iop4_2 = iop4_2__STRONG;
  inout  iop4_3;
  reg    iop4_3__PULL;
  reg    iop4_3__STRONG;
  assign (pull0, pull1) iop4_3 = iop4_3__PULL;
  assign iop4_3 = iop4_3__STRONG;
  inout  iop4_4;
  reg    iop4_4__PULL;
  reg    iop4_4__STRONG;
  assign (pull0, pull1) iop4_4 = iop4_4__PULL;
  assign iop4_4 = iop4_4__STRONG;
  inout  iop4_5;
  reg    iop4_5__PULL;
  reg    iop4_5__STRONG;
  assign (pull0, pull1) iop4_5 = iop4_5__PULL;
  assign iop4_5 = iop4_5__STRONG;
  inout  iop4_6;
  reg    iop4_6__PULL;
  reg    iop4_6__STRONG;
  assign (pull0, pull1) iop4_6 = iop4_6__PULL;
  assign iop4_6 = iop4_6__STRONG;
  inout  iop4_7;
  reg    iop4_7__PULL;
  reg    iop4_7__STRONG;
  assign (pull0, pull1) iop4_7 = iop4_7__PULL;
  assign iop4_7 = iop4_7__STRONG;
  inout  iop4_8;
  reg    iop4_8__PULL;
  reg    iop4_8__STRONG;
  assign (pull0, pull1) iop4_8 = iop4_8__PULL;
  assign iop4_8 = iop4_8__STRONG;
  inout  iop4_9;
  reg    iop4_9__PULL;
  reg    iop4_9__STRONG;
  assign (pull0, pull1) iop4_9 = iop4_9__PULL;
  assign iop4_9 = iop4_9__STRONG;
  inout  iop4_10;
  reg    iop4_10__PULL;
  reg    iop4_10__STRONG;
  assign (pull0, pull1) iop4_10 = iop4_10__PULL;
  assign iop4_10 = iop4_10__STRONG;
  inout  iop4_11;
  reg    iop4_11__PULL;
  reg    iop4_11__STRONG;
  assign (pull0, pull1) iop4_11 = iop4_11__PULL;
  assign iop4_11 = iop4_11__STRONG;
  inout  iop4_12;
  reg    iop4_12__PULL;
  reg    iop4_12__STRONG;
  assign (pull0, pull1) iop4_12 = iop4_12__PULL;
  assign iop4_12 = iop4_12__STRONG;
  inout  iop4_13;
  reg    iop4_13__PULL;
  reg    iop4_13__STRONG;
  assign (pull0, pull1) iop4_13 = iop4_13__PULL;
  assign iop4_13 = iop4_13__STRONG;
  inout  iop4_14;
  reg    iop4_14__PULL;
  reg    iop4_14__STRONG;
  assign (pull0, pull1) iop4_14 = iop4_14__PULL;
  assign iop4_14 = iop4_14__STRONG;
  inout  iop4_15;
  reg    iop4_15__PULL;
  reg    iop4_15__STRONG;
  assign (pull0, pull1) iop4_15 = iop4_15__PULL;
  assign iop4_15 = iop4_15__STRONG;
  inout  iop4_16;
  reg    iop4_16__PULL;
  reg    iop4_16__STRONG;
  assign (pull0, pull1) iop4_16 = iop4_16__PULL;
  assign iop4_16 = iop4_16__STRONG;
  inout  iop4_17;
  reg    iop4_17__PULL;
  reg    iop4_17__STRONG;
  assign (pull0, pull1) iop4_17 = iop4_17__PULL;
  assign iop4_17 = iop4_17__STRONG;
  input  bep1_n_0;
  input  bep1_n_1;
  input  bep2_n_0;
  input  bep2_n_1;
  input  bep3_n_0;
  input  bep3_n_1;
  input  bep4_n_0;
  input  bep4_n_1;
  input  ap1_0;
  input  ap1_1;
  input  ap1_2;
  input  ap1_3;
  input  ap1_4;
  input  ap1_5;
  input  ap1_6;
  input  ap1_7;
  input  ap1_8;
  input  ap1_9;
  input  ap1_10;
  input  ap1_11;
  input  ap1_12;
  input  ap1_13;
  input  ap2_0;
  input  ap2_1;
  input  ap2_2;
  input  ap2_3;
  input  ap2_4;
  input  ap2_5;
  input  ap2_6;
  input  ap2_7;
  input  ap2_8;
  input  ap2_9;
  input  ap2_10;
  input  ap2_11;
  input  ap2_12;
  input  ap2_13;
  input  ap3_0;
  input  ap3_1;
  input  ap3_2;
  input  ap3_3;
  input  ap3_4;
  input  ap3_5;
  input  ap3_6;
  input  ap3_7;
  input  ap3_8;
  input  ap3_9;
  input  ap3_10;
  input  ap3_11;
  input  ap3_12;
  input  ap3_13;
  input  ap4_0;
  input  ap4_1;
  input  ap4_2;
  input  ap4_3;
  input  ap4_4;
  input  ap4_5;
  input  ap4_6;
  input  ap4_7;
  input  ap4_8;
  input  ap4_9;
  input  ap4_10;
  input  ap4_11;
  input  ap4_12;
  input  ap4_13;

  // Allowed timing versions: 
  //  Device Name             TimingVersion
  //  ===========             =============

  // Parameter declarations 
  parameter  ModelType = "SWIFT";
  parameter  DefaultData = "111111111111111111";
  parameter  DelayRange = "Max";
  parameter  MemoryFile = ".";
  parameter  MessageLevel = "15";
  parameter  ModelAlias = ".";
  parameter  ModelConfig = "32'h0";
  parameter  ModelId = "-2";
  parameter  TimingVersion = "133";

  // Invoke the model 
  initial
    begin
      $lm_model(
        "cy7c04314bv_mx_lmtv",
        ModelType,
        "attr", "defaultdata", DefaultData,
        "attr", "delayrange", DelayRange,
        "attr", "memoryfile", MemoryFile,
        "attr", "messagelevel", MessageLevel,
        "attr", "modelalias", ModelAlias,
        "attr", "modelconfig", ModelConfig,
        "attr", "modelid", ModelId,
        "attr", "timingversion", TimingVersion,
        "in", clkp1,
        "in", clkp2,
        "in", clkp3,
        "in", clkp4,
        "in", oep1_n,
        "in", oep2_n,
        "in", oep3_n,
        "in", oep4_n,
        "in", r_w_np1,
        "in", r_w_np2,
        "in", r_w_np3,
        "in", r_w_np4,
        "in", ce0p1_n,
        "in", ce0p2_n,
        "in", ce0p3_n,
        "in", ce0p4_n,
        "in", ce1p1,
        "in", ce1p2,
        "in", ce1p3,
        "in", ce1p4,
        "out", intp1_n, intp1_n__STRONG, intp1_n__PULL,
        "out", intp2_n, intp2_n__STRONG, intp2_n__PULL,
        "out", intp3_n, intp3_n__STRONG, intp3_n__PULL,
        "out", intp4_n, intp4_n__STRONG, intp4_n__PULL,
        "in", mrst_n,
        "io", iop1_0, iop1_0__STRONG, iop1_0__PULL,
        "io", iop1_1, iop1_1__STRONG, iop1_1__PULL,
        "io", iop1_2, iop1_2__STRONG, iop1_2__PULL,
        "io", iop1_3, iop1_3__STRONG, iop1_3__PULL,
        "io", iop1_4, iop1_4__STRONG, iop1_4__PULL,
        "io", iop1_5, iop1_5__STRONG, iop1_5__PULL,
        "io", iop1_6, iop1_6__STRONG, iop1_6__PULL,
        "io", iop1_7, iop1_7__STRONG, iop1_7__PULL,
        "io", iop1_8, iop1_8__STRONG, iop1_8__PULL,
        "io", iop1_9, iop1_9__STRONG, iop1_9__PULL,
        "io", iop1_10, iop1_10__STRONG, iop1_10__PULL,
        "io", iop1_11, iop1_11__STRONG, iop1_11__PULL,
        "io", iop1_12, iop1_12__STRONG, iop1_12__PULL,
        "io", iop1_13, iop1_13__STRONG, iop1_13__PULL,
        "io", iop1_14, iop1_14__STRONG, iop1_14__PULL,
        "io", iop1_15, iop1_15__STRONG, iop1_15__PULL,
        "io", iop1_16, iop1_16__STRONG, iop1_16__PULL,
        "io", iop1_17, iop1_17__STRONG, iop1_17__PULL,
        "io", iop2_0, iop2_0__STRONG, iop2_0__PULL,
        "io", iop2_1, iop2_1__STRONG, iop2_1__PULL,
        "io", iop2_2, iop2_2__STRONG, iop2_2__PULL,
        "io", iop2_3, iop2_3__STRONG, iop2_3__PULL,
        "io", iop2_4, iop2_4__STRONG, iop2_4__PULL,
        "io", iop2_5, iop2_5__STRONG, iop2_5__PULL,
        "io", iop2_6, iop2_6__STRONG, iop2_6__PULL,
        "io", iop2_7, iop2_7__STRONG, iop2_7__PULL,
        "io", iop2_8, iop2_8__STRONG, iop2_8__PULL,
        "io", iop2_9, iop2_9__STRONG, iop2_9__PULL,
        "io", iop2_10, iop2_10__STRONG, iop2_10__PULL,
        "io", iop2_11, iop2_11__STRONG, iop2_11__PULL,
        "io", iop2_12, iop2_12__STRONG, iop2_12__PULL,
        "io", iop2_13, iop2_13__STRONG, iop2_13__PULL,
        "io", iop2_14, iop2_14__STRONG, iop2_14__PULL,
        "io", iop2_15, iop2_15__STRONG, iop2_15__PULL,
        "io", iop2_16, iop2_16__STRONG, iop2_16__PULL,
        "io", iop2_17, iop2_17__STRONG, iop2_17__PULL,
        "io", iop3_0, iop3_0__STRONG, iop3_0__PULL,
        "io", iop3_1, iop3_1__STRONG, iop3_1__PULL,
        "io", iop3_2, iop3_2__STRONG, iop3_2__PULL,
        "io", iop3_3, iop3_3__STRONG, iop3_3__PULL,
        "io", iop3_4, iop3_4__STRONG, iop3_4__PULL,
        "io", iop3_5, iop3_5__STRONG, iop3_5__PULL,
        "io", iop3_6, iop3_6__STRONG, iop3_6__PULL,
        "io", iop3_7, iop3_7__STRONG, iop3_7__PULL,
        "io", iop3_8, iop3_8__STRONG, iop3_8__PULL,
        "io", iop3_9, iop3_9__STRONG, iop3_9__PULL,
        "io", iop3_10, iop3_10__STRONG, iop3_10__PULL,
        "io", iop3_11, iop3_11__STRONG, iop3_11__PULL,
        "io", iop3_12, iop3_12__STRONG, iop3_12__PULL,
        "io", iop3_13, iop3_13__STRONG, iop3_13__PULL,
        "io", iop3_14, iop3_14__STRONG, iop3_14__PULL,
        "io", iop3_15, iop3_15__STRONG, iop3_15__PULL,
        "io", iop3_16, iop3_16__STRONG, iop3_16__PULL,
        "io", iop3_17, iop3_17__STRONG, iop3_17__PULL,
        "io", iop4_0, iop4_0__STRONG, iop4_0__PULL,
        "io", iop4_1, iop4_1__STRONG, iop4_1__PULL,
        "io", iop4_2, iop4_2__STRONG, iop4_2__PULL,
        "io", iop4_3, iop4_3__STRONG, iop4_3__PULL,
        "io", iop4_4, iop4_4__STRONG, iop4_4__PULL,
        "io", iop4_5, iop4_5__STRONG, iop4_5__PULL,
        "io", iop4_6, iop4_6__STRONG, iop4_6__PULL,
        "io", iop4_7, iop4_7__STRONG, iop4_7__PULL,
        "io", iop4_8, iop4_8__STRONG, iop4_8__PULL,
        "io", iop4_9, iop4_9__STRONG, iop4_9__PULL,
        "io", iop4_10, iop4_10__STRONG, iop4_10__PULL,
        "io", iop4_11, iop4_11__STRONG, iop4_11__PULL,
        "io", iop4_12, iop4_12__STRONG, iop4_12__PULL,
        "io", iop4_13, iop4_13__STRONG, iop4_13__PULL,
        "io", iop4_14, iop4_14__STRONG, iop4_14__PULL,
        "io", iop4_15, iop4_15__STRONG, iop4_15__PULL,
        "io", iop4_16, iop4_16__STRONG, iop4_16__PULL,
        "io", iop4_17, iop4_17__STRONG, iop4_17__PULL,
        "in", bep1_n_0,
        "in", bep1_n_1,
        "in", bep2_n_0,
        "in", bep2_n_1,
        "in", bep3_n_0,
        "in", bep3_n_1,
        "in", bep4_n_0,
        "in", bep4_n_1,
        "in", ap1_0,
        "in", ap1_1,
        "in", ap1_2,
        "in", ap1_3,
        "in", ap1_4,
        "in", ap1_5,
        "in", ap1_6,
        "in", ap1_7,
        "in", ap1_8,
        "in", ap1_9,
        "in", ap1_10,
        "in", ap1_11,
        "in", ap1_12,
        "in", ap1_13,
        "in", ap2_0,
        "in", ap2_1,
        "in", ap2_2,
        "in", ap2_3,
        "in", ap2_4,
        "in", ap2_5,
        "in", ap2_6,
        "in", ap2_7,
        "in", ap2_8,
        "in", ap2_9,
        "in", ap2_10,
        "in", ap2_11,
        "in", ap2_12,
        "in", ap2_13,
        "in", ap3_0,
        "in", ap3_1,
        "in", ap3_2,
        "in", ap3_3,
        "in", ap3_4,
        "in", ap3_5,
        "in", ap3_6,
        "in", ap3_7,
        "in", ap3_8,
        "in", ap3_9,
        "in", ap3_10,
        "in", ap3_11,
        "in", ap3_12,
        "in", ap3_13,
        "in", ap4_0,
        "in", ap4_1,
        "in", ap4_2,
        "in", ap4_3,
        "in", ap4_4,
        "in", ap4_5,
        "in", ap4_6,
        "in", ap4_7,
        "in", ap4_8,
        "in", ap4_9,
        "in", ap4_10,
        "in", ap4_11,
        "in", ap4_12,
        "in", ap4_13 );
    end

endmodule
