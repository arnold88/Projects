// Generated by vsg 01042

module k6r1004v1d_mx_bw(
  io,
  we_n,
  cs_n,
  oe_n,
  a );

  // Allowed timing versions: 
  //  Device Name             TimingVersion
  //  ===========             =============

  // Parameter declarations 
  parameter  ModelType = "SWIFT";
  parameter  DefaultData = "1111";
  parameter  DelayRange = "Max";
  parameter  MemoryFile = ".";
  parameter  MessageLevel = "15";
  parameter  ModelAlias = ".";
  parameter  ModelConfig = "32'h0";
  parameter  ModelId = "-2";
  parameter  TimingVersion = "8";


  inout  [4:1] io;
  input  we_n;
  input  cs_n;
  input  oe_n;
  input  [17:0] a;

k6r1004v1d_mx  I1 ( 
  .io__SWIFT_BUS__1(io[1]),
  .io__SWIFT_BUS__2(io[2]),
  .io__SWIFT_BUS__3(io[3]),
  .io__SWIFT_BUS__4(io[4]),
  .we_n(we_n),
  .cs_n(cs_n),
  .oe_n(oe_n),
  .a__SWIFT_BUS__0(a[0]),
  .a__SWIFT_BUS__1(a[1]),
  .a__SWIFT_BUS__2(a[2]),
  .a__SWIFT_BUS__3(a[3]),
  .a__SWIFT_BUS__4(a[4]),
  .a__SWIFT_BUS__5(a[5]),
  .a__SWIFT_BUS__6(a[6]),
  .a__SWIFT_BUS__7(a[7]),
  .a__SWIFT_BUS__8(a[8]),
  .a__SWIFT_BUS__9(a[9]),
  .a__SWIFT_BUS__10(a[10]),
  .a__SWIFT_BUS__11(a[11]),
  .a__SWIFT_BUS__12(a[12]),
  .a__SWIFT_BUS__13(a[13]),
  .a__SWIFT_BUS__14(a[14]),
  .a__SWIFT_BUS__15(a[15]),
  .a__SWIFT_BUS__16(a[16]),
  .a__SWIFT_BUS__17(a[17]));
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
