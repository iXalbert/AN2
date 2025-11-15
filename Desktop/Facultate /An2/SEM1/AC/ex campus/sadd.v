module sadd( input clk , input rst_b,
          input[1:0] x,
          output reg a );
          
          
      localparam S0_ST = 1'd0;
      localparam S1_ST = 1'd1;
      
      reg st;
      reg st_nxt;
      
      always @(*)
          case(st)
              S0_ST : if( x == 2'b11 ) st_nxt = S1_ST;
                    else st_nxt = S0_ST;
              S1_ST : if( x == 2'b00) st_nxt = S0_ST;
                    else st_nxt = S1_ST;
          endcase
      
      
      always @(*) begin
            a = 1'd0;
            case(st)
              S0_ST : if( x == 2'b11 || x == 2'b00 ) a = 0;
                    else a = 1;
              S1_ST : if( x == 2'b00 || x == 2'b11 ) a = 1;
                    else a = 0;
            endcase end
      
      
      always @(posedge clk or negedge rst_b)
            if( !rst_b) st <=S0_ST;
            else st<= st_nxt;
              
endmodule

module sadd_tb;
  reg clk, rst_b;
  reg[1:0] x;
  wire a;
  
  sadd uut(.clk(clk),.rst_b(rst_b),.x(x),.a(a));
  
  initial begin 
    clk =0;
    forever #100 clk = ~clk;
  end
  
  initial begin
    
      rst_b = 0;
      #25 rst_b = 1;
      #100 x = 2'b00;
      #120 x = 2'b01;
      #140 x = 2'b10;
      #160 x = 2'b11;
      
      #180 x = 2'b10;
      #200 x = 2'b01;
      #220 x = 2'b11;
      #240 x = 2'b00;
  end

endmodule