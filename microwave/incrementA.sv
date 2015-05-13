/* verilator lint_off UNUSED */
/* verilator lint_off WIDTH */
module incrementA(input logic reset, input logic clk, input logic[19:0] a, output logic out);

logic[8:0] counter; 

always_ff @(posedge clk)
begin
    if(reset)
    begin
        counter<= 8'd0; 
    end
    else
    begin
        out <= a[counter]; 
        if(counter < 8'd129) begin
            counter <= counter + 1'b1;
        end 
    end
end
endmodule
