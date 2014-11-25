`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:44:10 09/30/2013 
// Design Name: 
// Module Name:    test1 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module test1(clock,operand1,operand2,mode,result,overflow);
	 input clock;
	 input [2:0] operand1;
    input [2:0] operand2;
    input mode;
    output [2:0] result;
    output overflow;
	 reg [3:0] temp = 0;
	 reg [2:0] two_bit_sum = 0;
	 reg r_overflow = 0;
	 assign overflow = r_overflow;
	 assign result = temp[2:0];

	 
	 always @(posedge clock)
	 begin
		if(~mode)
			begin
				temp = operand1 + operand2;
				if(temp[3])
					r_overflow = 1;
				else
					r_overflow = 0;
			end
		else
			begin
				temp = operand1 + operand2;
				two_bit_sum = operand1[1:0] + operand2[1:0]; 
				if((temp[3]==0 && two_bit_sum[2]==1)||(temp[3]==1 && two_bit_sum[2]==0))
					r_overflow = 1;
				else
					r_overflow = 0;
			end				
	 end
		
endmodule
