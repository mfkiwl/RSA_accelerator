module blakley(
        input logic clk, 
        input logic[15:0] a, b, n,
        output logic[15:0] R
    ); 

    assign R[15:0] = 16'b0;
    
    wire[3:0] counter = 4'b1111;
    wire[3:0] counter2 = 4'b1110;
    logic[1:0] sub_a;
    logic[2:0] step = 3'b0;

    always_comb begin
        sub_a = {a[counter], a[counter2]};
    end

    always_ff @(posedge clk) begin

        case(step)
            3'd0: begin
                R <= R + R;
                step <= step + 1;
            end

            3'd1: begin
                step <= step + 1;
                R <= R + R;
            end
            
            3'd2: begin
                R <= R + sub_a * b;
                step <= step + 1;
            end

            3'd3: begin
                if(R >= n)
                    R <= R - n;
                else
                    step <= step + 1;
            end

            3'd4: begin
                if(counter2 > 4'b0) begin
                    counter <= counter - 2;
                    counter2 <= counter2 - 2;
                    step <= 3'b0;
                end
            end

            default:
                step <= 3'b0;
        endcase
    end
endmodule
