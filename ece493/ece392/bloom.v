/*A bloom filter verilog implemenation
Module: bit_vector: core part of a bloom filter
Module: Simplehash: hash function
Module: Fifo: buffer the write requests
Module: bloom: the Top module*/

/*remove this for synthesis; DEBUG mode includes testbench*/
//`define DEBUG

/*total len of the bit_vector*/
`define BIT_VEC_WIDTH 20
/*colume len*/
`define BIT_VEC_INDEX_L 8

`define BIT_VEC_LEN_L (1<<(`BIT_VEC_INDEX_L))


`define BIT_VEC_INDEX_H (`BIT_VEC_WIDTH - `BIT_VEC_INDEX_L)
`define BIT_VEC_LEN_H (1<<(`BIT_VEC_INDEX_H))

`define HIGH_ADDR (`BIT_VEC_WIDTH)-1:(`BIT_VEC_INDEX_L)
`define LOW_ADDR  (`BIT_VEC_INDEX_L)-1:0

`define BYTE3	31:24  
`define BYTE2	23:16
`define BYTE1	15:8
`define BYTE0	7:0

module bit_vector (clk,
                   rst,
                   rposition0,
                   rposition1,
                   rposition2,
                   rposition3,
                   rposition4,
                   rposition5,
                   rposition6,
                   rposition7,                                                                                               
                   wposition,
                   valid);
input clk;
input rst;

input [`BIT_VEC_WIDTH -1:0] rposition0; //8 ports for reading
input [`BIT_VEC_WIDTH -1:0] rposition1; //8 ports for reading
input [`BIT_VEC_WIDTH -1:0] rposition2; //8 ports for reading
input [`BIT_VEC_WIDTH -1:0] rposition3; //8 ports for reading
input [`BIT_VEC_WIDTH -1:0] rposition4; //8 ports for reading
input [`BIT_VEC_WIDTH -1:0] rposition5; //8 ports for reading
input [`BIT_VEC_WIDTH -1:0] rposition6; //8 ports for reading
input [`BIT_VEC_WIDTH -1:0] rposition7; //8 ports for reading

input [`BIT_VEC_WIDTH -1:0] wposition;    // 1 port for writing
//input [31:0] addr[0:7];

output valid;

wire [7:0]valid_bits;
wire write_enb;
reg  [(`BIT_VEC_LEN_L)-1:0]bit_vector [0: (`BIT_VEC_LEN_H)-1];

`ifdef DEBUG
integer i,j;

assign wx1 = wposition[`HIGH_ADDR];
assign wx2 = wposition[`LOW_ADDR];

assign rx1 = rposition1[`HIGH_ADDR];
assign rx2 = rposition1[`LOW_ADDR];
`endif

assign valid_bits [0] = (bit_vector[rposition0[`HIGH_ADDR]][rposition0[`LOW_ADDR]]) & 1'b1;
assign valid_bits [1] = (bit_vector[rposition1[`HIGH_ADDR]][rposition1[`LOW_ADDR]])& 1'b1;
assign valid_bits [2] = (bit_vector[rposition2[`HIGH_ADDR]][rposition2[`LOW_ADDR]])& 1'b1;
assign valid_bits [3] = (bit_vector[rposition3[`HIGH_ADDR]][rposition3[`LOW_ADDR]])& 1'b1;
assign valid_bits [4] = (bit_vector[rposition4[`HIGH_ADDR]][rposition4[`LOW_ADDR]])& 1'b1;
assign valid_bits [5] = (bit_vector[rposition5[`HIGH_ADDR]][rposition5[`LOW_ADDR]])& 1'b1;
assign valid_bits [6] = (bit_vector[rposition6[`HIGH_ADDR]][rposition6[`LOW_ADDR]])& 1'b1;
assign valid_bits [7] = (bit_vector[rposition7[`HIGH_ADDR]][rposition7[`LOW_ADDR]])& 1'b1;

/*
always @(wposition)
begin
    if (wposition)
       write_enb <= 1;
    else
       write_enb <= 0;
end
*/
assign write_enb = (wposition)?1:0;

//assign x2 = 1'b1 <<wposition[`LOW_ADDR];

//always @((posedge clk or posedge rst) && wposition)
always @(posedge clk)
begin: update_bloom

`ifdef DEBUG
    if (rst)
    begin
       for (i = 0; i < `BIT_VEC_LEN_H ; i = i+1)
          for (j =0; j < `BIT_VEC_LEN_L; j =j+1)
            bit_vector[i][j]<= 1'b0;
    end
    else
`endif

    if (write_enb)     
        bit_vector[wposition[`HIGH_ADDR]][wposition[`LOW_ADDR]] <= 1'b1;
end

assign valid = valid_bits[0] & valid_bits[1]&valid_bits[2]&valid_bits[3]&
               valid_bits[4] & valid_bits[5]&valid_bits[6]&valid_bits[7];
               
endmodule 


module Simplehash(pc, tpc, hash0,hash1,hash2,hash3,hash4,hash5,hash6,hash7);
input [31:0]pc;
input [31:0]tpc;

output [31:0] hash0;
output [31:0] hash1;
output [31:0] hash2;
output [31:0] hash3;
output [31:0] hash4;
output [31:0] hash5;
output [31:0] hash6;
output [31:0] hash7;

assign {hash0[`BYTE3],hash0[`BYTE2], hash0[`BYTE1],hash0[`BYTE0]}
    = {pc[`BYTE3]^tpc[`BYTE3],
       pc[`BYTE1]^tpc[`BYTE2],
       pc[`BYTE2]^tpc[`BYTE1],
       pc[`BYTE0]^tpc[`BYTE0]
       };

assign {hash1[`BYTE3],hash1[`BYTE2], hash1[`BYTE1],hash1[`BYTE0]}
    = {pc[`BYTE0]^tpc[`BYTE3],
       pc[`BYTE1]^tpc[`BYTE2],
       pc[`BYTE2]^tpc[`BYTE1],
       pc[`BYTE3]^tpc[`BYTE0]
       };              

assign {hash2[`BYTE3],hash2[`BYTE2], hash2[`BYTE1],hash2[`BYTE0]}
    = {pc[`BYTE1]^tpc[`BYTE3],
       pc[`BYTE0]^tpc[`BYTE2],
       pc[`BYTE3]^tpc[`BYTE1],
       pc[`BYTE2]^tpc[`BYTE0]
       };
       
assign {hash3[`BYTE3],hash3[`BYTE2], hash3[`BYTE1],hash3[`BYTE0]}
    = {pc[`BYTE0]^tpc[`BYTE3],
       pc[`BYTE3]^tpc[`BYTE2],
       pc[`BYTE2]^tpc[`BYTE1],
       pc[`BYTE1]^tpc[`BYTE0]
       };

assign {hash4[`BYTE3],hash4[`BYTE2], hash4[`BYTE1],hash4[`BYTE0]}
    = {pc[`BYTE2]^tpc[`BYTE3],
       pc[`BYTE1]^tpc[`BYTE2],
       pc[`BYTE0]^tpc[`BYTE1],
       pc[`BYTE3]^tpc[`BYTE0]
       };

assign {hash5[`BYTE3],hash5[`BYTE2], hash5[`BYTE1],hash5[`BYTE0]}
    = {pc[`BYTE1]^tpc[`BYTE3],
       pc[`BYTE2]^tpc[`BYTE2],
       pc[`BYTE3]^tpc[`BYTE1],
       pc[`BYTE0]^tpc[`BYTE0]
       };

assign {hash6[`BYTE3],hash6[`BYTE2], hash6[`BYTE1],hash6[`BYTE0]}
    = {pc[`BYTE3]^tpc[`BYTE3],
       pc[`BYTE0]^tpc[`BYTE2],
       pc[`BYTE1]^tpc[`BYTE1],
       pc[`BYTE2]^tpc[`BYTE0]
       };

assign {hash7[`BYTE3],hash7[`BYTE2], hash7[`BYTE1],hash7[`BYTE0]}
    = {pc[`BYTE2]^tpc[`BYTE3],
       pc[`BYTE3]^tpc[`BYTE2],
       pc[`BYTE0]^tpc[`BYTE1],
       pc[`BYTE1]^tpc[`BYTE0]
       };                        

endmodule


/* A module of FIFO*/
module FIFO (
   clk,rst,
   Data_out,
   Data_in,
   stack_empty,
   stack_full,   
   write_to_stack,
   read_from_stack
   );
  
   parameter stack_width = 32;
   parameter stack_height = 64;
   parameter stack_ptr_width = 6;
   parameter write_ports_num = 8;
  
   output [stack_width-1: 0] Data_out;
   output                    stack_empty, stack_full;
  
   input [stack_width*write_ports_num-1: 0] Data_in;
   input clk, rst;
   input write_to_stack, read_from_stack;
  
   reg   [stack_ptr_width-1: 0] read_ptr, write_ptr;  
   reg   [stack_ptr_width: 0] ptr_diff; //Gap between ptrs
  
   reg   [stack_width -1:0] Data_out;
   reg   [stack_width -1:0] stack[stack_height-1: 0]; //memory array
  
   assign stack_empty = (ptr_diff ==0)? 1'b1: 1'b0;
   assign stack_full  = (ptr_diff > stack_height - write_ports_num)? 1'b1:1'b0;
  
   always @(posedge clk or posedge rst) begin: data_transfer
       if (rst) Data_out <= 0;
      
       else if ((read_from_stack) && (!write_to_stack) && (!stack_empty))
           Data_out <= stack[read_ptr];
       else if ((write_to_stack) && (!read_from_stack) && (!stack_full))
       begin
           stack[write_ptr] <= Data_in[stack_width-1: 0];
           stack[write_ptr+1] <= Data_in[2*stack_width-1: stack_width];
           stack[write_ptr+2] <= Data_in[3*stack_width-1: 2*stack_width];
           stack[write_ptr+3] <= Data_in[4*stack_width-1: 3*stack_width];
           stack[write_ptr+4] <= Data_in[5*stack_width-1: 4*stack_width];
           stack[write_ptr+5] <= Data_in[6*stack_width-1: 5*stack_width];
           stack[write_ptr+6] <= Data_in[7*stack_width-1: 6*stack_width];
           stack[write_ptr+7] <= Data_in[8*stack_width-1: 7*stack_width];
       end
       else if (stack_empty)
          Data_out <= 0;
   end
  
   always @(posedge clk or posedge rst) begin: data_update
      if (rst)
          begin
             read_ptr <= 0;
             write_ptr <= 0;
             ptr_diff <= 0;
          end
      else
         if ((write_to_stack) && (!stack_full) && (!read_from_stack))
            begin
                 write_ptr <= write_ptr + write_ports_num;
                 ptr_diff <= ptr_diff + write_ports_num;
            end
      else
         if ((!write_to_stack) && (!stack_empty) && (read_from_stack))
            begin
                read_ptr <= read_ptr + 1;
                ptr_diff <= ptr_diff - 1;
            end                   
   end
   
endmodule

module bloom(r_wb, pc, tpc, enb, valid, clk, rst);
input r_wb;
input [31:0]pc;
input [31:0]tpc;
input enb;
input clk;
input rst;

output valid;

wire [31:0] hash0;
wire [31:0] hash1;
wire [31:0] hash2;
wire [31:0] hash3;

wire [31:0] hash4;
wire [31:0] hash5;
wire [31:0] hash6;
wire [31:0] hash7;

/*8 addresses generated by tpc/pc*/
wire [32*8-1: 0]write_data;
/* The only address that I use to feed into bloom filter*/
wire [32-1:0] write_datum;

assign write_data = {hash0, hash1, hash2, hash3,hash4, hash5, hash6, hash7};

FIFO WriteBufUnit(
   .Data_out(write_datum), 
   .Data_in(write_data),
   .stack_empty(),
   .stack_full(),
   .clk(clk),
   .rst(rst),
   .write_to_stack(r_wb),
   .read_from_stack(~r_wb)
   );
     
Simplehash SHunit(.pc(pc), .tpc(tpc),
                  .hash0(hash0),.hash1(hash1),.hash2(hash2),.hash3(hash3),
                  .hash4(hash4),.hash5(hash5),.hash6(hash6),.hash7(hash7));

bit_vector BLOOM_VALIDATION_UNIT(.clk(clk),
                                 .rst(rst),
                                 .rposition0(hash0[`BIT_VEC_WIDTH -1:0]),
                                 .rposition1(hash1[`BIT_VEC_WIDTH -1:0]),
                                 .rposition2(hash2[`BIT_VEC_WIDTH -1:0]),
                                 .rposition3(hash3[`BIT_VEC_WIDTH -1:0]),
                                 .rposition4(hash4[`BIT_VEC_WIDTH -1:0]),
                                 .rposition5(hash5[`BIT_VEC_WIDTH -1:0]),
                                 .rposition6(hash6[`BIT_VEC_WIDTH -1:0]),
                                 .rposition7(hash7[`BIT_VEC_WIDTH -1:0]),
                                 .wposition(write_datum[`BIT_VEC_WIDTH -1:0]), //leave empty for writing
                                 .valid(valid));
                                 
endmodule


`ifdef DEBUG
module bloom_test;

   reg clk, rst,r_wb;
   reg [31:0] pc;
   reg [31:0] tpc;
   wire valid;
   
   bloom bloom_filter(r_wb, pc, tpc, 1'b1, valid, clk, rst);
   
   initial begin
   #5 rst =1;
   #40 rst = 0;
   #600 rst = 1;
   #40 rst = 0;
   end
   
   initial begin   
   //#20 n = 256'h00112233445566778899aabbccddeeff_0123456789abcdeffedcba9876543210;
   # 40 r_wb = 1;
   # 5 pc = 32'h4012aabb; tpc=32'h2018ccdd;
   # 10 r_wb = 0;
   
   #100 r_wb=1;
   #5 pc = 32'h40121122; tpc=32'h20183344;
   #15 r_wb=0;
   
   #300 pc = 32'h4012aaee; tpc=32'h2018ccdd;
   #100 pc = 32'h4012aabb; tpc=32'h2018ccdd;
   #100 pc = 32'h4012aaee; tpc=32'h2018ccdd;
   //#100 Data_in = 256'h0123456789abcdeffedcba9876543210_00112233445566778899aabbccddeeff;
   end
   
   initial begin

   end

   always begin
      clk=0;
      #10 clk =1;
      #10;
   end

endmodule

`endif


`ifdef DEBUG_FIFO
module t_FiFO();
   parameter stack_width = 32;
   parameter stack_height = 16;
   parameter stack_ptr_width = 4;
   parameter write_ports_num = 8;

   wire [stack_width-1: 0] Data_out;
   wire stack_empty, stack_full;
  
   reg [stack_width*write_ports_num-1: 0] Data_in;
   
   reg clk, rst,write_to_stack, read_from_stack;
   wire[31:0] w0,w1,w2,w3,w4,w5,w6,w7,
        w8,w9,w10,w11,w12,w13,w14,w15,
        w16,w17,w18,w19,w20,w21,w22,w23,
        w24,w25,w26,w27,w28,w29,w30,w31;
  
   assign w0 = M1.stack[0]; assign w1= M1.stack[1];
   assign w2= M1.stack[2];assign w3= M1.stack[3];
   assign w4= M1.stack[4];assign w5= M1.stack[5];
   assign w6= M1.stack[6];assign w7= M1.stack[7];
   
   FIFO #(32, 16, 4, 8) M1 (
   Data_out,
   Data_in,
   stack_empty,
   stack_full,
   clk,rst,
   write_to_stack,
   read_from_stack
   );
   
   always begin
      clk=0;
      #10 clk =1;
      #10;
   end
   
   initial #1000 $stop;
   
   initial begin
   #5 rst =1;
   #40 rst = 0;
   #600 rst = 1;
   #40 rst = 0;
   end
   
   initial begin
   
   #5 Data_in = 256'h00112233445566778899aabbccddeeff_0123456789abcdeffedcba9876543210;
   #100 Data_in = 256'h0123456789abcdeffedcba9876543210_00112233445566778899aabbccddeeff;
   end
   
   initial begin
   #70 write_to_stack = 1; read_from_stack =0;
   #300 write_to_stack = 0; 
   #20 read_from_stack =1;
   end
   
endmodule
`endif //DEBUG_FIFO   
