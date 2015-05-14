`include "incrementA.sv"

module exponentiate( input logic reset, clk,
    input logic[127:0] m,
    input logic[31:0] e,
    input logic[127:0] n,
    output logic[127:0] c,
    output logic ready
); 

logic[31:0] counter;
logic[127:0] base;
logic mult_ready;
logic square_ready;
logic[31:0] BIG_E;
logic fun;
logic[127:0] squared;
logic[127:0] product;
logic mult_reset;
logic square_reset;
logic new_mult;
logic new_square;
logic[127:0] temp;
logic[31:0] exp;

incrementA multiply(
    .reset      (mult_reset),
    .clk,
    .a          (base),
    .b          (c),
    .outputAnswer (product),
    .ready      (mult_ready),
    .n
); 

incrementA square(
    .reset      (square_reset),
    .clk,
    .a          (base),
    .b          (base),
    .outputAnswer (squared),
    .ready      (square_ready),
    .n
);

assign mult_reset = (reset | new_mult);
assign square_reset = (reset | new_square);

always_ff @(posedge clk)
begin
    if(reset)
    begin
        counter <= 32'd0;
        BIG_E <= 32'd65537;
        ready <= 0;
        c <= 32'd1;
        base <= m;
        fun <= 1'b0;
        new_mult <= 0;
        new_square <= 0;
        exp <= e;
    end
    else if(exp > 32'b0) begin
        case(fun)
            1'b0: begin
                new_mult <= 1;
                new_square <= 1;
                if(!mult_ready & !square_ready)
                    fun <= 1'b1;
            end
            1'b1: begin
                new_mult <= 0;
                new_square <= 0;
                if(mult_ready & square_ready) begin
                    if(exp[0])
                        c <= product;
                    base <= squared;
                    fun <= 1'b0;
                    exp <= exp >> 1;
                end
            end
        endcase
    end
    else 
        ready <= 1;
end
endmodule
