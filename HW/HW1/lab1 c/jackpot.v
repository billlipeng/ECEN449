/********************************************/
`timescale 1ns / 1ps
//////////////////////////////////////////////
// Create Date:    20:18:12 09/09/2013 
// Module Name:    jackpot 
//////////////////////////////////////////////
module jackpot(
    input [3:0] I_SWITCHES,	// three inputs are I_SWITCHES, I_RESET, I_CLK
    input I_RESET,				// one output is I_LEDS
    input I_CLK,					
    output [3:0] I_LEDS
    );							
	 
	 wire W_CLK_2HZ;				// wire for frequency-modified clock 
	 reg	R_CLK_2HZ;				// register for frequency-modified clock
	 reg 	[29:0] R_CNT;			// register for the counter to modify the clock frequency
	 reg 	[3:0] R_OUT;			// register for output
	 reg 	R_WIN_FLAG;				// register for win flag
	 
	 assign I_LEDS[3:0] = R_OUT[3:0];		// assign register R_OUT to output I_LEDS
	 assign SWITCH_FLAG = I_SWITCHES[0] | I_SWITCHES[1] | I_SWITCHES[2] | I_SWITCHES[3]; // if any switches input is 1, the SWITCH_FLAG is high
	 assign W_CLK_2HZ = R_CLK_2HZ;			// assign register R_CLK_2HZ to wire W_CLK_2HZ
/********************************************/ 
	 always @(posedge	I_CLK or posedge I_RESET)  // the original 100MHz clock is divided by 2.5e7
		begin													// generate the 2Hz clock R_CLK_2HZ
		if(I_RESET)											// if I_RESET input is active, R_CNT back to zero, R_CLK_2HZ becomes low
		 begin
			R_CNT <= 0;
			R_CLK_2HZ <= 0;
		 end
		else
		 begin
			if (R_CNT == 25000000) 						// if R_CNT =  5e7, invert R_CLK_2HZ, R_CNT back to zero
		 	 begin 
				R_CNT <= 0;
				R_CLK_2HZ <= ~R_CLK_2HZ;
			 end
			else
			 begin											// if R_COUNT <= 2.5e7, R_CNT counts up		
				R_CNT <= R_CNT + 1;
			 end
		 end
	 end
/********************************************/	
	 always @(posedge W_CLK_2HZ or posedge I_RESET) // LEDS control part
		begin
			if(I_RESET)											// if I_RESET is active, the output is 0001
				R_OUT <= 1;
			else
			begin
				if(R_WIN_FLAG == 1)							// if R_WIN_FLAG is active, output is 1111
					R_OUT <= 4'b1111;
				else												// if I_RESET=0 and R_WIN_FLAG=0, R_OUT shift one by one
					R_OUT[3:0] <= {R_OUT[0], R_OUT[3:1]};
			end
		end
/********************************************/		
	 always @(posedge SWITCH_FLAG or posedge I_RESET) //Comparator part
		begin
			if(I_RESET)										// if I_RESET is active, win flag is 0
				R_WIN_FLAG <= 0;
			else if (I_LEDS == I_SWITCHES)			// if I_LEDS = I_SWITCHES, win flag is active
				R_WIN_FLAG <= 1;			
			else 												// else win flag remain
				R_WIN_FLAG <= R_WIN_FLAG;
		end
		
endmodule
/********************************************/