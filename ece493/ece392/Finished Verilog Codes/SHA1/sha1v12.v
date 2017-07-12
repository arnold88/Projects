// Arnold Lee
// SHA-1 Verilog -- Version 1.2 with Multi-cycle path optimization
// Created: 08/07/2006

// This module implements the SHA-1 algorithm. It accepts 4 inputs:
// 1 clk_i input, 1 reset input, 1 32-bit text input, and 2-bit control input.
// The output 
// The module is designed in a way so that it is sequential, i.e. follow the order 
// of the algorithm given in FIPS 180-1 document.

// The FIPS 180-1 docuemnt can be found at:
// http://www.itl.nist.gov/fipspubs/fip180-1.htm



// We should be coming out with an 160-bit message digest or an error status (for debug purposes).


// first,Constant and function declaration
// using the same name as the doucment, namely H0 to H4 , K0 to K4 (constant word)



//THE FOLLOWING PRE-DEFINED VARIABLES ARE FOR DATA
//PADDING AND PROCESSING

`define SHA1_H0 32'h67452301
`define SHA1_H1 32'hefcdab89
`define SHA1_H2 32'h98badcfe
`define SHA1_H3 32'h10325476
`define SHA1_H4 32'hc3d2e1f0

`define SHA1_K0 32'h5a827999
`define SHA1_K1 32'h6ed9eba1
`define SHA1_K2 32'h8f1bbcdc
`define SHA1_K3 32'hca62c1d6

module sha1v12 (clk_i, reset, command_input, write, text_in, text_out, status);

	input		clk_i; 	// clk_i
	input		reset; 	// ACTIVE HIGH RESET
	input	[31:0]	text_in;	//32-BIT TEXT INPUT
	output	[31:0]	text_out;	// 32-BIT TEXT OUTPUT
	input	[2:0]	command_input;	// command_input INPUT
	input		write;// command_input INPUT WRITE ENABLE
	output	[3:0]	status;	// STATUS

    	reg	[3:0]	cmd;
    	wire	[3:0]	status;
    	reg	[31:0]	text_out;
     reg	[6:0]	round;
    	wire	[6:0]	round_plus_1;
    	reg	[2:0]	read_counter;
    	reg	[31:0]	H0,H1,H2,H3,H4;
    	reg	[31:0]	W0,W1,W2,W3,W4,W5,W6,W7,W8,W9,W10,W11,W12,W13,W14;
    	reg	[31:0]	Wt,Kt;
    	reg	[31:0]	A,B,C,D,E;
     reg		busy;
    	assign status = cmd;
    	    	
	wire [31:0] SHA1_f1_BCD,SHA1_f2_BCD,SHA1_f3_BCD,SHA1_Wt_1;
	wire [31:0] SHA1_ft_BCD;
	wire [31:0] next_Wt,next_A,next_C;
	wire [159:0] SHA1_result;
	
	assign SHA1_f1_BCD = (B & C) ^ (~B & D);
	assign SHA1_f2_BCD = B ^ C ^ D;
	assign SHA1_f3_BCD = (B & C) ^ (C & D) ^ (B & D);
	
	assign SHA1_ft_BCD = (round < 'd21) ? SHA1_f1_BCD : (round < 'd41) ? SHA1_f2_BCD : (round < 'd61) ? SHA1_f3_BCD : SHA1_f2_BCD;
	
    	assign SHA1_Wt_1 = {W13 ^ W8 ^ W2 ^ W0};

	assign next_Wt = {SHA1_Wt_1[30:0],SHA1_Wt_1[31]};	
	assign next_A = {A[26:0],A[31:27]} + SHA1_ft_BCD + E + Kt + Wt;
	assign next_C = {B[1:0],B[31:2]};
	
	assign SHA1_result   = {A,B,C,D,E};
	
	assign round_plus_1 = round + 1;
	
	// POSITIVE EDGE TRIGGERED SEQUENCE
	always @(posedge clk_i)  // START clk_i
	begin
	    //*** BUSY-BIT INTIALIZATION
	    // This busy bit is used to avoid accidential
	    // overwriting of data.
	   if (reset)
    			cmd <= 'b0;
    		else
    		if (write)
    			cmd[2:0] <= command_input[2:0];		// BUSY-BIT WRITE PROTECTION
    		else
    		begin
    			cmd[3] <= busy;			// BUSY-BIT CEAR
    			if (~busy)
    				cmd[1:0] <= 2'b00;	
    		end
	 end
	 
	 always @ (posedge clk_i)
	 begin   
	   //******** SHA ROUND STARTS 
		if (reset)
		begin
			round <= 'd0;
			busy <= 'b0;

			W0  <= 'b0;
			W1  <= 'b0;
			W2  <= 'b0;
			W3  <= 'b0;
			W4  <= 'b0;
			W5  <= 'b0;
			W6  <= 'b0;
			W7  <= 'b0;
			W8  <= 'b0;
			W9  <= 'b0;
			W10 <= 'b0;
			W11 <= 'b0;
			W12 <= 'b0;
			W13 <= 'b0;
			W14 <= 'b0;
			Wt  <= 'b0;
			
			A <= 'b0;
			B <= 'b0;
			C <= 'b0;
			D <= 'b0;
			E <= 'b0;
			
			H0 <= 'b0;
			H1 <= 'b0;
			H2 <= 'b0;
			H3 <= 'b0;
			H4 <= 'b0;

		end
		else
		begin
			case (round)
			'd0:
				begin
					if (cmd[1])
					begin
						W0 <= text_in;
						Wt <= text_in;
						busy <= 'b1;
						round <= round_plus_1;
                                               	
						case (cmd[2])
							1'b0:	// FIRST INPUT MESSAGE
								begin
									A <= `SHA1_H0;
									B <= `SHA1_H1;
									C <= `SHA1_H2;
									D <= `SHA1_H3;
									E <= `SHA1_H4;
									
									H0 <= `SHA1_H0;
									H1 <= `SHA1_H1;
									H2 <= `SHA1_H2;
									H3 <= `SHA1_H3;
									H4 <= `SHA1_H4;
								end
							1'b1:	// INTERNAL MESSAGE
								begin
									H0 <= A;
									H1 <= B;
									H2 <= C;
									H3 <= D;
									H4 <= E;
								end
						endcase
					end
					else
					begin	// IDLE
						round <= 'd0;
					end
				end
			'd1:
				begin
					W1 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd2:
				begin
					W2 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd3:
				begin
					W3 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd4:
				begin
					W4 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd5:
				begin
					W5 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd6:
				begin
					W6 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd7:
				begin
					W7 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd8:
				begin
					W8 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd9:
				begin
					W9 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd10:
				begin
					W10 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd11:
				begin
					W11 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd12:
				begin
					W12 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd13:
				begin
					W13 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd14:
				begin
					W14 <= text_in;
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd15:
				begin
					Wt <= text_in;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd16,
			'd17,
			'd18,
			'd19,
			'd20,
			'd21,
			'd22,
			'd23,
			'd24,
			'd25,
			'd26,
			'd27,
			'd28,
			'd29,
			'd30,
			'd31,
			'd32,
			'd33,
			'd34,
			'd35,
			'd36,
			'd37,
			'd38,
			'd39,
			'd40,
			'd41,
			'd42,
			'd43,
			'd44,
			'd45,
			'd46,
			'd47,
			'd48,
			'd49,
			'd50,
			'd51,
			'd52,
			'd53,
			'd54,
			'd55,
			'd56,
			'd57,
			'd58,
			'd59,
			'd60,
			'd61,
			'd62,
			'd63,
			'd64,
			'd65,
			'd66,
			'd67,
			'd68,
			'd69,
			'd70,
			'd71,
			'd72,
			'd73,
			'd74,
			'd75,
			'd76,
			'd77,
			'd78,
			'd79:
				begin
					W0  <= W1;
					W1  <= W2;
					W2  <= W3;
					W3  <= W4;
					W4  <= W5;
					W5  <= W6;
					W6  <= W7;
					W7  <= W8;
					W8  <= W9;
					W9  <= W10;
					W10 <= W11;
					W11 <= W12;
					W12 <= W13;
					W13 <= W14;
					W14 <= Wt;
					Wt  <= next_Wt;
					
					E <= D;
					D <= C;
					C <= next_C;
					B <= A;
					A <= next_A;
						
					round <= round_plus_1;
				end
			'd80:
				begin
					A <= next_A + H0;
					B <= A + H1;
					C <= next_C + H2;
					D <= C + H3;
					E <= D + H4;
					round <= 'd0;
					busy <= 'b0;
				end
			default:
				begin
					round <= 'd0;
					busy <= 'b0;
				end
			endcase
		end	
	end
		
//******  WRITE TO K's REGISTER
   always @(posedge clk_i)
   begin
		if (reset)
		begin
			Kt <= 'b0;
		end
		else
		begin
			if (round < 'd20)
				Kt <= `SHA1_K0;
			else
			if (round < 'd40)
				Kt <= `SHA1_K1;
			else
			if (round < 'd60)
				Kt <= `SHA1_K2;
			else
				Kt <= `SHA1_K3;
		end
	end
//***** WRITE TO TEXT OUTPUT (DIGEST)
   always @ (posedge clk_i)
   begin
		if (reset)
		begin
			text_out <= 'b0;
			read_counter <= 'b0;
		end
		else
		begin
			if (cmd[0])
			begin
				read_counter <= 'd4;	// INCREMENT READ COUNTER
			end
			else
			begin
			if (~busy)
			begin
				case (read_counter)
					'd4:	text_out <= SHA1_result[5*32-1:4*32];
					'd3:	text_out <= SHA1_result[4*32-1:3*32];
					'd2:	text_out <= SHA1_result[3*32-1:2*32];
					'd1:	text_out <= SHA1_result[2*32-1:1*32];
					'd0:	text_out <= SHA1_result[1*32-1:0*32];
					default:text_out <= 'b0;
				endcase
				if (|read_counter)
					read_counter <= read_counter - 'd1;
			end
			else
			begin
				text_out <= 'b0;
			end
			end
		end
end // END clk_i 
	
endmodule
 
