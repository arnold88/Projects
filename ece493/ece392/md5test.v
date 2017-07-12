// Arnold Lee	
// MD5 Test Bench


module md5testbench;

reg clock;
reg reset;
reg load;
wire ready;
reg text;

reg [127:0] datain;
wire [127:0] dataout;

md5 m1(clock,reset,load,ready,text,datain,dataout);

   initial

   begin
     clock = 'b1;
     reset = 'b1;  
     load = 'b0;
     text= 'b0;
     datain=128'h44528061262d718c33bdf2ac44206635;
     @(posedge clock);
     reset = #1 'b0;
     @(posedge clock);
     reset = #1 'b1;
     @(posedge clock);
     load = #1 'b1;
     @(posedge clock);
     load = #1 'b0;
     datain= 128'h0;
     @(posedge clock);
     load = #1 'b1;
     @(posedge clock);
     @(posedge clock);
     load = #1 'b0;
     datain= 128'h800000000;
     @(posedge clock);
     load =#1 'b1;
     @(posedge clock);
     load = #1 'b0;
	
	
     $display("Test Start:");
     wait(ready);	
     $display("Hash for \"a\":");
     $display("%H",dataout);
		
     @(posedge clock);
     text=#1'b1;	
     @(posedge clock);
     text=#1'b0;		
		
     @(posedge clock);
     datain=128'h45453333efef00943232112344058861;
     @(posedge clock);
     load = #1 'b1;
     @(posedge clock);
     @(posedge clock);
     @(posedge clock);
     @(posedge clock);
     load = #1 'b0;
     wait(ready);	
		
     @(posedge clock);
     datain=128'h81718171817181718171817181718171;
     @(posedge clock);
     load = #1 'b1;
     @(posedge clock);
     @(posedge clock);
     load = #1 'b0;
     datain=128'h80000000000000000000000000;
     @(posedge clock);
     load = #1 'b1;
     @(posedge clock);
     load = #1 'b0;
     datain=128'h30000000000;
     @(posedge clock);
     load = #1 'b1;
     @(posedge clock);
     load = #1 'b0;
     wait(ready);	
     $display("Hash source for: \"a\":");
     $display("%H",dataout);
	
	
     $finish;

   end
   
   always #5 clock = !clock;  // flip the clock constantly

endmodule
