module dff (
d  , // Data Input
clock    , // Clock Input
r , // Reset input 
q,         // Q output
iq
);

input d, clock, r ; 


output q,iq;


reg q,iq;


always @ ( posedge clock or negedge r)
if (~r) begin
  q <= 1'b0;
end  else begin
  q <= d;
end





endmodule 
 	

  
module dlatch (
d   , // Data Input
e     , // LatchInput
r  , // Reset input
q,       // Q output
iq
);

input d, e, r ; 


output q,iq;


reg q,iq;


always @ ( e or r or d)
if (~r) begin
  q <= 1'b0;
end else if (e) begin
  q <= d;
end



endmodule 

