// Generated by vsg 01042

module cy7c0831v_mx_bw(
  clkl,
  clkr,
  oel_n,
  oer_n,
  r_w_nl,
  r_w_nr,
  ce0l_n,
  ce0r_n,
  ce1l,
  ce1r,
  adsl_n,
  adsr_n,
  cntenl_n,
  cntenr_n,
  cntrstl_n,
  cntrstr_n,
  cnt_msk_nl,
  cnt_msk_nr,
  intl_n,
  intr_n,
  cntintl_n,
  cntintr_n,
  mrst_n,
  bl_n,
  br_n,
  dql,
  dqr,
  al,
  ar );

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
  parameter  TimingVersion = "150";


  input  clkl;
  input  clkr;
  input  oel_n;
  input  oer_n;
  input  r_w_nl;
  input  r_w_nr;
  input  ce0l_n;
  input  ce0r_n;
  input  ce1l;
  input  ce1r;
  input  adsl_n;
  input  adsr_n;
  input  cntenl_n;
  input  cntenr_n;
  input  cntrstl_n;
  input  cntrstr_n;
  input  cnt_msk_nl;
  input  cnt_msk_nr;
  output intl_n;
  output intr_n;
  output cntintl_n;
  output cntintr_n;
  input  mrst_n;
  input  [1:0] bl_n;
  input  [1:0] br_n;
  inout  [17:0] dql;
  inout  [17:0] dqr;
  inout  [16:0] al;
  inout  [16:0] ar;

cy7c0831v_mx  I1 ( 
  .clkl(clkl),
  .clkr(clkr),
  .oel_n(oel_n),
  .oer_n(oer_n),
  .r_w_nl(r_w_nl),
  .r_w_nr(r_w_nr),
  .ce0l_n(ce0l_n),
  .ce0r_n(ce0r_n),
  .ce1l(ce1l),
  .ce1r(ce1r),
  .adsl_n(adsl_n),
  .adsr_n(adsr_n),
  .cntenl_n(cntenl_n),
  .cntenr_n(cntenr_n),
  .cntrstl_n(cntrstl_n),
  .cntrstr_n(cntrstr_n),
  .cnt_msk_nl(cnt_msk_nl),
  .cnt_msk_nr(cnt_msk_nr),
  .intl_n(intl_n),
  .intr_n(intr_n),
  .cntintl_n(cntintl_n),
  .cntintr_n(cntintr_n),
  .mrst_n(mrst_n),
  .bl_n_0(bl_n[0]),
  .bl_n_1(bl_n[1]),
  .br_n_0(br_n[0]),
  .br_n_1(br_n[1]),
  .dql_0(dql[0]),
  .dql_1(dql[1]),
  .dql_2(dql[2]),
  .dql_3(dql[3]),
  .dql_4(dql[4]),
  .dql_5(dql[5]),
  .dql_6(dql[6]),
  .dql_7(dql[7]),
  .dql_8(dql[8]),
  .dql_9(dql[9]),
  .dql_10(dql[10]),
  .dql_11(dql[11]),
  .dql_12(dql[12]),
  .dql_13(dql[13]),
  .dql_14(dql[14]),
  .dql_15(dql[15]),
  .dql_16(dql[16]),
  .dql_17(dql[17]),
  .dqr_0(dqr[0]),
  .dqr_1(dqr[1]),
  .dqr_2(dqr[2]),
  .dqr_3(dqr[3]),
  .dqr_4(dqr[4]),
  .dqr_5(dqr[5]),
  .dqr_6(dqr[6]),
  .dqr_7(dqr[7]),
  .dqr_8(dqr[8]),
  .dqr_9(dqr[9]),
  .dqr_10(dqr[10]),
  .dqr_11(dqr[11]),
  .dqr_12(dqr[12]),
  .dqr_13(dqr[13]),
  .dqr_14(dqr[14]),
  .dqr_15(dqr[15]),
  .dqr_16(dqr[16]),
  .dqr_17(dqr[17]),
  .al_0(al[0]),
  .al_1(al[1]),
  .al_2(al[2]),
  .al_3(al[3]),
  .al_4(al[4]),
  .al_5(al[5]),
  .al_6(al[6]),
  .al_7(al[7]),
  .al_8(al[8]),
  .al_9(al[9]),
  .al_10(al[10]),
  .al_11(al[11]),
  .al_12(al[12]),
  .al_13(al[13]),
  .al_14(al[14]),
  .al_15(al[15]),
  .al_16(al[16]),
  .ar_0(ar[0]),
  .ar_1(ar[1]),
  .ar_2(ar[2]),
  .ar_3(ar[3]),
  .ar_4(ar[4]),
  .ar_5(ar[5]),
  .ar_6(ar[6]),
  .ar_7(ar[7]),
  .ar_8(ar[8]),
  .ar_9(ar[9]),
  .ar_10(ar[10]),
  .ar_11(ar[11]),
  .ar_12(ar[12]),
  .ar_13(ar[13]),
  .ar_14(ar[14]),
  .ar_15(ar[15]),
  .ar_16(ar[16]));
  defparam
    I1.DefaultData = DefaultData,
    I1.DelayRange = DelayRange,
    I1.MemoryFile = MemoryFile,
    I1.MessageLevel = MessageLevel,
    I1.ModelAlias = ModelAlias,
    I1.ModelConfig = ModelConfig,
    I1.ModelId = ModelId,
    I1.TimingVersion = TimingVersion;

endmodule
