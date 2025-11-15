module d_ff(
    input clk,
    input rst_b,
    input set_b,
    input d,
    output reg q
);  
    
    always@(posedge clk or negedge rst_b or negedge set_b )
      if( !rst_b )
          q<=0;
      else  if (!set_b)
          q <= 0;
      else
          q<=d;
    end
  
endmodule