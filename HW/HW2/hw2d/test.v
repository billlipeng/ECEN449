`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   00:22:20 10/01/2013
// Design Name:   stat_machine
// Module Name:   /homes/ugrad/billlipeng/ECEN449/HW/HW2/hw2d/test.v
// Project Name:  hw2d
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: stat_machine
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test;

	// Inputs
	reg reset;
	reg A;

	// Outputs
	wire Y;

	// Instantiate the Unit Under Test (UUT)
	stat_machine uut (
		.reset(reset), 
		.A(A), 
		.Y(Y)
	);

	initial begin
		//$monitor($time, "%b",S);
		// Initialize Inputs
		reset = 0;
		A = 0;

		// Wait 100 ns for global reset to finish
		#100;
		A = 1;
		#100;
		A = 0;
		#100;
		A = 1;
		#100;
		A = 0;
		#100;
		A = 0;
		#100;
        
		// Add stimulus here

	end
      
endmodule

