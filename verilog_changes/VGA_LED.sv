/*
 * Code for RSA Box, a hardware implementation of the RSA algorithm.
 */

module VGA_LED(input logic		clk,
		  input logic       		reset,
        input logic [31:0]   	data1,
        input logic       		write,
        input         			chipselect,
        input logic[3:0]    	address,
        output logic [31:0]  	bitsOut1 
    ); 

	 logic[31:0] instrBits; // instruction bits
	 
    logic[127:0] keyBits; 
	 logic[159:0] encryptBits;
	 logic[383:0] decryptBits;
    logic[127:0] outputBits; 
	 
    logic[1:0] functionCall; 
	 
    ALU alu_input( .*  );
	 
    always_ff @(posedge clk)
        if (reset) begin
            bitsOut1 <= 32'd0; 
		      
				// initialize all to-be-read-in bits to 0
				instrBits <= 32'd0;
				
				keyBits <= 128'd0;
				encryptBits <= 160'd0;
				decryptBits <= 384'd0;
            functionCall <= 2'd0; 
				// result <= 127'd1;
        end 
   																																																																																																																																																																																																																																																																																																																																																																																																																																																																										
		 // if writing																																																																																																																							
		 else if (chipselect && write) begin
		 
				/*
					addr0 to addr3 corresponds to first 128 bits
					addr0 to addr3 + addr4 correspond to first 160 bits (ENCRYPT)
					addr0 to addr11 correspond to first 3 * 128 bits (DECRYPT)
				*/
		 
				// change eventually to addr == 0
			  if (address == 4'b0000) begin
			      // we have received an instruction specifier
					instrBits[31:0] <= data1[31:0];
					end
			  else if(instrBits == 32'd1) begin
					// we have [keys instruction] 
					if(address == 4'b0001)
						keyBits[31:0] <= data1[31:0];
					else if(address == 4'b0010) // should go from 0 to 2, not 1 to 3 & make case (?)
						keyBits[63:32] <= data1[31:0];
					else if(address == 4'b0011)
						keyBits[95:64] <= data1[31:0];
					else if(address == 4'b0100)
						keyBits[127:96] <= data1[31:0];
						functionCall <= 2'd1; 
					end
			  else if(instrBits == 32'd2) begin
					// we have [encryption instruction]
					if(address == 4'b0001)
						encryptBits[31:0] <= data1[31:0];
					else if(address == 4'b0010)
						encryptBits[63:32] <= data1[31:0];
					else if(address == 4'b0011)
						encryptBits[95:64] <= data1[31:0];
					else if(address == 4'b0100)
						encryptBits[127:96] <= data1[31:0];
					else if(address == 4'b0101) begin
						encryptBits[159:128] <= data1[31:0];
						functionCall <= 2'd2;
						end
					end
			  else if(instrBits == 32'd3) begin
					// we have [decryption instruction]
					if(address == 4'b0001)
						decryptBits[31:0] <= data1[31:0];
					else if(address == 4'b0010)
						decryptBits[63:32] <= data1[31:0];
					else if(address == 4'b0011)
						decryptBits[95:64] <= data1[31:0];
					else if(address == 4'b0100)
						decryptBits[127:96] <= data1[31:0];
					else if(address == 4'b0101)
						decryptBits[159:128] <= data1[31:0];
					else if(address == 4'b0110)
						decryptBits[191:160] <= data1[31:0];
					else if(address == 4'b0111)
						decryptBits[223:192] <= data1[31:0];
					else if(address == 4'b1000)
						decryptBits[255:224] <= data1[31:0];
					else if(address == 4'b1001)
						decryptBits[287:256] <= data1[31:0];
					else if(address == 4'b1010)
						decryptBits[319:288] <= data1[31:0];
					else if(address == 4'b1011)
						decryptBits[351:320] <= data1[31:0];
					else if(address == 4'b1100) begin
						decryptBits[383:352] <= data1[31:0];
						functionCall <= 2'd3;
						end
					end
		 end
		 // if reading
		 else if (chipselect && !write)
			  case (address)
					// write selected 32-bit chunk of outputBits to the output wire
					4'b0000: bitsOut1[31:0] <= outputBits[31:0];
					4'b0001: bitsOut1[31:0] <= outputBits[63:32];
					4'b0010: bitsOut1[31:0] <= outputBits[95:64];
					4'b0011: bitsOut1[31:0] <= outputBits[127:96]; 
					// e value: 65537;
			  endcase
endmodule

/*
module modular_exponentiation(input logic clk,
										input logic[127:0] message, 
										input logic[127:0] exponent, 
										input logic[127:0] n
										output logic[127:0] result);
										
		  
        always_ff @(posedge clk)
		      if(exponent > 0) begin
					if(exponent[0:0] == 1) begin
						result <= (result * base) % modulus; 
					end
					exponent <= exponent >> 1;
					base <= (base * base) % modulus;
				end

endmodule 
*/


module ALU(
			 input logic clk, 
          input logic[127:0] keyBits,
          input[1:0] functionCall,
          output logic[127:0] outputBits,
			 input logic[383:0] decryptBits,
			 input logic[159:0] encryptBits
			 );
   
	
   always_ff @(posedge clk)
    case(functionCall)
      2'b01: outputBits[127:0] <= ( keyBits[63:0] * keyBits[127:64] ) ;
		2'b10: outputBits[127:0] <= 127'd1; 
		2'b11: outputBits[127:0] <= 127'd2; 
	endcase

endmodule
