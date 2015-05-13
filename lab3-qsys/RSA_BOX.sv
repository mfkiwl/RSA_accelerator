/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */
/*
* Code for RSA Box, a hardware implementation of the RSA algorithm.
 */

 module RSA_BOX(input logic      clk,
     input logic             reset,
     input logic             write,
     input                   chipselect,
     input logic[31:0]       data_in, // the current 32 bit input
     input logic[2:0]        address, // which 32 bit segment of each structure to write into
     output logic[31:0]      data_out 
//		  output	logic				  is_ready
    ); 

    /* instruction bits (can pick from instructions defined in user-level/instructions.h) */
    logic[31:0] instrBits;
    /* structures/registers */
    logic[127:0] outputBits; 
    // private keys
    logic[63:0] p;
    logic[63:0] q;

    // public keys
    logic[127:0] 	n; // p * q
    logic[31:0]	e;
    /* enabler for ALU */
    logic[1:0] functionCall; 
    // ALU alu_input( .*  );

    always_ff @(posedge clk) begin
        if (reset || (address == 3'b000 && instrBits == 1'b1)) begin
            /* reset triggered when clock starts */
            data_out[31:0] <= 		32'd0; 
            instrBits[31:0] <= 		32'd0;     // reset typeof(instr)
            p[63:0] <=					64'd0;
            q[63:0] <=					64'd0;
            n[127:0] <=					128'd0;
            e[31:0] <=					32'd0;
            functionCall[1:0] <= 	2'd0; 
        end

        /* reading */
        if (chipselect && !write) begin
            case (address)
                3'b000: data_out[31:0] <= outputBits[31:0];
                3'b001: data_out[31:0] <= outputBits[63:32];
                3'b010: data_out[31:0] <= outputBits[95:64];
                3'b011: data_out[31:0] <= outputBits[127:96]; 
                default: begin end
            endcase
        end

        /* writing */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
        else if (chipselect && write) begin
            /* determine what kind of instruction this is */
            if (address == 3'b000) begin
                instrBits[31:0] <= data_in[31:0];
            end

            /****** INSTRUCTIONS: check which each instruction *******/ 
            /* STORE_PUBLIC_KEY_1: n */
            case(instrBits)
                32'd2: begin
                    case(address)
                        3'b001: n[31:0] <= 	data_in[31:0];
                        3'b010: n[63:32] <= 	data_in[31:0];
                        3'b011: n[95:64] <= 	data_in[31:0];
                        3'b100: n[127:96] <= data_in[31:0];
                        default: begin end
                    endcase
                end
                32'd3: begin  
                    /* STORE_PUBLIC_KEY_2: e */
                    e[31:0] <= 	data_in[31:0];
                    functionCall <= 2'b10; // all data recvd
                end
                32'd4: begin
                    /* STORE_PRIVATE_KEY_1: p */
                    case(address)
                        3'b001: p[31:0] <= 	data_in[31:0];
                        3'b010: p[63:32] <= 	data_in[31:0];
                        default: begin end
                    endcase
                end
                32'd5: begin
                    /* STORE_PRIVATE_KEY_2: q */
                    case(address)
                        3'b001: q[31:0] <= data_in[31:0];
                        3'b010: q[63:32] <= data_in[31:0];
                        default: begin end
                    endcase
                end
                32'd8: begin
                    /* READ_PUBLIC_KEY_1: n */
                    case (address)
                        3'b001: outputBits[31:0] <= 	n[31:0];
                        3'b010: outputBits[63:32] <= 	n[63:32];
                        3'b011: outputBits[95:64] <= 	n[95:64];
                        3'b100: outputBits[127:96] <=	n[127:96];
                        default: begin end
                    endcase
                end
                32'd9: begin
                    /* READ_PUBLIC_KEY_2: e */
                    outputBits[31:0] <= e[31:0];
                end
                default: begin
                end
            endcase
        end // end for _writing_
    end // end always_ff
    endmodule
