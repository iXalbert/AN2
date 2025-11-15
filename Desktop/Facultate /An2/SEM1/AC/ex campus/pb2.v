module counter #(
  parameter w = 8,
  parameter  vi = 8'hff)(
  
  input clk,
  input rst_b,c_up,clr,
  output reg [w-1:0] q 
);

always @(posedge clk or negedge rst_b) begin
  
  if(!rst_b) begin
    q <= vi;
  end
  if(clr) begin
    q<= vi;
  end
  else if(c_up) begin
    q<= q+1;
end

end
          
endmodule 

module counter_tb();
  
  parameter w=8;
  parameter vi = 8'haa;
  
  reg clk,rst_b,c_up,clr;
  wire [w-1:0]q;
  
  counter #(
    .w(w),
    .vi(vi)
  )
  
  uut(
    .clk(clk),
    .rst_b(rst_b),
    .c_up(c_up),
    .clr(clr),
    .q(q)
  );
  
  initial begin 
    {clk,rst_b,c_up,clr} = 4'b0001;
    forever #100 clk = ~clk;
    
end
  
  initial begin
    
    #5 rst_b=~rst_b;
    #50 c_up=~c_up;
    #15 clr=~clr;
    #40 clr=~clr;
    #100 c_up=~c_up;
    #75 c_up=~c_up;
    #25 clr=~clr;
    
  end
  
endmodule