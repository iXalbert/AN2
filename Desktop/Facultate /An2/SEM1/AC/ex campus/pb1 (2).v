module mlopadd # (
  parameter width_x = 7,
  parameter width_a = 14    
) (
  input clk, rst,
  input [width_x - 1 : 0] x,  
  output reg [width_a - 1 : 0] a
);

  reg [width_a - 1 : 0] interm;

  always @ (posedge clk or posedge rst) begin
    if (rst)
      interm <= 0;
    else
      interm <= a;  
  end

  always @ (interm) begin
    a = interm + 2 * x + 1;
  end

endmodule

module mlopadd_tb();
  
  localparam CLK = 100;
  localparam nrCLK = 100;
  localparam start_value = 0;
  
  reg clk, rst;
  reg [6:0] x;
  wire [13:0] a;
  
  mlopadd mlopadd_UUt(
    .clk(clk),
    .rst(rst),
    .x(x),
    .a(a)
  );
  
  initial begin 
    clk = 0;
    rst = 1;
    x = start_value + 1;
    
    #(CLK >> 2) rst = ~rst;  
    
    #(CLK * nrCLK) $stop;    
  end
  
  always begin 
    #(CLK >> 1) clk = ~clk;  
  end
  
  always begin 
    #(CLK) x = x + 1; 
  end
  
endmodule
