module add2b(
  input [1:0] x, y,
  input  cIn,
  output [1:0] z,
  output cOut
);

wire c1;

fac fac1(
  .x(x[0]),
  .y(y[0]),
  .cIn(cIn),
  .z(z[0]),
  .cOut(c1)
);

fac fac2(
  .x(x[1]),
  .y(y[1]),
  .cIn(c1),
  .z(z[1]),
  .cOut(cOut)
);

endmodule

module add2b_tb(
);
  reg [1:0] x, y;
  reg cIn;
  wire [1:0] z;
  wire cOut;
  
  add2b dut(
    .x(x),
    .y(y),
    .cIn(cIn),
    .z(z),
    .cOut(cOut)
  );
  
  integer i;
  initial begin
  $display("time\tx\ty\\tcIn\t||z\tcOut");
  $monitor("%4t\t%b\t%b\t%b\t||%b\t%b",$time,x,y,cIn,z,cOut);
  for(i=0;i<32;i=i+1) begin
    {x,y,cIn} = i;
    #10;
  end
end
endmodule