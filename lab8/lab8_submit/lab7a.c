// lab7a.c
// Author: Peng Li, Sundaresan Adin
// C application for user_logic in Lab 7
#include<xparameters.h>
#include<ir_demod.h>

int main()
{
  // reg0 stores the decoded IR_signal information
  // reg1: number of received signal
  // reg2:for debugging
  int reg0, reg1, reg2;
  // reg0_new, reg1_new, reg2_new stores the updated 
  // value of reg0, reg1, reg2
  int reg0_new, reg1_new, reg2_new;

  reg1 = IR_DEMOD_mReadSlaveReg1(XPAR_IR_DEMOD_0_BASEADDR, 0);
  //xil_printf("Hellow world");
  while(1)
  { 
    // read data from the slv_reg0, slv_reg1, slv_reg2
    reg0_new = IR_DEMOD_mReadSlaveReg0(XPAR_IR_DEMOD_0_BASEADDR, 0); 
    reg1_new = IR_DEMOD_mReadSlaveReg1(XPAR_IR_DEMOD_0_BASEADDR, 0);
    reg2_new = IR_DEMOD_mReadSlaveReg2(XPAR_IR_DEMOD_0_BASEADDR, 0);
    
    // print the result if the value is updated
    if(reg2_new  == 0x8000 && reg1_new != reg1 )
    {
      
      // reg1_new = IR_DEMOD_mReadSlaveReg1(XPAR_IR_DEMOD_0_BASEADDR, 0);
      // print value in reg0
      xil_printf("Decoded IR signal  = 0x%x\n\r", reg0_new);
      
      // print value in reg1
      xil_printf("Number of messages = %d\n\r", reg1_new);
      reg1 = reg1_new;
      // print value in reg2
      xil_printf("Interrupt Status0 = 0x%x\n\r", reg2_new);
      IR_DEMOD_mWriteSlaveReg2(XPAR_IR_DEMOD_0_BASEADDR, 0, 0x10000000);
      xil_printf("Interrupt Status1 = 0x%x\n\r", reg2_new);  
    }	

  }
  return(0);
}
