`timescale 1ns/1ns
module cmp4b (
  input [3:0]x, [3:0]y,
  output eq, lt, gt
  );
  
  wire [1:0] eqIn, ltIn, gtIn;
  
  cmp2b comp2b0 (
  .x(x[1:0]), 
  .y(y[1:0]),
  .eq(eqIn[0]), 
  .lt(ltIn[0]), 
  .gt(gtIn[0])
  );
  
  cmp2b comp2b1 (
  .x(x[3:2]),
  .y(y[3:2]),
  .eq(eqIn[1]),
  .lt(ltIn[1]), 
  .gt(gtIn[1])
  );
  
  assign eq = eqIn[1] & eqIn[0];
  assign lt = ltIn[1] | ( eqIn[1] & ltIn[0] );
  assign gt = gtIn[1] | ( eqIn[1] & gtIn[0] );
  
endmodule

module cmp4btb ();
  
  integer i;
  
  reg [3:0] x, y;
  wire eq, lt, gt;
  
  cmp4b cmp4bUUT (
  .x(x), 
  .y(y),
  .eq(eq), 
  .lt(lt), 
  .gt(gt)
  );
  
  initial begin 
    for(i=0;i<1<<8;i=i+1) begin
      { x, y } = i;
      #10;
    end   
  end
  
endmodule


module fsmm (

    input clk,

    input rst_b,

    input A6,

    input X3,

    input I3,

    output reg [3:0] state

);

    localparam S0 = 4'b1000;

    localparam S1 = 4'b0100;

    localparam S2 = 4'b0010;

    localparam S3 = 4'b0001;

  

    reg [3:0] next_state;
    
always @(posedge clk or negedge rst_b) begin

        if (!rst_b)

            state <= S0;

        else

            state <= next_state;

    end

endmodule
