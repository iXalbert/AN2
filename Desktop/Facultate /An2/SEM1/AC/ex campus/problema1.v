`timescale 1ns/1ns

module sadd(
  input clk,rst_b,
  input x,y,
  output reg s
);

  localparam S0_ST = 2'd0;
  localparam S1_ST = 2'd1;
  
  reg [1:0] st;
  reg [1:0] st_nxt;
  
  always @ (posedge clk, negedge ~rst_b) begin
      
    if ( ~rst_b )
      st <= S0_ST;
    else
      st <= st_nxt;
      
    end
    
    always @ (*) begin
      
      s <= 0;
      st_nxt <= S0_ST;
      
      case (st) 
        
        S0_ST: 
        if(x^y) begin
          
          s<=1;
          st_nxt <= S0_ST;
        end
        else begin
          
          s<=0;
          if(~x & ~y) 
          
            st_nxt<=S0_ST;
          else
            st_nxt<=S1_ST;
          end
          
          S1_ST:
          if(x^y) begin
             s<=0;
             st_nxt <=S1_ST;
           end
         else begin 
            if(~x & ~y)
            st_nxt <= S1_ST;
          else
            st_nxt <= S0_ST;
          end
               endcase 
             end
           endmodule
           
module sadd_tb();
  
  localparam CLK_PERIOD = 100;
  
  reg x,y,clk,rst_b;
  wire s;
  
  sadd sadd_UUT(
    .x(x),
    .y(y),
    .s(s),
    .clk(clk),
    .rst_b(rst_b)
  );
  
  initial begin
    
    clk = 0;
    rst_b = 0;
    
    x=0;
    y=1;
    
    #(CLK_PERIOD / 4);
    
    rst_b = ~rst_b;
    
    #(CLK_PERIOD / 4 * 3);
    
    x=~x;
    
    # CLK_PERIOD
    y=~y;
    # CLK_PERIOD
    x=~x;
    # CLK_PERIOD
    y=~y;
    
    # CLK_PERIOD $stop;
    
  end
  
  always begin 
    
    #(CLK_PERIOD >> 1)
    clk = ~clk;
    
  end
  
endmodule
            