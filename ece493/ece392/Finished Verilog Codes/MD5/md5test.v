// Arnold Lee
// MD5 Verilog test bench
// 09/02/2006


`timescale 10ns/1ns

module md5testbench;


reg clk;
reg reset;
reg load_i;
wire ready_o;
reg newtext_i;

reg [127:0] data_i;
wire [127:0] data_o;

md5 m1(clk,reset,load_i,ready_o,newtext_i,data_i,data_o);

   initial

   begin
     clk = 'b1;
     reset = 'b1;  
     load_i = 'b0;
     newtext_i= 'b0;
     data_i=128'h00008061000000000000000000000000;
     @(posedge clk);
     reset = #1 'b0;
     @(posedge clk);
     reset = #1 'b1;
     @(posedge clk);
     load_i = #1 'b1;
     @(posedge clk);
     load_i = #1 'b0;
     data_i= 128'h0;
     @(posedge clk);
     load_i = #1 'b1;
     @(posedge clk);
     @(posedge clk);
     load_i = #1 'b0;
     data_i= 128'h800000000;
     @(posedge clk);
     load_i =#1 'b1;
     @(posedge clk);
     load_i = #1 'b0;
	
	
     wait(ready_o);	
     $display("Hash for \"a\":");
     $display("%H",data_o);
		
     
	
	
     $finish;

   end
   
   always #5 clk = !clk;

endmodule