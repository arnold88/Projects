// Generated by vsg 01042

module cy7c006a_mx_bw(
  al,
  ar,
  cel_n,
  cer_n,
  iol,
  ior,
  oel_n,
  oer_n,
  r_w_nl,
  r_w_nr,
  seml_n,
  semr_n,
  intl_n,
  intr_n,
  busyl_n,
  busyr_n,
  m_s_n );

  // Allowed timing versions: 
  //  Device Name             TimingVersion
  //  ===========             =============

  // Parameter declarations 
  parameter  ModelType = "SWIFT";
  parameter  DefaultData = "11111111";
  parameter  DelayRange = "Max";
  parameter  MemoryFile = ".";
  parameter  MessageLevel = "15";
  parameter  ModelAlias = ".";
  parameter  ModelConfig = "32'h0";
  parameter  ModelId = "-2";
  parameter  TimingVersion = "12";


  input  [13:0] al;
  input  [13:0] ar;
  input  cel_n;
  input  cer_n;
  inout  [7:0] iol;
  inout  [7:0] ior;
  input  oel_n;
  input  oer_n;
  input  r_w_nl;
  input  r_w_nr;
  input  seml_n;
  input  semr_n;
  output intl_n;
  output intr_n;
  inout  busyl_n;
  inout  busyr_n;
  input  m_s_n;

cy7c006a_mx  I1 ( 
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
  .cel_n(cel_n),
  .cer_n(cer_n),
  .iol_0(iol[0]),
  .iol_1(iol[1]),
  .iol_2(iol[2]),
  .iol_3(iol[3]),
  .iol_4(iol[4]),
  .iol_5(iol[5]),
  .iol_6(iol[6]),
  .iol_7(iol[7]),
  .ior_0(ior[0]),
  .ior_1(ior[1]),
  .ior_2(ior[2]),
  .ior_3(ior[3]),
  .ior_4(ior[4]),
  .ior_5(ior[5]),
  .ior_6(ior[6]),
  .ior_7(ior[7]),
  .oel_n(oel_n),
  .oer_n(oer_n),
  .r_w_nl(r_w_nl),
  .r_w_nr(r_w_nr),
  .seml_n(seml_n),
  .semr_n(semr_n),
  .intl_n(intl_n),
  .intr_n(intr_n),
  .busyl_n(busyl_n),
  .busyr_n(busyr_n),
  .m_s_n(m_s_n));
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
