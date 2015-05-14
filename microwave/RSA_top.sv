`include "exponentiate.sv"
/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */
/*
* Code for RSA Box, a hardware implementation of the RSA algorithm.
 */

 module RSA_top(input logic      clk,
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
    logic[127:0] m; 
    // public keys
    logic [127:0] c; 
    logic[127:0] 	n; // p * q
    logic[31:0]	e;
    /* enabler for ALU */
    logic[1:0] functionCall; 
    logic ready;
    logic ready_for_encrypt; 
    logic reset_exponent; 

    logic reset_decrypt; 
    logic[127:0] m1; 
    logic [127:0] d; 
    logic[127:0] decrypt_message; 
    logic ready_for_decrypt; 

         //assign reset_exponent = (reset | reset_exponent_signal);

         exponentiate encryptModule(.reset(reset_exponent), .clk(clk), .m(m), .e(e), .n(n), .c(c), .ready(ready_for_encrypt)) ; 
         exponentiate decryptModule(.reset(reset_decrypt), .clk(clk), .m(m1), .e(d), .n(n), .c(decrypt_message), .ready(ready_for_decrypt)) ; 

         always_ff @(posedge clk) begin
             if (reset || (address == 3'b000 && instrBits == 1'b1)) begin
                 /* reset triggered when clock starts */
                 data_out[31:0] <= 		32'd0; 
                 instrBits[31:0] <= 		32'd0;     // reset typeof(instr)
                 p[63:0] <=					64'd0;
                 q[63:0] <=					64'd0;
                 n[127:0] <=					128'd0;
                 e[31:0] <=					32'd0;
                 m[127:0] <= 128'd0; 
                 ready <= 1'b0; 
                 d[127:0] <= 128'd0; 
                 m1[127:0] <= 128'd0; 
                 functionCall <= 2'b00; 
                 reset_exponent <= 1'b1;
                 reset_decrypt <= 1'b1; 

             end

             /* reading */
             if (chipselect && !write) begin
                 case(functionCall)
                     2'b01: begin
                         case (address)
                             3'b000: data_out[31:0] <= c[31:0];
                             3'b001: data_out[31:0] <= c[63:32];
                             3'b010: data_out[31:0] <= c[95:64];
                             3'b011: data_out[31:0] <= c[127:96]; 
                             3'b100: data_out[0] <= ready_for_encrypt; 
                             default: begin end
                         endcase
                     end
                     2'b10: begin
                         case (address)
                             3'b000: data_out[31:0] <= decrypt_message[31:0];
                             3'b001: data_out[31:0] <= decrypt_message[63:32];
                             3'b010: data_out[31:0] <= decrypt_message[95:64];
                             3'b011: data_out[31:0] <= decrypt_message[127:96]; 
                             3'b100: data_out[1] <= ready_for_decrypt; 
                             default: begin end
                         endcase
                     end
                     2'b11: begin 

                     end
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
                         case(address)
                             3'b001: begin
                                 e[31:0] <= 	data_in[31:0];
                             end
                             default: begin end
                         endcase
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

                     32'd6: begin  
                         /* DECRYPT_BITS */
                         case(address)
                             3'b001: begin
                                 functionCall[1:0] <= 2'b10; 
                                 reset_decrypt <= 1'b1; 
                             end
                             3'b010: begin
                                 functionCall[1:0] <= 2'b10; 
                                 reset_decrypt <= 1'b0; 
                             end
                             default: begin end
                         endcase
                     end

                     32'd7: begin  
                         /* ENCRYPT_BITS */
                         case(address)
                             3'b001: begin
                                 functionCall[1:0] <= 2'b01; 
                                 reset_exponent <= 1'b1; 
                             end
                             3'b010: begin
                                 functionCall[1:0] <= 2'b01; 
                                 reset_exponent <= 1'b0; 
                             end
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
                         case(address)
                             3'b001: begin
                                 outputBits[31:0] <= e[31:0];
                             end
                             default: begin end
                         endcase
                     end
                     32'd10: begin
                         /* STORE_MESSAGE: m*/
                         case (address)
                             3'b001: m[31:0] <= 	data_in[31:0];
                             3'b010: m[63:32] <= 	data_in[31:0];
                             3'b011: m[95:64] <= 	data_in[31:0];
                             3'b100: m[127:96] <=	data_in[31:0];
                             default: begin end
                         endcase
                     end
                     
                     32'd11: begin
                         /* STORE_MESSAGE: m1*/
                         case (address)
                             3'b001: m1[31:0] <= 	data_in[31:0];
                             3'b010: m1[63:32] <= 	data_in[31:0];
                             3'b011: m1[95:64] <= 	data_in[31:0];
                             3'b100: m1[127:96] <=	data_in[31:0];
                             default: begin end
                         endcase
                     end
                    

                     32'd12: begin
                         /* STORE D*/
                         case (address)
                             3'b001: d[31:0] <= 	data_in[31:0];
                             3'b010: d[63:32] <= 	data_in[31:0];
                             3'b011: d[95:64] <= 	data_in[31:0];
                             3'b100: d[127:96] <=	data_in[31:0];
                             default: begin end
                         endcase
                     end

                     default: begin
                     end
                 endcase
             end // end for _writing_
         end // end always_ff
         endmodule





