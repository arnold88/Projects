// Arnold Lee
// SHA1 Test bench version 1.1
// Internal use only


`timescale 1ns/10ps

`define SHA1_TEST_PADDING	{1'b1,63'b0,448'b0,64'd448}
`define SHA1_TEST		"xbcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
`define SHA1_TEST_RESULT	160'h84983e44_1c3bd26e_baae4aa1_f95129e5_e54670f1

module test_sha;

reg clk,rst,cmd_w_i;
reg [31:0] text_i;

reg [2:0] cmd_i;

wire [31:0] text_o;
wire [3:0] cmd_o;

initial
begin

	clk = 1'b0;
	rst = 1'b0;
	cmd_w_i = 1'b0;
	cmd_i = 3'b0;
	
	#21;
	rst = 1'b1;
	#17;
	rst = 1'b0;
	
	test_SHA1;
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	
	$finish;
end


always #5 clk = ~clk;

sha1v12 sha_core(
	.clk_i(clk),
	.reset(rst),
	.command_input(cmd_i),
	.write(cmd_w_i),
	.text_in(text_i),
	.text_out(text_o),
	.status(cmd_o)
	);

task test_SHA1;
integer i;
reg [1023:0] all_message;
reg [511:0] tmp_i;
reg [159:0] tmp_o;
reg [31:0] tmp;
begin
	all_message = {`SHA1_TEST,`SHA1_TEST_PADDING};
	tmp_i = all_message[1023:512];
	tmp_o = `SHA1_TEST_RESULT;
	
	#100;
	
	
	@(posedge clk);
	cmd_i = 3'b010;
	cmd_w_i = 1'b1;
	
	for (i=0;i<16;i=i+1)
	begin
		@(posedge clk);
		cmd_w_i = 1'b0;
		text_i = tmp_i[16*32-1:15*32];
		tmp_i = tmp_i << 32;
	end

	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);

	while (cmd_o[3])
		@(posedge clk);
	
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	
	#100;
	
	
	tmp_i = all_message[511:0];
	@(posedge clk);
	cmd_i = 3'b110;
	cmd_w_i = 1'b1;
	
	for (i=0;i<16;i=i+1)
	begin
		@(posedge clk);
		cmd_w_i = 1'b0;
		text_i = tmp_i[16*32-1:15*32];
		tmp_i = tmp_i << 32;
	end

	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);

	while (cmd_o[3])
		@(posedge clk);
	
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);

	cmd_i = 6'b001;
	cmd_w_i = 1'b1;
	
	@(posedge clk);
	cmd_w_i = 1'b0;
	for (i=0;i<5;i=i+1)
	begin
		@(posedge clk);
		#1;
		tmp = tmp_o[5*32-1:4*32];
		if (text_o !== tmp | (|text_o)===1'bx)
		begin
			$display("ERROR(SHA-160-%02d) Expected %x, Got %x", i,tmp, text_o);
		end
		else
		begin
			$display("OK(SHA-160-%02d),Expected %x, Got %x", i,tmp, text_o);
		end
		tmp_o = tmp_o << 32;
	end	
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	#100;
end
endtask


endmodule