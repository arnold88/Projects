// Arnold Lee
// SHA-1 Verilog algo

// This module implements the SHA-1 algorithm. It accepts 4 inputs:
// 1 clock input, 1 reset input, 1 32-bit text input, and 2-bit control input.
// The output 
// The module is designed in a way so that it is sequential, i.e. follow the order 
// of the algorithm given in FIPS 180-1 document.

// The FIPS 180-1 docuemnt can be found at:
// http://www.itl.nist.gov/fipspubs/fip180-1.htm



// We should be coming out with an 160-bit message digest or an error status (for debug purposes).


// first,Constant and function declaration
// using the same name as the doucment, namely H0 to H4 , K0 to K4 (constant word)


`define h0 32'h67452301
`define h1 32'hefcdab89
`define h2 32'h98badcfe
`define h3 32'h10325476
`define h4 32'hc3d2e1f0

`define k0 32'h5a827999
`define k1 32'h6ed9eba1
`define k2 32'h8f1bbcdc
`define k3 32'hca62c1d6

module sha1 (clock, reset, source, product, control, wenable, es);

	input		clock; 	
	input		reset;
	input	[2:0]	control;	// control signal
	input		wenable;// control block write enable
	input	[31:0]	source;	
	output	[31:0]	product;	
	output	[3:0]	es;	// error status
   reg	[3:0]	csreg; // control signal register
    	wire	[3:0]	es;
    	assign es = csreg;
    	reg	[31:0]	product;
    	reg	[6:0]	counter;
    	wire	[6:0]	counter1;
    	reg	[2:0]	read_counter;
    	reg busy_bit;
    	
    	// Initialize intermediate constants and varaibles, as specified
    	
    	reg	[31:0]	A,B,C,D,E;
    	reg	[31:0]	Wt,Kt;
    	reg	[31:0]	H0,H1,H2,H3,H4;
    	reg	[31:0]	W0,W1,W2,W3,W4,W5,W6,W7,W8,W9,W10,W11,W12,W13,W14;
    	
    	 	// Hash functions intermediate results intialization
    	
	wire [31:0] f_zero,f_twenty_or_sixty,f_forty,wt,ft;
	
	// ft = selection into which "f" (function) to use according to the value of t
	// f_zero = chosen if 0 <= t <= 19
	// f_twenty_or_sixty = chosen if 20<=t<=39 , 60<=t<=79
	// f_forty = chosen if 40 < = t <= 59
	// all those "f"s are defined below
	
	// placeholder for the next processing 32-bit words
	wire [31:0] wt_next,A_next,C_next;
	
	
	wire [159:0] digest;  //message digest
    	
   
    
  
    	
   // define "f"s and next's
	
	assign f_zero = (B & C) ^ (~B & D);
	assign f_twenty_or_sixty = B ^ C ^ D;
	assign f_forty = (B & C) ^ (C & D) ^ (B & D);
	assign ft = (counter < 'd21) ? f_zero : (counter < 'd41) ? f_twenty_or_sixty : (counter < 'd61) ? f_forty : f_twenty_or_sixty;
	assign wt = {W13 ^ W8 ^ W2 ^ W0};
   assign A_next = {A[26:0],A[31:27]} + ft + E + Kt + Wt;
	assign C_next = {B[1:0],B[31:2]};
	assign wt_next = {wt[30:0],wt[31]};	
	assign digest   = {A,B,C,D,E};
   assign counter1 = counter + 1;
	
	
	 	// In this portion we will process the control signal to perform the appropriate action
    	// Reset, clear, busy, or write disabled.
	
	
	always @(posedge clock)
			begin
    		if (reset)
    			csreg <= 1'b0;
    		else
    		if (wenable)
    			csreg[2:0] <= control[2:0];		
    		else
    		begin
    			csreg[3] <= busy_bit;			
    			if (~busy_bit)
    				csreg[1:0] <= 2'b00;	
    		end
	end
	
	// Section 1: Padding

	always @(posedge clock)
	 begin
		if (reset)
		begin
			counter <= 'd0;
			busy_bit <= 'b0;
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
			case (counter)  //section 2. : Using H's and A,B,C,D,E to manipulate the message
			
			'd0:
				begin
					if (csreg[1])
					begin
						W0 <= source;
						Wt <= source;
						busy_bit <= 'b1;
						counter <= counter1;
                                               	
						case (csreg[2])
							1'b0:	//first portion for the digest
								begin
									A <= `h0;
									B <= `h1;
									C <= `h2;
									D <= `h3;
									E <= `h4;
									
									H0 <= `h0;
									H1 <= `h1;
									H2 <= `h2;
									H3 <= `h3;
									H4 <= `h4;
								end
							1'b1:	// first internal portion
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
					begin	// waiting for something else to finish.....
						counter <= 'd0;
					end
				end
			'd1:
				begin
					W1 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd2:
				begin
					W2 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd3:
				begin
					W3 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd4:
				begin
					W4 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd5:
				begin
					W5 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd6:
				begin
					W6 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd7:
				begin
					W7 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd8:
				begin
					W8 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd9:
				begin
					W9 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd10:
				begin
					W10 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd11:
				begin
					W11 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd12:
				begin
					W12 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd13:
				begin
					W13 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd14:
				begin
					W14 <= source;
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd15:
				begin
					Wt <= source;
					
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
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
					Wt  <= wt_next;
					E <= D;
					D <= C;
					C <= C_next;
					B <= A;
					A <= A_next;
						
					counter <= counter1;
				end
			'd80:
				begin // Section 3: Message digest composition (remember: digest = {A,B,C,D,E})
					A <= A_next + H0;
					B <= A + H1;
					C <= C_next + H2;
					D <= C + H3;
					E <= D + H4;
					counter <= 'd0;
					busy_bit <= 'b0;
				end
			default:
				begin
                              busy_bit <= 1'b0;
					counter <= 1'd0;
					
				end
			endcase
		end	
	end 
	
	

// generate K(t) for masking

	always @ (posedge clock)
	begin
		if (reset)
		begin
			Kt <= 'b0;
		end
		else
		begin
			if (counter < 'd20)
				Kt <= `k0;
			else
			if (counter < 'd40)
				Kt <= `k1;
			else
			if (counter < 'd60)
				Kt <= `k2;
			else
				Kt <= `k3;
		end
	end

	// Section 4: Assign digest to the "product" wires
	always @ (posedge clock)
	begin
		if (reset)
		begin
			product <= 'b0;
			read_counter <= 'b0;
		end
		else
		begin
			if (csreg[0])
			begin
				read_counter <= 'd4;	
			end
			else
			begin
			if (~busy_bit)
			begin
				case (read_counter)
					'd4:	product <= digest[5*32-1:4*32];
					'd3:	product <= digest[4*32-1:3*32];
					'd2:	product <= digest[3*32-1:2*32];
					'd1:	product <= digest[2*32-1:1*32];
					'd0:	product <= digest[1*32-1:0*32];
					default:product <= 'b0;
				endcase
				if (|read_counter)
					read_counter <= read_counter - 'd1;
			end
			else
			begin
				product <= 'b0;
			end
			end
		end
	end
	
endmodule
 