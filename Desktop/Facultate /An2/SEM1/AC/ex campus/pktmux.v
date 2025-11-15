`timescale 1ns/1ns

module pktmux(
  input [63:0] msg_len,pkt,
  input pad_pkt,zero_pkt,mgln_pkt,
  output reg [63:0] o
);

  always @(*)
  if(pad_pkt) 
    o = (1 << 63);
  else if(zero_pkt)
    o = 0;
  else if(mgln_pkt)
    o = msg_len;
  else
    o <= pkt;
    
endmodule
  
module pktmux_tb();
  
  reg [63:0] msg_len,pkt;
  reg pad_pkt,zero_pkt,mgln_pkt;
  wire [63:0] o;

  pktmux u0 (
    .msg_len(msg_len),
    .pkt(pkt),
    .pad_pkt(pad_pkt),
    .zero_pkt(zero_pkt),
    .mgln_pkt(mgln_pkt),
    .o(o)
  );
  
task urand64 (output reg [63:0]r);

  begin
    r[63:32] = $urandom ; 
    r[31:0] = $urandom ;
  end
endtask

  parameter Ciclu = 100;
  
  initial begin
    
    repeat(5) begin 
      
      {pad_pkt,zero_pkt,mgln_pkt} = 'b000; #Ciclu;
      {pad_pkt,zero_pkt,mgln_pkt} = 'b100; #Ciclu;
      {pad_pkt,zero_pkt,mgln_pkt} = 'b010; #Ciclu;
      {pad_pkt,zero_pkt,mgln_pkt} = 'b001; #Ciclu;
      
    end
    
      {pad_pkt,zero_pkt,mgln_pkt} = 'b000; #Ciclu;
    
  end
  
    initial begin 
      
      repeat(20) begin
        
        urand64(pkt);
        urand64(msg_len);
        
        #Ciclu;
      end
      
      urand64(pkt);
      urand64(msg_len);
    end

endmodule