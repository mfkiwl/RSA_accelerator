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
        input logic[1:0]    	address,
        output logic [31:0]  	bitsOut1 
    ); 

    logic[127:0] inputBits; 
    logic[127:0] outputBits;
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
		      2'b00: inputBits[31:0] <= data1[31:0];
            2'b01: inputBits[63:32] <= data1[31:0];
            2'b10: inputBits[95:64] <= data1[31:0];
            2'b11: 
            begin
                inputBits[127:96] <= data1[31:0];
                multiply <= 1'b1; 
            end
        endcase
   
	 // if reading
    else if (chipselect && !write)
        case (address)
            // write selected 32-bit chunk of outputBits to the output wire
            2'b00: bitsOut1[31:0] <= outputBits[31:0];
            2'b01: bitsOut1[31:0] <= outputBits[63:32];
            2'b10: bitsOut1[31:0] <= outputBits[95:64];
            2'b11: bitsOut1[31:0] <= outputBits[127:96]; 
        endcase
endmodule

module multiply_karatsuba(input logic clk, 
          input logic[127:0] inputBits,
          input multiply,
          output logic[127:0] outputBits);
     
   always_comb
    if(multiply)
     outputBits = ( (inputBits[31:0] + inputBits[63:32] )* (inputBits[127:96] + inputBits[95:64]) ) ; 
    else
  			outputBits = 128'd0; 
endmodule
