-------------------------------------------------------------------------------
-- OPB AC97 Controller
--     -  component declaration
-------------------------------------------------------------------------------
--
--     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
--     SOLELY FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR
--     XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION
--     AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE, APPLICATION
--     OR STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS
--     IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
--     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
--     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
--     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
--     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
--     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
--     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
--     FOR A PARTICULAR PURPOSE.
--     
--     (c) Copyright 2004 Xilinx, Inc.
--     All rights reserved.
--
-------------------------------------------------------------------------------
-- Filename:     opb_ac97_controller_ref_pkg.vhd
--
-- Description:
--    Contains component declaration
--
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

package opb_ac97_controller_ref_pkg is
   
   component OPB_AC97_CONTROLLER_REF
      generic (
         C_OPB_AWIDTH      : integer := 32;
         C_OPB_DWIDTH      : integer := 32;
         C_BASEADDR        : std_logic_vector(0 to 31) := X"A600_0000";
         C_HIGHADDR        : std_logic_vector(0 to 31) := X"A600_00FF";
         C_PLAYBACK        : integer := 1;
         C_RECORD          : integer := 1;
         C_PLAY_INTR_LEVEL : integer := 1;
         C_REC_INTR_LEVEL  : integer := 4);
      port (
         OPB_Clk                     : in  std_logic;
         OPB_Rst                     : in  std_logic;
         OPB_ABus                    : in  std_logic_vector(0 to 31);
         OPB_BE                      : in  std_logic_vector(0 to 3);
         OPB_RNW                     : in  std_logic;
         OPB_select                  : in  std_logic;
         OPB_seqAddr                 : in  std_logic;
         OPB_DBus                    : in  std_logic_vector(0 to 31);
         OPB_AC97_CONTROLLER_DBus    : out std_logic_vector(0 to 31);
         OPB_AC97_CONTROLLER_errAck  : out std_logic;
         OPB_AC97_CONTROLLER_retry   : out std_logic;
         OPB_AC97_CONTROLLER_toutSup : out std_logic;
         OPB_AC97_CONTROLLER_xferAck : out std_logic;
         Playback_Interrupt          : out std_logic;
         Record_Interrupt            : out std_logic;
         Bit_Clk                     : in  std_logic;
         Sync                        : out std_logic;
         SData_Out                   : out std_logic;
         SData_In                    : in  std_logic);
   end component;
   
end opb_ac97_controller_ref_pkg;

