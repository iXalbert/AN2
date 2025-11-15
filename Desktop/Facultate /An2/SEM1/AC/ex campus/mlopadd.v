module rgst #(
    parameter w=8
)(
    input clk, rst_b, ld, clr, input [w-1:0] d, output reg [w-1:0] q
);
    always @ (posedge clk, negedge rst_b)
        if (!rst_b)                 q <= 0;
        else if (clr)               q <= 0;
        else if (ld)                q <= d;
endmodule

module mlopadd(input clk,rst_b,input [9:0] x, output[15:0] a);
//for output, 16 bc 59,302<2^16
//for input, 3*199-2=575<1024
//look at the schema cu registers for sequential multi operant addition
    wire [9:0] xo;
    //w has 10 bits <= input bits
    rgst #(.w(10)) i0(.clk(clk),.rst_b(rst_b),.clr(1'd0),.ld(1'd1), .d(x), .q(xo));//clr=0 so thta it doesnt clear 
    //ld=1, always loads the obtained result/
    rgst #(.w(16)) i1(.clk(clk), .rst_b(rst_b),.clr(1'd0),.ld(1'd1), .d(a+xo), .q(a));

    
endmodule

module mlopadd_tb;
    reg clk, rst_b; reg [9:0] x;
    wire [15:0] a;
    mlopadd i0(.clk(clk), .rst_b(rst_b), .x(x), .a(a));

    localparam CLK_CYCKES=200, CLK_PERIOD=100, RST_DURATION=25; //200 clk cycles bc it takes 199 to generte all 199 sum terms, then another clk cycel to swtich x to 0 at the end bc otherwise its gonna keep adding numbers infine=itely
    

    initial begin
        clk=0; repeat(CLK_CYCKES*2) #(CLK_PERIOD/2) clk=1-clk; end
    
    initial begin
        rst_b=0; #(RST_DURATION)rst_b=1;
    end

    initial begin
        x=1; repeat(198) #CLK_PERIOD x=x+3; //generates x=1, 4, 7, ..., 575
        #CLK_PERIOD x=0;
    end

endmodule