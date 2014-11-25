`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   23:13:26 09/30/2013
// Design Name:   zero_checker
// Module Name:   /homes/ugrad/billlipeng/ECEN449/HW/HW2/hw2b/hw2b/testbench.v
// Project Name:  hw2b
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: zero_checker
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module testbench;

	// Inputs
	reg [11:0] data;
	reg data_ready;

	// Outputs
	wire result;

	// Instantiate the Unit Under Test (UUT)
	zero_checker uut (
		.data(data), 
		.data_ready(data_ready), 
		.result(result)
	);

	initial begin
		// Initialize Inputs
		data = 0;
		data_ready = 0;

		// Wait 100 ns for global reset to finish
		#100;
		data_ready = 1;
		data = 12'b101010101010;
		#100;
		data_ready = 1;
		data = 12'b101111101010;
		#100;
		data_ready = 0;
		data = 12'b111110101010;
		#100;
		data_ready = 1;
		data = 12'b111110101010;
		#100;
		data_ready = 0;
		data = 12'b111110101010;
		#100;
       
	end
      
endmodule

