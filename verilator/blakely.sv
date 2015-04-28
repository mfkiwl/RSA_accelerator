module blakely(input logic clk,input logic reset_l,input logic[4:0] a, input logic[4:0] b, output logic[4:0] out_number); 
    always_ff @(posedge clk) begin
        if(reset_l)
            out_number[4:0] <= 5'd1; 
        else begin
            out_number[4:0] <= a[4:0] + b[4:0] ; 
        end
    end
endmodule

