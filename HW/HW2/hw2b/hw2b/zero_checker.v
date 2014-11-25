`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:59:57 09/30/2013 
// Design Name: 
// Module Name:    zero_checker 
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
module zero_checker(
    input [11:0] data,
    input data_ready,
    output result
    );
	 reg r_result = 0;
	 integer count_1 = 0;
	 integer i;
	 assign result = r_result;
	 
	 always @(data_ready or data)
	 begin
		if(data_ready)
		begin
			for(i=0;i<11;i=i+1)
			begin
				if(data[i])
					count_1 = count_1 + 1;
			end
			if(count_1 > 6)
				r_result = 1;
		end
			
	 else
		r_result = 0;
	 
	 end
	 
endmodule
