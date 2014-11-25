`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:56:08 09/30/2013 
// Design Name: 
// Module Name:    stat_machine 
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
module stat_machine(
	 input reset,
    input A,
    output Y
    );
	 
	 reg r_Y;
	 reg [1:0] S = 2'b00;
	 assign Y = r_Y;
	 always @(reset or A)
	 begin
		if(reset)
		begin
			S = 2'b00;
		end
		else
		begin
			case (S)
				2'b00:
				begin
					if(A)
					begin
						r_Y = 1;
						S = 2'b01;
					end
					else
						begin
						r_Y = 0;
						S = 2'b00;
					end
				end
				
				2'b01:
				begin
					if(A)
					begin
						r_Y = 0;
						S = 2'b10;
					end
					else
					begin
						r_Y = 1;
						S = 2'b01;
					end
				end
				
				2'b10:
				begin
					if(~A)
					begin
						r_Y = 0;
						S = 2'b00;
					end
				end
			endcase	
		end
	 end

endmodule
