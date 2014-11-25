`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:18:12 09/09/2013 
// Design Name: 
// Module Name:    jackpot 
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
module jackpot(
    input [3:0] I_SWITCHES,
    input I_RESET,
    input I_CLK,
    output [3:0] I_LEDS
    );
	 
	 wire W_CLK_1HZ;
	 reg	R_CLK_1HZ;
	 reg 	[29:0] R_CNT;
	 reg 	[3:0] R_OUT;
	 reg 	R_WIN_FLAG;
	 
	 assign I_LEDS[3:0] = R_OUT[3:0];
	 assign SWITCH_FLAG = I_SWITCHES[0] | I_SWITCHES[1] | I_SWITCHES[2] | I_SWITCHES[3];
	 assign W_CLK_1HZ = R_CLK_1HZ;
	 
	 always @(posedge	I_CLK or posedge I_RESET) 
		begin
		if(I_RESET)
		 begin
			R_CNT <= 0;
			R_CLK_1HZ <= 0;
		 end
		else
		 begin
			if (R_CNT == 25000000) 
		 	 begin 
				R_CNT <= 0;
				R_CLK_1HZ <= ~R_CLK_1HZ;
			 end
			else
			 begin
				R_CNT <= R_CNT + 1;
			 end
		 end
	 end
	
	 always @(posedge W_CLK_1HZ or posedge I_RESET) 
		begin
			if(I_RESET)
				R_OUT <= 1;
			else
			begin
				if(R_WIN_FLAG == 1)
					R_OUT <= 4'b1111;
				else
					R_OUT[3:0] <= {R_OUT[0], R_OUT[3:1]};
			end
		end
		
	 always @(posedge SWITCH_FLAG or posedge I_RESET)
		begin
			if(I_RESET)
				R_WIN_FLAG <= 0;
			else if (I_LEDS == I_SWITCHES)
				R_WIN_FLAG <= 1;			
			else 
				R_WIN_FLAG <= R_WIN_FLAG;
		end
		
endmodule
