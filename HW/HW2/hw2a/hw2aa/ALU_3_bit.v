`timescale 1ns / 1ps
// Design Name: Homework2_1
// Module Name: ALU_3_bit    
// Description: This verilog module implement a 3 bits ALU
// When mode = 0. Module do two 3-bit-operands unsigned addition.
// When mode = 1. Module do two 3-bit-operands signed addition.

module ALU_3_bit (clock,operand1,operand2,mode,result,overflow);
	 input        clock;
	 input  [2:0] operand1;
    input  [2:0] operand2;
    input        mode;
    output [2:0] result;
    output       overflow;
	 reg    [3:0] r_temp = 0;
	 reg    [2:0] r_two_bit_sum = 0; 
	 reg          r_overflow = 0;
	 
	 assign overflow = r_overflow;
	 assign result = r_temp[2:0];

	 
	 always @(posedge clock)
	 begin
	 // unsigned addition
		if(~mode)
			begin
				r_temp = operand1 + operand2;
				if(r_temp[3])
					r_overflow = 1;
				else
					r_overflow = 0;
			end
	 // signed addition
		else
			begin
				r_temp = operand1 + operand2;
				r_two_bit_sum = operand1[1:0] + operand2[1:0]; //check the second highest bit carry in 
				//when highest one of the two highest bits carry out, overflow is true
				if((r_temp[3]==0 && r_two_bit_sum[2]==1)||(r_temp[3]==1 && r_two_bit_sum[2]==0)) 
					r_overflow = 1;
				else
					r_overflow = 0;
			end				
	 end
		
endmodule
