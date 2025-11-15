module sisr4b(
    input clk,
    input rst_b,
    input d,
    input i
    output reg [3:0] q
);  
    
    generate
      genvar k;
      for( k = 0 ; k < 4 ; k = k + 1 ) begin: vect 
        if( k == 0 ) begin
          d_ff ff(.clk(clk),.rst_b(rst_b),.d(i^q[3]),.q(q[0]));
        end
        else if( k == 1 ) begin
          d_ff ff(.clk(clk),.rst_b(1),.q(q[i]),.d(q[3]^q[0]),.q(q[1]));
        end 
        else begin
          d_ff ff(.clk(clk),.rst_b(1),.q(q[i]),.d(q[k-1]),q(q[k]));
        end
      end
    endgenerate 
  
endmodule