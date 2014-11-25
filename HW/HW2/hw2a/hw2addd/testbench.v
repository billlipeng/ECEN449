`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   21:43:44 09/30/2013
// Design Name:   test1
// Module Name:   /homes/ugrad/billlipeng/ECEN449/HW/HW2/hw2a/hw2a/testbench.v
// Project Name:  hw2a
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: test1
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
	reg clock;
	reg [2:0] operand1;
	reg [2:0] operand2;
	reg mode;

	// Outputs
	wire [2:0] result;
	wire overflow;

	// Instantiate the Unit Under Test (UUT)
	test1 uut (
		.clock(clock), 
		.operand1(operand1), 
		.operand2(operand2), 
		.mode(mode), 
		.result(result), 
		.overflow(overflow)
	);

	initial begin
		// Initialize Inputs
		clock = 0;
		operand1 = 0;
		operand2 = 0;
		mode = 0;
		forever #50 clock = ~clock;
		// Wait 100 ns for global reset to finish
	end
	
	initial begin
	
		#100;
		mode = 0;
		operand1 = 3'b001;
		operand2 = 3'b001;
		
		#100;
		mode = 0;
		operand1 = 3'b101;
		operand2 = 3'b110;
		
		#100;
		mode = 0;
		operand1 = 3'b111;
		operand2 = 3'b111;
				
		#100;
		mode = 1;
		operand1 = 3'b111;
		operand2 = 3'b111;
		
		#100;
		mode = 1;
		operand1 = 3'b101;
		operand2 = 3'b001;
		
		#100;
		mode = 1;
		operand1 = 3'b011;
		operand2 = 3'b011;
		
		#100;
		mode = 1;
		operand1 = 3'b111;
		operand2 = 3'b011;	
		
		#200;
		$finish;
		
	end
      
endmodule

