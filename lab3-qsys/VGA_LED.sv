/*
 * Code for RSA Box, a hardware implementation of the RSA algorithm.
 */

module VGA_LED(input logic		clk,
		  input logic       		reset,
        input logic [31:0]   	data1,
        input logic       		write,
        input         			chipselect,
        input logic[2:0]    	address,
        output logic [31:0]  	bitsOut1 
    ); 

	 /* instruction bits (key, encrypt, or DECRYPT) */
	 logic[31:0] instrBits;
	 
    logic[127:0] keyBits; 
	 logic[159:0] encryptBits;
	 logic[383:0] decryptBits;
    logic[127:0] outputBits; 
    logic[1:0] functionCall; 
	 
	 logic[1:0] countOfAddr; 
	 
	 
    ALU alu_input( .*  );
	 //M_mult multiplication( .* );
	 //M_mod_mult modular_exponentiation ( .* ); 

    always_ff @(posedge clk)
        if (reset) begin
            bitsOut1 <= 32'd0; 
				// initialize all to-be-read-in bits to 0
				instrBits <= 32'd0;
				
				keyBits <= 128'd0;
				encryptBits <= 160'd0;
				decryptBits <= 384'd0;
            functionCall <= 2'd0; 
				countOfAddr <= 2'd0; 
				// result <= 127'd1;
        end 
   																																																																																																																																																																																																																																																																																																																																																																																																																																																																										
		 // if writing																																																																																																																							
		 else if (chipselect && write) 	 
		 begin
		 
				/*
					addr0 to addr3 corresponds to first 128 bits
					addr0 to addr3 + addr4 correspond to first 160 bits (ENCRYPT)
					addr0 to addr11 correspond to first 3 * 128 bits (DECRYPT)
				*/
		 
				// change eventually to addr == 0
			  if (address == 3'b000) 
			    begin
			      // we have received an instruction specifier
						instrBits[31:0] <= data1[31:0];
			    end
			  
			  if(instrBits[1:0] == 2'b01) 
			    begin
					// we have [keys instruction] 
					case(address)
						3'b001: keyBits[31:0] <= data1[31:0];
						3'b010: keyBits[63:32] <= data1[31:0];
						3'b011: keyBits[95:64] <= data1[31:0];
						3'b100:
							begin
									keyBits[127:96] <= data1[31:0];
									functionCall <= 2'b01;
							end	
					endcase
					
			    end
			  
			  
			  
			  else if(instrBits[1:0] == 2'b10) 
			  begin
					// we have [encryption instruction]
					case(address)
					3'b001: encryptBits[31:0] <= data1[31:0];
					3'b010: encryptBits[63:32] <= data1[31:0];
					3'b011: encryptBits[95:64] <= data1[31:0];
					3'b100: encryptBits[127:96] <= data1[31:0];
					3'b101:
						begin
								encryptBits[159:128] <= data1[31:0];
								functionCall <= 2'b10;
						end
					endcase
			  end
				 
			  else if(instrBits[1:0] == 2'b11) 
			  begin
					// we have [decryption instruction]
					case(instrBits[4:2])
					
					2'b00:
						begin
							case(address)
								3'b001: decryptBits[31:0] <= data1[31:0];
								3'b010: decryptBits[63:32] <= data1[31:0];
								3'b011: decryptBits[95:64] <= data1[31:0];
								3'b100: decryptBits[127:96] <= data1[31:0];
							endcase
						end
					
					2'b01:
						begin
							case(address)
								3'b001: decryptBits[159:128] <= data1[31:0];
								3'b010: decryptBits[191:160] <= data1[31:0];
								3'b011: decryptBits[223:192] <= data1[31:0];
								3'b100: decryptBits[255:224] <= data1[31:0];
							endcase
						end
					
					2'b10:
						begin
							case(address)
								3'b001: decryptBits[287:256] <= data1[31:0];
								3'b010: decryptBits[319:288] <= data1[31:0];
								3'b011: decryptBits[351:320] <= data1[31:0];
								3'b100:
								begin
										  decryptBits[383:352] <= data1[31:0];
										  functionCall <= 2'b11;
								end
							endcase
				
						end
						
						
					endcase
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



module ALU(
			 input logic clk, 
			 input logic reset,
          input logic[127:0] keyBits,
          input logic [1:0] functionCall,
			 input logic[383:0] decryptBits,
			 input logic[159:0] encryptBits,
			 output logic [127:0] outputBits
			 );
   
	logic[1:0] state; 
	logic[4:0] r, a, b,n; 
	logic[4:0] count; 
	logic step1, step2, step3; 
   
	always_ff @(posedge clk) begin
		if(reset)
			begin
				state<= 2'b0; 
				r<=5'd0; 
				count <= 5'd0;
				step1 <= 1'b1; 
				step2 <= 1'b0; 
				step3 <= 1'b0;
			end
    case(functionCall)
      2'b01: 
			outputBits[127:0] <= ( keyBits[63:0] * keyBits[127:64] ) ;
		2'b10:  
				case(state)
						//state 0 is idle
						1'b0:
							begin
								r<= 5'd0; 
								state<=1'b1;
								count <= 5'd0;
								step1 <= 1'b1; 
								step2 <= 1'b0; 
								step3 <= 1'b0; 
								a[4:0] <= encryptBits[4:0]; 
								b[4:0] <= encryptBits[36:32]; 
								n[4:0] <= encryptBits[66:64]; 
								//outputBits[4:0] <= 5'd0; 
							end
						1'b1:
							
								case(count)
									5'd5: begin
										outputBits[4:0] <= r[4:0];
									   state <= 1'b0; 	
									end
									
									5'd0: begin
										
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[4]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
											end
										
										else if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
												end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
											end
										
										else begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
												end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
											end
											
										end
									
									5'd1: begin
										 if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[3]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
											end
										
										else if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
												end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
											end
										
										else  begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
												end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
											end
										end
									
									5'd2: begin
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[2]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
											end
										
										else if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
												end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
											end
										
										else  begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
											end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
											end
										end
									
									5'd3: begin
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[1]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
											end
										
										else if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
											end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
											end
										
										else begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
												end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
											end
										end
									
									5'd4: begin
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[0]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
											end
										
										else if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
												end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
											end
										
										else  begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
												end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
											end
										end
									endcase
						endcase
				2'b11:
						outputBits[127:0] <= 2'd2; 
			endcase
		
	end
endmodule

/*
module multiplication(input logic clk,
										input logic reset,
										input logic [1:0] functionCall, 
										input logic [127:0] keyBits, 
										output logic[127:0] outputBits); 
										
										
		
   always_ff @(posedge clk)
		if(functionCall == 2'b01 )
			outputBits[127:0] <= ( keyBits[63:0] * keyBits[127:64] ) ;

										
endmodule
//2'b01: outputBits[127:0] <= ( keyBits[63:0] * keyBits[127:64] ) ;
module modular_exponentiation(input logic clk,
										input logic reset,
										input logic [1:0] functionCall, 
										input logic [383:0] decryptBits, 
										output logic[127:0] outputBits); 
			
			
			logic[1:0] state; 
			logic[4:0] r, a, b; 
			logic[4:0] count; 
			logic step1, step2, step3; 
			always_ff @(posedge clk)
			begin
				//done<=1'b0; 
				if(reset)begin
					state<= 2'b0; 
					r<=5'd0; 
					count <= 5'd0;
					step1 = 1'b1; 
					step2 = 1'b0; 
					step3 = 1'b0;
				end
				
				else if (functionCall == 2'b10) begin 
					case(state)
						//state 0 is idle
						1'b0:
							begin
								r<= 5'd0; 
								state<=1'b1;
								count <= 5'd0;
								step1 <= 1'b1; 
								step2 <= 1'b0; 
								step3 <= 1'b0; 
								a <= decryptBits[4:0]; 
								b <= decryptBits[36:32]; 
								n <= decryptBits[66:64]; 
							end
						1'b1:
							begin
								case(count)
									5'd5: begin
										outputBits[4:0] <= r[4:0]; 
									end
									
									5'd0: begin
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[4]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
										end
										
										if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
											end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
										end
										
										if(step3) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
											end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
										end
									end
									
									5'd1: begin
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[3]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
										end
										
										if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
											end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
										end
										
										if(step3) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
											end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
										end
									end
									
									5'd2: begin
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[2]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
										end
										
										if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
											end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
										end
										
										if(step3) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
											end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
										end
									end
									
									5'd3: begin
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[1]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
										end
										
										if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
											end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
										end
										
										if(step3) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
											end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
										end
									end
									
									5'd4: begin
										if(step1) begin
											r[4:0]<= ((r[4:0]<<1) + (a[0]*b[4:0])); 
											step1 <=1'b0; 
											step2 <= 1'b1; 
										end
										
										if(step2) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]-n[4:0]); 
											end
											step2 <= 1'b0; 
											step3 <= 1'b1; 
										end
										
										if(step3) begin
											if(r[4:0] >= n[4:0]) begin
												r[4:0] <= (r[4:0]- n[4:0]); 
											end
											step3 <= 1'b0; 
											step1 <= 1'b1; 
											count <= (count+1); 
										end
									end
									

								endcase
							end
					
					endcase
							
				end
							
				
			end
endmodule 

*/