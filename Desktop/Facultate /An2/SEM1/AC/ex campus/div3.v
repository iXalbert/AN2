module div3 (
  input [3:0] i,
  output reg [2:0] o
);
  always @(*) begin
    if(i>=0 && i<2)
      o=0;
    if(i>=2 && i<5)
      o=1;
    if(i>=5 && i<8)
      o=2;
    if(i>=8 && i<11)
      o=3;
    if(i>=12 && i<15)
      o=4;
    if(i>15 && i<18)
      o=5;
    if(i==16)
      o=6;
    end
endmodule

module div3_tb;
  reg [3:0] i;
  wire [2:0] o;

  div3 div3_i (.i(i), .o(o));

  integer k;
  initial begin
    $display("Time\ti\t\to");
    $monitor("%0t\t%b(%2d)\t%b(%0d)", $time, i, i, o, o);
    i = 0;
    for (k = 1; k < 16; k = k + 1)
      #10 i = k;
  end
endmodule