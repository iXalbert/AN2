module cmp2b (
input [1:0]x, [1:0]y,
output eq, lt, gt
);

  if ( x == y )
    assign { eq, lt, gr } = 3'b100;
  else if ( x > y )
    assign { eq, lt, gr } = 3'b001;
  else
    assign { eq, lt, gr } = 3'b010;
    
  
endmodule
