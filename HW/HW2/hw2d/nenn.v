`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:46:11 10/03/2013 
// Design Name: 
// Module Name:    nenn 
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
module nenn(
    output out,
    input in1,
    input in2,
    input in3
    );
assign /*out  = ~(~in1 & in2) & in3;*/
out = in1 | ~in2 & in3;
endmodule
