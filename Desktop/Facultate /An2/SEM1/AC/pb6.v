`timescale 1ns/1ns
module Add4bc1 (
  input [3:0] x, [3:0] y,
  output [3:0] suma
  );
  
  integer i;
  wire [3:0] cIn, sIn;
  
  for(i=0;i<4;i=i+1) begin
    if (i==0)
      fac facUI0(
      .x(x[i]), 
      .y(y[i]), 
      .cIn(0),
      .sum(sIn[i]), 
      .cOut(cIn[i])
      );
    else
      fac facUI1(
      .x(x[i]),
      .y(y[i]), 
      .cIn(cIn[i-1]),
      .sum(sIn[i]), 
      .cOut(cIn[i])
      );
    
  end
  
  assign sum=sIn+cIn[3];
  
endmodule

module Add4bc1tb ();
  
  reg [3:0] x, y;
  wire [3:0] suma;
  
  integer i;
  
  Add4bc1 Add4bc1UUT (
  .x(x), 
  .y(y),
  .suma(suma)
  );
  
   initial begin
    for (i=0;i<1<<8;i=+1) begin
      { x, y } = i;
      #10;
    end
  end
  
endmodule;

 module regfl_4x8 (

    input [7:0] wr_data,

    input [1:0] wr_addr,

    input [1:0] rd_addr,

    input wr_e,

    input clk,

    output [7:0] rd_data

);

  

    wire [3:0] decode_out;

    wire [7:0] q0, q1, q2, q3;

  

    assign decode_out = (wr_e) ? (1 << wr_addr) : 4'b0000;

  

    reg [7:0] reg0, reg1, reg2, reg3;

  

    always @(posedge clk) begin

        if (decode_out[0]) reg0 <= wr_data;

        if (decode_out[1]) reg1 <= wr_data;

        if (decode_out[2]) reg2 <= wr_data;

        if (decode_out[3]) reg3 <= wr_data;

    end

  

    assign rd_data = (rd_addr == 2'b00) ? reg0 :

                     (rd_addr == 2'b01) ? reg1 :

                     (rd_addr == 2'b10) ? reg2 :

                     (rd_addr == 2'b11) ? reg3 : 8'b00000000;

  

endmodule
