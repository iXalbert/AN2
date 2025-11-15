module dff(input clk, input rst_b, input set_b, input d, output reg q);
    always @ (posedge clk, negedge rst_b, negedge set_b)
    if(!set_b)  q<=1;
    else if(!rst_b) q<=0;
    else q<=d;
endmodule

module lfsr5b(input clk, rst_b, output [4:0]q);
    genvar k;
    generate 
        for(k=0;k<5;k=k+1) begin
            if(k==0)
                dff i0(.clk(clk), .rst_b(1'd1), .set_b(rst_b),.d(q[4]), .q(q[k]));
            else if (k==2)
                dff i0(.clk(clk), .rst_b(1'd1), .set_b(rst_b),.d(q[k-1] ^ q[4]), .q(q[k]));
            else
                dff i0(.clk(clk), .rst_b(1'd1), .set_b(rst_b),.d(q[k-1]), .q(q[k]));
        end
    endgenerate
endmodule

module lfsr5b_tb;
    reg clk,rst_b;
    wire [4:0] q;
    lfsr5b i0(.clk(clk), .rst_b(rst_b), .q(q));
    localparam CLK_CYCLES = 35, CLK_PERIOD=100, RST_DURATION=25;
    initial begin
        clk=0;
        repeat (2*CLK_CYCLES) #(CLK_PERIOD/2) clk=1-clk;
    end
    initial begin
        rst_b=0; #RST_DURATION rst_b=1;
    end

endmodule

module sisr4b(input clk, rst_b,i, output [3:0] q);
    //version without generate
    dff i0(.clk(clk), .rst_b(rst_b), .set_b(1'd1),.d(q[3]^i), .q(q[0]));
    dff i1(.clk(clk), .rst_b(rst_b), .set_b(1'd1),.d(q[3]^q[0]), .q(q[1]));
    dff i2(.clk(clk), .rst_b(rst_b), .set_b(1'd1),.d(q[1]), .q(q[2]));
    dff i3(.clk(clk), .rst_b(rst_b), .set_b(1'd1),.d(q[2]), .q(q[3]));
endmodule

module check(input [4:0] i, output o);

//version 1
    //always @ (*)
    //if(i%8==0)
    //    o=1;
    //else o=0;

//or

    //un nr de 5 bits e multiplu de 8 cand ultimii 3 bits sunt 0
    assign o=(i[2:0]==0);

endmodule


module bist(input clk,rst_b, output [3:0] sig);
    wire [4:0] qw;
    wire iw;
    lfsr5b i0(.clk(clk), .rst_b(rst_b), .q(qw));
    check i1(.i(qw), .o(iw));
    sisr4b i2(.clk(clk), .rst_b(rst_b), .i(iw), .q(sig));

endmodule

module bist_tb;
    reg clk, rst_b;
    wire [3:0] sig;
    bist i0(.clk(clk),.rst_b(rst_b),.sig(sig));
    localparam CLK_CYCLES = 32, CLK_PERIOD=100, RST_DURATION=25;
    initial begin
        clk=0;
        repeat (CLK_CYCLES*2) #(CLK_PERIOD/2) clk=1-clk;
    end
    initial begin
        rst_b=0;
        #RST_DURATION rst_b=1;
    end
endmodule