`timescale 1ns / 1ps
/********************************************/
// Create Date:    12:37:01 09/05/2013 
// Module Name:    led_count 
/********************************************/
module led_count(
    input RESET,
    input [1:0] I_SWITCHES,
    input CLOCK,
    output [3:0] O_LEDS
    );
/********************************************/	 	 
	 wire W_CLK_1HZ; 							// 1Hz clock
	 reg  R_CLK_1HZ;							// register for 1Hz clock
	 reg  [29:0] R_COUNT; 					// counter to generate 1 Hz clock
	 reg  [3:0] R_OUT;						// output data register
	 assign O_LEDS[3:0] = R_OUT[3:0];	// assign the output register to the leds
	 assign W_CLK_1HZ = R_CLK_1HZ;		// assign the clock register to the clock wire
/********************************************/	 	 
	 always @(posedge	CLOCK)				// the original 100MHz clock is divided by 10^8
		begin										// generate the 1Hz clock R_CLK_1Hz
		if (R_COUNT == 50000000) 			// if R_COUNT =  5e7, invert R_CLK_1HZ, R_COUNT back to zero
			begin 								
			R_COUNT <= 0;			
			R_CLK_1HZ <= !R_CLK_1HZ;
			end
		else										// if R_COUNT <= 5e7, R_COUNT counts up, R_CLK_1HZ remain
			begin
			R_COUNT <= R_COUNT + 1;
			R_CLK_1HZ <= R_CLK_1HZ;
			end
	 end
/********************************************/	
	 always @(posedge W_CLK_1HZ or posedge RESET) // switch control part
		begin
			if(RESET)							// if RESET = 1, R_OUT becomes zero
				R_OUT <= 0;
			else if(I_SWITCHES[1])			// if down_botton is pressed, R_OUT substracted one by one
				R_OUT <= R_OUT - 1;
			else if(I_SWITCHES[0])			// if up_botton is pressed, R_OUT added one by one
				R_OUT <= R_OUT + 1;
		end
		
endmodule
/********************************************/