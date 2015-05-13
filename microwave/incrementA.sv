/* verilator lint_off UNUSED */
module incrementA(input logic reset, input logic clk, input logic[19:0] a, output logic out);

        logic[4:0] counter; 

        always_ff @(posedge clk)
        begin
            if(reset)
            begin
                counter<= 5'd0; 
            end
            else
            begin
                out <= a[counter]; 
                counter <= counter + 1'b1; 
            end
        end
endmodule
