/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */
module blakley128(input logic clk,input logic reset_l, input logic[127:0] a, input logic[127:0] b, input logic[127:0] n,  output logic[127:0] out_number, output logic ready); 

logic fun;
logic [9:0] count;
logic inputToFunctionR;
logic [127:0] r; 
logic [127:0] previousR; 
logic subModuleReady;
logic [1:0] step; 

logic [127:0] n1; 
logic [127:0] n2; 
logic [127:0] secondR; 
logic signed [127:0] nMinusOne; 
logic signed [127:0] nMinusTwo;
logic signed [127:0] nMinusZero;

always_ff @(posedge clk) 
begin
    if(reset_l) begin
        out_number[127:0] <= 5'd1; 
        fun <= 1'b0;
        count[9:0]  <= 9'd0;
        r <= 5'd0;
        subModuleReady <= 1'b1;
        ready <= 1'b0; 
        secondR <= 5'd0; 
        step <= 2'b00;
        previousR <= 4'd0;  
    end

    else begin

        n1[127:0] <= n[127:0]; 
        n2[127:0] <= n[127:0]<<1; 
        previousR[127:0] <= r[127:0]<<1;
        secondR[127:0] <=  b[127:0] ; 

        case(fun) 
            1'b0: begin
                case(count)
                    9'd0: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[127]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd1: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[126]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd2: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[125]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd3: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[124]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd4: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[123]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd5: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[122]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd6: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[121]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd7: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[120]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd8: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[119]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd9: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[118]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd10: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[117]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd11: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[116]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd12: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[115]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd13: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[114]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd14: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[113]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd15: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[112]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd16: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[111]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd17: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[110]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd18: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[109]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd19: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[108]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd20: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[107]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd21: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[106]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd22: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[105]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd23: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[104]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd24: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[103]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd25: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[102]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd26: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[101]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd27: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[100]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd28: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[99]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd29: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[98]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd30: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[97]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd31: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[96]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd32: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[95]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd33: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[94]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd34: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[93]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd35: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[92]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd36: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[91]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd37: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[90]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd38: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[89]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd39: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[88]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd40: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[87]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd41: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[86]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd42: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[85]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd43: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[84]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd44: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[83]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd45: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[82]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd46: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[81]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd47: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[80]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd48: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[79]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd49: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[78]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd50: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[77]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd51: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[76]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd52: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[75]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd53: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[74]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd54: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[73]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd55: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[72]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd56: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[71]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd57: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[70]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd58: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[69]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd59: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[68]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd60: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[67]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd61: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[66]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd62: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[65]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd63: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[64]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd64: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[63]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd65: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[62]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd66: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[61]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd67: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[60]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd68: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[59]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd69: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[58]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd70: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[57]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd71: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[56]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd72: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[55]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd73: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[54]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd74: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[53]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd75: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[52]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd76: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[51]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd77: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[50]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd78: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[49]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd79: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[48]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd80: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[47]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd81: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[46]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd82: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[45]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd83: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[44]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd84: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[43]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd85: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[42]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd86: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[41]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd87: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[40]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd88: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[39]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd89: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[38]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd90: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[37]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd91: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[36]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd92: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[35]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd93: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[34]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd94: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[33]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd95: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[32]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd96: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[31]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd97: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[30]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd98: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[29]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd99: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[28]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd100: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[27]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd101: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[26]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd102: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[25]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd103: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[24]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd104: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[23]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd105: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[22]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd106: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[21]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd107: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[20]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd108: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[19]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd109: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[18]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd110: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[17]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd111: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[16]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd112: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[15]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd113: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[14]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd114: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[13]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd115: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[12]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd116: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[11]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd117: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[10]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd118: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[9]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd119: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[8]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd120: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[7]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd121: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[6]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd122: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[5]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd123: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[4]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd124: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[3]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd125: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[2]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd126: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[1]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd127: begin 
                        if(subModuleReady && !ready) begin 
                            inputToFunctionR <= a[0]; 
                            fun <= 1'b1; 
                            subModuleReady <= 1'b0; 
                            count[9:0] <= count[9:0] + 9'd1;
                        end 
                    end 
                    9'd128: begin 
                        if(subModuleReady) begin 
                            out_number[127:0] <= r[127:0]; 
                            ready <= 1'b1;
                        end 
                    end 
                    default: begin
                    end
                endcase
            end
            1'b1: begin
                case(step)
                    2'b00: begin
                        case(inputToFunctionR)
                            1'b0: begin
                                r[127:0] <= previousR[127:0]; 
                                step <= 2'b01;                     
                            end
                            1'b1: begin
                                r[127:0] <= (secondR[127:0]+previousR[127:0]);
                                step <= 2'b01;                     
                            end
                        endcase
                    end
                    2'b01: begin
                        nMinusOne[127:0] <= r[127:0] - n1[127:0];
                        nMinusTwo[127:0] <= r[127:0] - n2[127:0];                         
                        step <= 2'b10; 
                    end
                    2'b10:begin
                        if(r[127:0] < n[127:0]) begin
                            fun <= 1'b0;
                            subModuleReady <= 1'b1;
                        end                        
                        else if($signed(nMinusOne[127:0]) >= 0 && nMinusOne[127:0] <= n[127:0]) begin
                            r[127:0] <= nMinusOne[127:0];                     
                            fun <= 1'b0;
                            subModuleReady <= 1'b1;
                        end
                        else begin
                            r[127:0] <= nMinusTwo[127:0];                         
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

