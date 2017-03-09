`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:37:01 09/05/2013 
// Design Name: 
// Module Name:    led_count 
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
module led_count(
    input RESET,
    input [1:0] I_SWITCHES,
    input CLOCK,
    output [3:0] O_LEDS
    );
/************************************/	 
	 
	 wire W_CLK_1HZ;
	 reg  R_CLK_1HZ;
	 reg  [29:0] R_COUNT;
	 reg  [3:0] R_OUT;
	 assign O_LEDS[3:0] = R_OUT[3:0];
	 assign W_CLK_1HZ = R_CLK_1HZ;
	 	 
	 always @(posedge	CLOCK) 
		begin
		if (R_COUNT == 50000000) 
			begin 
			R_COUNT <= 0;
			R_CLK_1HZ <= !R_CLK_1HZ;
			end
		else
			begin
			R_COUNT <= R_COUNT + 1;
			R_CLK_1HZ <= R_CLK_1HZ;
			end
	 end
	
	 always @(posedge W_CLK_1HZ or posedge RESET) 
		begin
			if(RESET)
				R_OUT <= 0;
			else if(I_SWITCHES[1])
				R_OUT <= R_OUT - 1;
			else if(I_SWITCHES[0])
				R_OUT <= R_OUT + 1;
		end
		
endmodule
