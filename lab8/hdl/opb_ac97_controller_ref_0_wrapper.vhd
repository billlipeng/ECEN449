-------------------------------------------------------------------------------
-- opb_ac97_controller_ref_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library opb_ac97_controller_ref_v1_01_a;
use opb_ac97_controller_ref_v1_01_a.all;

entity opb_ac97_controller_ref_0_wrapper is
  port (
    OPB_Clk : in std_logic;
    OPB_Rst : in std_logic;
    OPB_ABus : in std_logic_vector(0 to 31);
    OPB_BE : in std_logic_vector(0 to 3);
    OPB_RNW : in std_logic;
    OPB_select : in std_logic;
    OPB_seqAddr : in std_logic;
    OPB_DBus : in std_logic_vector(0 to 31);
    OPB_AC97_CONTROLLER_DBus : out std_logic_vector(0 to 31);
    OPB_AC97_CONTROLLER_errAck : out std_logic;
    OPB_AC97_CONTROLLER_retry : out std_logic;
    OPB_AC97_CONTROLLER_toutSup : out std_logic;
    OPB_AC97_CONTROLLER_xferAck : out std_logic;
    Playback_Interrupt : out std_logic;
    Record_Interrupt : out std_logic;
    Bit_Clk : in std_logic;
    Sync : out std_logic;
    SData_Out : out std_logic;
    SData_In : in std_logic
  );

  attribute x_core_info : STRING;
  attribute x_core_info of opb_ac97_controller_ref_0_wrapper : entity is "opb_ac97_controller_ref_v1_01_a";

end opb_ac97_controller_ref_0_wrapper;

architecture STRUCTURE of opb_ac97_controller_ref_0_wrapper is

  component opb_ac97_controller_ref is
    generic (
      C_OPB_AWIDTH : INTEGER;
      C_OPB_DWIDTH : INTEGER;
      C_BASEADDR : std_logic_vector(0 to 31);
      C_HIGHADDR : std_logic_vector(0 to 31);
      C_PLAYBACK : INTEGER;
      C_RECORD : INTEGER;
      C_PLAY_INTR_LEVEL : INTEGER;
      C_REC_INTR_LEVEL : INTEGER
    );
    port (
      OPB_Clk : in std_logic;
      OPB_Rst : in std_logic;
      OPB_ABus : in std_logic_vector(0 to 31);
      OPB_BE : in std_logic_vector(0 to 3);
      OPB_RNW : in std_logic;
      OPB_select : in std_logic;
      OPB_seqAddr : in std_logic;
      OPB_DBus : in std_logic_vector(0 to 31);
      OPB_AC97_CONTROLLER_DBus : out std_logic_vector(0 to 31);
      OPB_AC97_CONTROLLER_errAck : out std_logic;
      OPB_AC97_CONTROLLER_retry : out std_logic;
      OPB_AC97_CONTROLLER_toutSup : out std_logic;
      OPB_AC97_CONTROLLER_xferAck : out std_logic;
      Playback_Interrupt : out std_logic;
      Record_Interrupt : out std_logic;
      Bit_Clk : in std_logic;
      Sync : out std_logic;
      SData_Out : out std_logic;
      SData_In : in std_logic
    );
  end component;

begin

  opb_ac97_controller_ref_0 : opb_ac97_controller_ref
    generic map (
      C_OPB_AWIDTH => 32,
      C_OPB_DWIDTH => 32,
      C_BASEADDR => X"74400000",
      C_HIGHADDR => X"7440ffff",
      C_PLAYBACK => 1,
      C_RECORD => 1,
      C_PLAY_INTR_LEVEL => 2,
      C_REC_INTR_LEVEL => 3
    )
    port map (
      OPB_Clk => OPB_Clk,
      OPB_Rst => OPB_Rst,
      OPB_ABus => OPB_ABus,
      OPB_BE => OPB_BE,
      OPB_RNW => OPB_RNW,
      OPB_select => OPB_select,
      OPB_seqAddr => OPB_seqAddr,
      OPB_DBus => OPB_DBus,
      OPB_AC97_CONTROLLER_DBus => OPB_AC97_CONTROLLER_DBus,
      OPB_AC97_CONTROLLER_errAck => OPB_AC97_CONTROLLER_errAck,
      OPB_AC97_CONTROLLER_retry => OPB_AC97_CONTROLLER_retry,
      OPB_AC97_CONTROLLER_toutSup => OPB_AC97_CONTROLLER_toutSup,
      OPB_AC97_CONTROLLER_xferAck => OPB_AC97_CONTROLLER_xferAck,
      Playback_Interrupt => Playback_Interrupt,
      Record_Interrupt => Record_Interrupt,
      Bit_Clk => Bit_Clk,
      Sync => Sync,
      SData_Out => SData_Out,
      SData_In => SData_In
    );

end architecture STRUCTURE;

