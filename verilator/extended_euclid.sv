module inverse(
        input logic[31:0] e,  
        input logic[31:0] phi_n,
        output logic[31:0] d, 
        output logic d_valid
    );

    assign d = 31'd0;
    assign d_valid = 1'b0;
    logic [31:0] new_d = 31'd1;

    assign r = phi_n;
    logic [31:0] new_r = e;

    logic [3:0] state = 4'd1;

    always_ff @(posedge clk) begin

        if(new_r == 32'd0) begin
            state <= 4'd0;
        end

        case(state) 
            4'd0: 
                // finish state
                if(d < 0 && !d_valid) begin
                    d <= d + phi_n;
                    d_valid <= 1'b1;
                end
                /* exit module */
            4'd1:
                // perform step
                quotient <= r / new_r;
                temp <= d;
                d <= new_d; 
                new_d <= temp - quotient * new_d;
                temp <= r;
                r <= new_r;
                new_r <= temp - quotient * new_r;

                if(new_r == 32'd0) begin
                    state <= 4'd0; // done
                end

                // go back with state = 1 again

    end

endmodule
