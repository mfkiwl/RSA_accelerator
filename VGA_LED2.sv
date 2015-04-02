/*
 * Code for RSA Box, a hardware implementation of the RSA algorithm.
 *
 * Started from Stephen A. Edwards' VGA_LED code for CSEE 4840 spring 2015 at Columbia University.
 */

module VGA_LED(input logic		clk,
		  input logic       		reset,
        input logic [31:0]   	data1,
        input logic       		write,
        input         			chipselect,
        input logic[2:0]    	address,
        output logic [31:0]  	bitsOut1 
    ); 

    logic[127:0] inputBits; 
    logic[159:0] outputBits;
    logic multiply;
   
    multiply_karatsuba mk( .*  ); 
    always_ff @(posedge clk)
        if (reset) begin
            bitsOut1 <= 32'd0; 
		      inputBits <= 128'd0;
            multiply <= 1'b0; 
        end 
   
    // if writing
    else if (chipselect && write) 
        case (address)
		      3'b000: inputBits[31:0] <= data1[31:0];
            3'b001: inputBits[63:32] <= data1[31:0];
            3'b010: inputBits[95:64] <= data1[31:0];
            3'b011: 
            begin
                inputBits[127:96] <= data1[31:0];
                multiply <= 1'b1; 
            end
        endcase
   
	 // if reading
    else if (chipselect && !write)
        case (address)
            // write selected 32-bit chunk of outputBits to the output wire
            3'b000: bitsOut1[31:0] <= outputBits[31:0];
            3'b001: bitsOut1[31:0] <= outputBits[63:32];
            3'b010: bitsOut1[31:0] <= outputBits[95:64];
            3'b011: bitsOut1[31:0] <= outputBits[127:96]; 
				3'b100: bitsOut1[31:0] <= 32'd65537;
        endcase
endmodule

module multiply_karatsuba(input logic clk, 
          input logic[127:0] inputBits,
          input multiply,
          output logic[159:0] outputBits);
   
	
   always_ff @(posedge clk)
    if(multiply)
      outputBits[127:0] <= ( inputBits[63:0] * inputBits[127:64] ) ; 

endmodule
