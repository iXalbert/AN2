module cons(input clk, rst_b,val, input [7:0] data, output reg [7:0] sum);
    integer last_valid_data;
    always @ (posedge clk, negedge rst_b)
        if(!rst_b) begin
            sum<=0;
            last_valid_data<=0;
        end
        else if(val) begin
            if(data>=last_valid_data)
            sum<=sum+data; //how do we check sa fei crescator?
            else sum=0;
        end
endmodule

module cons_tb;
    reg clk,rst_b;
    wire val; wire[7:0] data;
    wire [7:0] sum;
    prod i0(.clk(clk), .rst_b(rst_b), . val(val), .data(data));
    cons i1(.clk(clk), .rst_b(rst_b), .val(val), .data(data), .sum(sum));
    localparam CLK_PERIOD=100, CLK_CYCLES=100,RST_DURATION=25;
    initial begin
        clk=0;
        repeat (2*CLK_CYCLES) #(CLK_PERIOD/2) clk=1-clk; end
    initial begin
        rst_b=0;
        #RST_DURATION rst_b=1;
    end
endmodule