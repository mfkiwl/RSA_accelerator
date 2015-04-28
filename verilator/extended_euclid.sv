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




// igcdex.v, (c) Sept 08, 2005, Ron Dotson
// Use Euclid's extendend algorithm to calculate:
// g=GCD(p1,p2), and s and t such that: g= s*p1 + t*p2

`define L 32  // Bus Width
`define K 31  // Bus Width-1

module IGCDEX(reset,clock,p1,p2,  s,t,g,finished);
parameter N= `L; // Bus Width
parameter S0=0,S1=1,S2=2,S3=3, S4=4,S5=5,S6=6,S7=7;
input       reset, clock;
input       [N-1:0] p1, p2;
output reg  [N-1:0] s, t, g;    // "g" is GCD, and t and s are inverses
output reg  finished;

reg         resetDivider, resetMul, swappedInputs;
reg         [N-1:0] c1, a2,b2,c2, a3,b3,c3; // multiplier inputs
reg         [N-1:0] b,u,v;
reg         [2:0] state;

wire        dividerFinished, mulFinished1, mulFinished2, mulFinished3;
wire        [2*N-1:0] m1, m2, m3;  // multiplier outputs
wire        [N-1:0] q;

DIVIDER    divider (resetDivider,clock,g,b,  q,,dividerFinished); // q= iquo(g/b)
MULTIPLIER mul1    (resetMul,clock,q,b,c1,   m1,mulFinished1); // m1= (a1*b1+c1)
MULTIPLIER mul2    (resetMul,clock,q,u,c2,   m2,mulFinished2); // m2= (a2*b2+c2)
MULTIPLIER mul3    (resetMul,clock,q,v,c3,   m3,mulFinished3); // m3= (a3*b3+c3)

always @(posedge clock)
begin
if (reset==1)
    begin
    finished<=0;
    resetDivider<=0;   // ensure these start off low
    resetMul<=0;
    g<= p1[N-1]? -p1: p1;   // g= abs(p1)
    b<= p2[N-1]? -p2: p2;   // b= abs(p2)
    t<= p1[N-1]?  -1:  1;   // t= sign(p1)
    s<= 0;
    u<= 0;
    v<= p2[N-1]?  -1:  1;   // v= sign(p2)
    resetMul<= 0;
    resetDivider<= 0;
    state<=S0;
    //$display("IGCDEX 10: RESET p1=%X, p2=%X\n", p1,p2);
    end
else
    begin
    case (state)
        S0: begin
            //$display("IGCDEX 20: g=%d, b=%d, t=%X, v=%d\n", g,b,t,v);
            if (g < b)
                begin
                g<= b;    // swap operands so that g>=b
                b<= g;
                t<= v;
                v<= t;
                end
            state<= S1;
            end

        S1: begin          // while b<>0
            if (|b)     // if b!=0 continue loop, else exit
                begin
                resetDivider<= 1;  // enable divider, q= iquo(g/b)
                state<= S2;
                end
            else
                state<= S4;  // finished
            end

        S2: begin
            resetDivider<= 0;
            if (dividerFinished)
                begin
                //$display("IGCDEX 30: q=%X, g=%d, b=%d (q= g/b)\n", q,g,b);
                c1<= -g;
                c2<= -t;
                c3<= -s;
                resetMul<= 1;  // enable multipliers
                state<= S3;
                end
            end

        S3: begin
            resetMul<= 0;
            if (mulFinished1 & mulFinished2 & mulFinished3)
                begin
                if (m1[N]!=m1[N-1] | m2[N]!=m2[N-1] | m3[N]!=m3[N-1])
                    begin          // overflow
                    //$display("\nIGCDEX xx: OVERFLOW!\n");
                    //$display("\tm1=%X, m2=%X, m3=%X\n", m1, m2, m3);
                    //$display("\nIGCDEX Inputs: p1=%X, p2=%X\n", p1,p2);
                    $stop();
                    end
                g<= b;
                b<= -m1[N-1:0];
                t<= u;
                u<= -m2[N-1:0]; // -m2 = x
                s<= v;
                v<= -m3[N-1:0];
                state<= S1;  // end of while loop
                //$display("IGCDEX 30: Looping Back; q=%d, g=%d, b=%d\n\n\n", q,g,b);
                end
            end

        S4: begin
            finished<= 1;
            end
    endcase
    end
end
endmodule                  // IGCDEX
