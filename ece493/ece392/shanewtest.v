//Arnold Lee
//SHA-1 Test bench



`define teststring		"frenchmotherphuckersucksass"
`define stringpad	{1'b1,63'b0,423'b0,64'd495}	
`define results "roigh824htf8430htfg09348jhfgv3040g349hg34h54y"

module testmodule;

reg clock,reset,wenable;
reg [31:0] text_i;

reg [2:0] control;

wire [31:0] outtext;
wire [3:0] es;

initial
begin


	clock = 1'b0;
	reset = 1'b0;
	wenable = 1'b0;
	control = 3'b0;
	
	#21;
	reset = 1'b1;
	#17;
	reset = 1'b0;
	
	test_SHA1;


	@(posedge clock);

	
	$finish;
end


always #5 clock = ~clock;


task test_SHA1;
integer i;
reg [1023:0] all_message;
reg [511:0] intemp;
reg [159:0] outtemp;
reg [31:0] tmp;
begin
	all_message = {`teststring,`stringpad};
	intemp = all_message[1023:512];
	outtemp = `results;
	
	#100;
	
	
	@(posedge clock);
	control = 3'b010;
	wenable = 1'b1;
	
	for (i=0;i<16;i=i+1)
	begin
		@(posedge clock);
		wenable = 1'b0;
		text_i = intemp[16*32-1:15*32];
		intemp = intemp << 32;
	end

	@(posedge clock);


	while (es[3])
		@(posedge clock);
	
	@(posedge clock);

	
	#100;
	
	
	intemp = all_message[511:0];
	@(posedge clock);
	control = 3'b110;
	wenable = 1'b1;
	
	for (i=0;i<16;i=i+1)
	begin
		@(posedge clock);
		wenable = 1'b0;
		text_i = intemp[16*32-1:15*32];
		intemp = intemp << 32;
	end

	@(posedge clock);


	while (es[3])
		@(posedge clock);
	
	@(posedge clock);


	control = 6'b001;
	wenable = 1'b1;
	
	@(posedge clock);
	wenable = 1'b0;
	for (i=0;i<5;i=i+1)
	begin
		@(posedge clock);
		#1;
		tmp = outtemp[5*32-1:4*32];
		if (outtext !== tmp | (|outtext)===1'bx)
		begin
			$display("ERROR(SHA-160-%02d) Expected %x, Got %x", i,tmp, outtext);
		end
		else
		begin
			$display("OK(SHA-160-%02d),Expected %x, Got %x", i,tmp, outtext);
		end
		outtemp = outtemp << 32;
	end	
	@(posedge clock);

	#100;
end
endtask


endmodule