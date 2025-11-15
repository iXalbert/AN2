module lfsr5b(
    input clk,
    input rst_b,
    input d,
    output reg q
);  
    
    generate
      genvar i;
      for( i = 0 ; i < 5 ; i = i + 1 ) begin: vect 
        if( i == 0 )
          d_ff ff(.clk(clk),.rst_b(1),.q(q[i]),.d(q[4]),.set_b(rst_b));
        else if( i == 2 )
          d_ff ff(.clk(clk),.rst_b(1),.q(q[i]),.d(q[4]^q[1]));
        else
          d_ff ff(.clk(clk),.rst_b(1),.q(q[i]),.d(q[i-1]]));
            
      end
    endgenerate 
  
endmodule