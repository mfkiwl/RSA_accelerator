/* verilator lint_off UNUSED */
/* verilator lint_off WIDTH */
/* verilator lint_off UNSIGNED */
module incrementA(input logic reset, input logic clk, input logic[127:0] a, input logic[127:0] b, input logic [127:0] n, output logic[127:0] r, output logic ready, output logic[127:0] outputAnswer);

logic[8:0] counter; 

logic[127:0] a_and_zero; 
logic[127:0] not_a_and_zero;
logic[127:0] a_and_n; 
logic[127:0] not_a_and_n; 

logic[127:0] a_and_two_n; 
logic[127:0] not_a_and_two_n; 
logic[127:0] twoN; 
logic fun; 

logic[127:0] twoR; 
logic[127:0] b_minus_n; 
logic[127:0] b_minus_two_n; 

logic out; 

always_ff @(posedge clk)
begin
    if(reset)
    begin
        counter[8:0] <= 9'd127;

        r[127:0] <= 6'd0; 
        a_and_zero[127:0] <= 9'd0; 
        not_a_and_zero[127:0] <= 9'd0; 

        a_and_n[127:0] <= 9'd0; 
        not_a_and_n[127:0] <= 9'd0; 

        a_and_two_n[127:0] <= 9'd0; 
        not_a_and_two_n[127:0] <= 9'd0; 

        twoN[127:0] <= n[127:0]<<1; 
        fun <= 1'b1; 

        b_minus_n[127:0] <= b[127:0] - n[127:0];

    end
    else
    begin
        b_minus_two_n[127:0] <= b[127:0] - twoN[127:0];
        case(fun)
            1'b0: begin
                if($signed(counter) == -2'd1) begin
                    outputAnswer[127:0] <= r[127:0];  
                    ready <= 1'b1; 
                end
                else begin
                    out <= a[counter];
                    a_and_zero[8:0] <= (twoR[127:0] + b[127:0] ); 
                    not_a_and_zero[127:0] <= (twoR[127:0]); 
                    a_and_n[127:0] <= (twoR[127:0] + b_minus_n[127:0]); 
                    not_a_and_n[127:0] <= (twoR[127:0] - n[127:0]); 
                    a_and_two_n[127:0] <= (twoR[127:0] + b_minus_two_n[127:0]); 
                    not_a_and_two_n[127:0] <= (twoR[127:0] - twoN[127:0]); 
                    fun <= 1'b1;
                end
            end
            1'b1: begin
                if($signed(counter) >= 8'd0) begin
                    counter <= $signed(counter) - 1'b1;
                    fun <= 1'b0; 
                    case(out)
                        1'b0: begin
                            if($signed(not_a_and_zero[127:0]) >= 0 && not_a_and_zero[127:0]<n[127:0]) begin
                                r[127:0] <= not_a_and_zero[127:0];
                                twoR[127:0] <= not_a_and_zero[127:0] <<1; 
                            end
                            else if($signed(not_a_and_n[127:0]) >= 0 && not_a_and_n[127:0]<n[127:0]) begin
                                r[127:0] <= not_a_and_n[127:0];
                                twoR[127:0] <= not_a_and_n[127:0] <<1; 
                            end
                            else begin
                                r[127:0] <= not_a_and_two_n[127:0];
                                twoR[127:0] <= not_a_and_two_n[127:0] <<1; 
                            end
                        end
                        1'b1: begin
                            if($signed(a_and_zero[127:0]) >= 0 && a_and_zero[127:0]<n[127:0]) begin
                                r[127:0] <= a_and_zero[127:0];
                                twoR[127:0] <= a_and_zero[127:0] <<1; 
                            end
                            else if($signed(a_and_n[127:0]) >= 0 && a_and_n[127:0]<n[127:0]) begin
                                r[127:0] <= a_and_n[127:0];
                                twoR[127:0] <= a_and_n[127:0] <<1; 
                            end 
                            else begin    
                                r[127:0] <= a_and_two_n[127:0];
                                twoR[127:0] <= a_and_two_n[127:0] <<1; 
                            end
                        end
                    endcase
                end

            end

        endcase
    end
end
endmodule
