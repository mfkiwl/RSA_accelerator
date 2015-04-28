module our(input logic clk,input logic reset_l,output logic[4:0] out_number); 
    always_ff @(posedge clk) begin
        if(reset_l)
            out_number[4:0] <= 5'd1; 
        else begin
        out_number[4:0] <= out_number[4:0] + 5'd1 ; 
        end
    end
endmodule

