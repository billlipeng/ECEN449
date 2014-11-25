`timescale 1ns / 1ps
/////////////////////////////
// Create Date:    22:54:09 09/04/2013 
// Module Name:    switch 
/////////////////////////////
module switch(SWITCHES,LEDS);
    input 	[3:0]	SWITCHES;	// 4-bits input switches
    output 	[3:0] LEDS;			// 4-bits output leds
    assign 	LEDS[3:0] = SWITCHES[3:0]; // assigne the value of switches to the leds 
endmodule
