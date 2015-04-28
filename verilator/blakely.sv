/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */
module blakely(input logic clk,input logic reset_l, input logic[4:0] a, input logic[4:0] b, input logic[4:0] n,  output logic[4:0] out_number, output logic ready); 

logic fun;
logic [5:0] count;
logic inputToFunctionR;
logic [4:0] r; 
logic [4:0] previousR; 
logic subModuleReady;
logic [1:0] step; 

logic [4:0] n1; 
logic [4:0] n2; 
logic [4:0] secondR; 
logic signed [4:0] nMinusOne; 
logic signed [4:0] nMinusTwo;
logic signed [4:0] nMinusZero;

always_ff @(posedge clk) 
begin
    if(reset_l) begin
        out_number[4:0] <= 5'd1; 
        fun <= 1'b0;
        count[5:0]  <= 6'd0;
        r <= 5'd0;
        subModuleReady <= 1'b1;
        ready <= 1'b0; 
        secondR <= 5'd0; 
        step <= 2'b00;
        previousR <= 4'd0;  
    end

    else begin

        n1[4:0] <= n[4:0]; 
        n2[4:0] <= n[4:0]<<1; 
        previousR[4:0] <= r[4:0]<<1;
        secondR[4:0] <=  b[4:0] ; 

        case(fun) 
            1'b0: begin
                case(count)
                    6'd0: begin
                        if(subModuleReady && !ready) begin
                            inputToFunctionR <= a[4];
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0;
                            count[5:0] <= count[5:0] + 6'd1;  
                        end 
                    end
                    6'd1: begin
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[3]; 
                            subModuleReady <= 1'b0;
                            count[5:0] <= count[5:0] + 6'd1;  
                            fun <= 1'b1; 
                        end 
                    end 
                    6'd2: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[2]; 
                            subModuleReady <= 1'b0;
                            count[5:0] <= count[5:0] + 6'd1;  
                            fun <= 1'b1;  
                        end
                    end 
                    6'd3: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[1]; 
                            subModuleReady <= 1'b0;
                            count[5:0] <= count[5:0] + 6'd1;  
                            fun <= 1'b1;  
                        end
                    end 
                    6'd4: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[0]; 
                            subModuleReady <= 1'b0;
                            count[5:0] <= count[5:0] + 6'd1;  
                            fun <= 1'b1;  
                        end
                    end 
                    6'd5: begin 
                        if(subModuleReady) begin 
                            out_number[4:0] <= r[4:0]; 
                            ready <= 1'b1;
                        end 
                    end 
                    default: begin
                        out_number[4:0] <= 6'd0; 
                    end
                endcase
            end
            1'b1: begin
                case(step)
                    2'b00: begin
                        case(inputToFunctionR)
                            1'b0: begin
                                r[4:0] <= previousR[4:0]; 
                                step <= 2'b01;                     
                            end
                            1'b1: begin
                                r[4:0] <= (secondR[4:0]+previousR[4:0]);
                                step <= 2'b01;                     
                            end
                        endcase
                    end
                    2'b01: begin
                        nMinusOne[4:0] <= r[4:0] - n1[4:0];
                        nMinusTwo[4:0] <= r[4:0] - n2[4:0];                         
                        step <= 2'b10; 
                    end
                    2'b10:begin
                        if(r[4:0] < n[4:0]) begin
                            fun <= 1'b0;
                            subModuleReady <= 1'b1;
                        end                        
                        else if($signed(nMinusOne[4:0]) >= 0 && nMinusOne[4:0] <= n[4:0]) begin
                            r[4:0] <= nMinusOne[4:0];                     
                            fun <= 1'b0;
                            subModuleReady <= 1'b1;
                        end
                        else begin
                            r[4:0] <= nMinusTwo[4:0];                         
                            fun <= 1'b0;
                            subModuleReady <= 1'b1;
                        end
                        step<= 2'b00; 
                    end
                    default: begin
                    end
                endcase
            end
        endcase 
    end
end
endmodule

