module fac(
  input x,y,cIn,
  output z,cOut
);
  
  assign z = x ^ cIn ^ y;
  assign cOut = x & y | x & cIn | y & cIn;
  
endmodule

module fac_tb(
);
  reg x, y, cIn;
  wire z, cOut;
  fac dut(
    .x(x),
    .y(y),
    .cIn(cIn),
    .z(z),
    .cOut(cOut)
  );
  
  integer i;
  
  initial begin 
    $display("time\tx\ty\tcIn\t||z\tcOut");
    $monitor("%4t\t%b\t%b\t||%b\t%b",$time,x,y,cIn,z,cOut);
    for(i=0;i<8;i=i+1) begin
      {x,y,cIn} =  i;
      #10;
    end
  end
endmodule