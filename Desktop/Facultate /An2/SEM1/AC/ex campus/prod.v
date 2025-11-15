module prod(input clk,rst_b, output reg val, output reg [7:0] data);
integer valid_cycles; //random number of valid cycles, between 3 nd 5
integer invalid_cycles;//between 1 and 4
always @ (posedge clk, negedge rst_b) begin
    if(!rst_b) begin
        val<=0;
        invalid_cycles<=1; end
    else if (valid_cycles>0) begin
        val<=1;
        data<= $urandom_range(0,5);
        valid_cycles <= valid_cycles-1;
        if(valid_cycles==1) begin // 1 because pf <= se evalueaza intai toate
        //expresiile din stanga de pe toate liniile, iar doar apoi cele din dreapta 
        //=> valid_cycles-1 devine 0 doar la sfarsit, dupa evaluarea ifuluui> noi practic testam daca e 0
            invalid_cycles <= $urandom_range(1,4);
        end
    end
    else if (invalid_cycles>0) begin
        val<=0;
        invalid_cycles<=invalid_cycles-1;
        if(invalid_cycles == 1) begin
            val<=1;
            data <= $urandom_range(0,5);
            valid_cycles <= $urandom_range(1,4);
        end
    end
end
endmodule

module prod_tb;
    reg clk,rst_b;
    wire val; wire [7:0] data;
    prod i0(.clk(clk), .rst_b(rst_b), . val(val), .data(data));
    localparam CLK_PERIOD=100, CLK_CYCLES=100,RST_DURATION=25;
    initial begin
        clk=0;
        repeat (2*CLK_CYCLES) #(CLK_PERIOD/2) clk=1-clk; end
    initial begin
        rst_b=0;
        #RST_DURATION rst_b=1;
    end
endmodule