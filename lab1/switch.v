`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:54:09 09/04/2013 
// Design Name: 
// Module Name:    switch 
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
module switch(SWITCHES,LEDS);
    input 	[3:0]	SWITCHES;
    output 	[3:0] LEDS;
	 
    assign 	LEDS[3:0] = SWITCHES[3:0];

endmodule
