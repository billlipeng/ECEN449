-------------------------------------------------------------------------------
-- opb_ac97_controller.vhd
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
-- Filename:        opb_ac97_controller_ref.vhd
--
-- Description:     
--                  
-- VHDL-Standard:   VHDL'93
-------------------------------------------------------------------------------
-- Structure:   
--              opb_ac97_controller_ref.vhd
--
-------------------------------------------------------------------------------
-- Author:          g
-- Revision:        $Revision: 1.1.1.1 $
-- Date:            $Date: 2006/05/25 22:25:30 $
--
-- History:
--   g      2002-01-09    First Version
--
-------------------------------------------------------------------------------
-- Naming Conventions:
--      active low signals:                     "*_n"
--      clock signals:                          "clk", "clk_div#", "clk_#x" 
--      reset signals:                          "rst", "rst_n" 
--      generics:                               "C_*" 
--      user defined types:                     "*_TYPE" 
--      state machine next state:               "*_ns" 
--      state machine current state:            "*_cs" 
--      combinatorial signals:                  "*_com" 
--      pipelined or register delay signals:    "*_d#" 
--      counter signals:                        "*cnt*"
--      clock enable signals:                   "*_ce" 
--      internal version of output port         "*_i"
--      device pins:                            "*_pin" 
--      ports:                                  - Names begin with Uppercase 
--      processes:                              "*_PROCESS" 
--      component instantiations:               "<ENTITY_>I_<#|FUNC>
-------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

entity OPB_AC97_CONTROLLER_REF is
  generic (
    C_OPB_AWIDTH      : integer                   := 32;
    C_OPB_DWIDTH      : integer                   := 32;
    C_BASEADDR        : std_logic_vector(0 to 31) := X"A600_0000";
    C_HIGHADDR        : std_logic_vector(0 to 31) := X"A600_00FF";
    C_PLAYBACK        : integer                   := 1;
    C_RECORD          : integer                   := 1;
    -- value of 0,1,2,3,4
    -- 0 = No Interrupt
    -- 1 = empty      Nr_Of_Valid_Words = 0
    -- 2 = halfempty  Nr_Of_Valid_Words = 0-7
    -- 3 = halffull   Nr_Of_Valid_Words = 8-16
    -- 4 = full       Nr_Of_Valid_Words = 16
    C_PLAY_INTR_LEVEL : integer                   := 2;
    C_REC_INTR_LEVEL  : integer                   := 3
    );
  port (
    -- Global signals
    OPB_Clk : in std_logic;
    OPB_Rst : in std_logic;

    -- OPB signals
    OPB_ABus    : in std_logic_vector(0 to 31);
    OPB_BE      : in std_logic_vector(0 to 3);
    OPB_RNW     : in std_logic;
    OPB_select  : in std_logic;
    OPB_seqAddr : in std_logic;
    OPB_DBus    : in std_logic_vector(0 to 31);

    OPB_AC97_CONTROLLER_DBus    : out std_logic_vector(0 to 31);
    OPB_AC97_CONTROLLER_errAck  : out std_logic;
    OPB_AC97_CONTROLLER_retry   : out std_logic;
    OPB_AC97_CONTROLLER_toutSup : out std_logic;
    OPB_AC97_CONTROLLER_xferAck : out std_logic;

    -- Interrupt signals
    Playback_Interrupt : out std_logic;
    Record_Interrupt   : out std_logic;

    -- CODEC signals
    Bit_Clk   : in  std_logic;
    Sync      : out std_logic;
    SData_Out : out std_logic;
    SData_In  : in  std_logic
    );

end entity OPB_AC97_CONTROLLER_REF;

library opb_ac97_controller_ref_v1_01_a;
use opb_ac97_controller_ref_v1_01_a.all;

library Common_v1_00_a;
use Common_v1_00_a.pselect;

-- synthesis translate_off
library unisim;
use unisim.vcomponents.all;
-- synthesis translate_on

architecture IMP of OPB_AC97_CONTROLLER_REF is

  component opb_ac97_core is
    generic (
      C_PLAYBACK : integer := 1;
      C_RECORD   : integer := 0
      );
    port (
      -- signals belonging to Clk clock region
      Clk   : in std_logic;
      Reset : in std_logic;

      AC97_Reg_Addr         : in  std_logic_vector(0 to 6);
      AC97_Reg_Read         : in  std_logic;
      AC97_Reg_Write_Data   : in  std_logic_vector(0 to 15);
      AC97_Reg_Read_Data    : out std_logic_vector(0 to 15);
      AC97_Reg_Access       : in  std_logic;
      AC97_Got_Request      : out std_logic;
      AC97_Reg_Finished     : out std_logic;
      AC97_Request_Finished : in  std_logic;
      CODEC_RDY             : out std_logic;

      In_Data_FIFO   : in  std_logic_vector(0 to 15);
      In_Data_Exists : in  std_logic;
      in_FIFO_Read   : out std_logic;

      Out_Data_FIFO  : out std_logic_vector(0 to 15);
      Out_FIFO_Full  : in  std_logic;
      Out_FIFO_Write : out std_logic;

      -- signals belonging to Bit_Clk clock region
      Bit_Clk   : in  std_logic;
      Sync      : out std_logic;
      SData_Out : out std_logic;
      SData_In  : in  std_logic);
  end component opb_ac97_core;

  component pselect is
    generic (
      C_AB  : integer;
      C_AW  : integer;
      C_BAR : std_logic_vector);
    port (
      A      : in  std_logic_vector(0 to C_AW-1);
      AValid : in  std_logic;
      ps     : out std_logic);
  end component pselect;
  
  --used for 1024 deep record fifo 
  component fifo_generator_v4_4
	port (
	clk: IN std_logic;
	din: IN std_logic_VECTOR(15 downto 0);
	rd_en: IN std_logic;
	rst: IN std_logic;
	wr_en: IN std_logic;
	almost_empty: OUT std_logic;
	almost_full: OUT std_logic;
	dout: OUT std_logic_VECTOR(15 downto 0);
	empty: OUT std_logic;
	full: OUT std_logic);
end component;
--use for 8192 deep playback fifo
component playback_fifo_generator_v4_4
	port (
	clk: IN std_logic;
	din: IN std_logic_VECTOR(15 downto 0);
	rd_en: IN std_logic;
	rst: IN std_logic;
	wr_en: IN std_logic;
	almost_full: OUT std_logic;
	dout: OUT std_logic_VECTOR(15 downto 0);
	empty: OUT std_logic;
	full: OUT std_logic;
	prog_empty: OUT std_logic);
end component;
--  component SRL_FIFO is
--    generic (
--      C_DATA_BITS : integer;
--      C_DEPTH     : integer);
--    port (
--      Clk         : in  std_logic;
--      Reset       : in  std_logic;
--      Clear_FIFO  : in  std_logic;
--      FIFO_Write  : in  std_logic;
--      Data_In     : in  std_logic_vector(0 to C_DATA_BITS-1);
--      FIFO_Read   : in  std_logic;
--      Data_Out    : out std_logic_vector(0 to C_DATA_BITS-1);
--      FIFO_Full   : out std_logic;
--      Data_Exists : out std_logic;
--      Half_Full   : out std_logic;
--      Half_Empty  : out std_logic
--      );
--  end component SRL_FIFO;

  component FDRE is
    port (
      Q  : out std_logic;
      C  : in  std_logic;
      CE : in  std_logic;
      D  : in  std_logic;
      R  : in  std_logic);
  end component FDRE;

  component FDSE is
    port (
      Q  : out std_logic;
      C  : in  std_logic;
      CE : in  std_logic;
      D  : in  std_logic;
      S  : in  std_logic);
  end component FDSE;

  component FDR is
    port (Q : out std_logic;
          C : in  std_logic;
          D : in  std_logic;
          R : in  std_logic);
  end component FDR;

  component FDCE is
    port (
      Q   : out std_logic;
      C   : in  std_logic;
      CE  : in  std_logic;
      D   : in  std_logic;
      CLR : in  std_logic);
  end component FDCE;

  function Addr_Bits (x, y : std_logic_vector(0 to C_OPB_AWIDTH-1)) return integer is
    variable addr_nor : std_logic_vector(0 to C_OPB_AWIDTH-1);
  begin
    addr_nor := x xor y;
    for i in 0 to C_OPB_AWIDTH-1 loop
      if addr_nor(i) = '1' then return i;
      end if;
    end loop;
    return(C_OPB_AWIDTH);
  end function Addr_Bits;

  constant C_AB : integer := Addr_Bits(C_HIGHADDR, C_BASEADDR);

  subtype  ADDR_CHK is natural range C_OPB_AWIDTH-5 to C_OPB_AWIDTH-3;
  constant IN_FIFO_ADR     : std_logic_vector(0 to 2) := "000";
  constant OUT_FIFO_ADR    : std_logic_vector(0 to 2) := "001";
  constant FIFO_STATUS_ADR : std_logic_vector(0 to 2) := "010";
  constant FIFO_CTRL_ADR   : std_logic_vector(0 to 2) := "011";
  constant AC97_CTRL_ADR   : std_logic_vector(0 to 2) := "100";
  constant AC97_READ_ADR   : std_logic_vector(0 to 2) := "101";
  constant AC97_WRITE_ADR  : std_logic_vector(0 to 2) := "110";

  signal opb_ac97_controller_CS : std_logic;

  signal opb_ac97_controller_CS_1 : std_logic;  -- Active as long as OPB_AC97_CONTROLLER_CS is active
  signal opb_ac97_controller_CS_2 : std_logic;  -- Active only 1 clock cycle during an
  signal opb_ac97_controller_CS_3 : std_logic;  -- Active only 1 clock cycle during an
                                                -- access

  signal xfer_Ack  : std_logic;
  signal opb_RNW_1 : std_logic;

  signal OPB_AC97_CONTROLLER_Dbus_i : std_logic_vector(0 to 15);

  signal in_FIFO_Write      : std_logic;
  signal in_FIFO_Read       : std_logic;
  signal in_FIFO_Read_gated : std_logic;
  signal in_Data_FIFO       : std_logic_vector(0 to 15);
  signal in_FIFO_Full       : std_logic;
  signal in_Data_Exists     : std_logic;
  signal in_FIFO_Empty      : std_logic; --added signal
  signal out_FIFO_Empty     : std_logic; --added signal
  signal in_FIFO_Half_Full  : std_logic;
  signal in_FIFO_Half_Empty : std_logic;

  signal out_FIFO_Write      : std_logic;
  signal out_FIFO_Read       : std_logic;
  signal out_Data_Read       : std_logic_vector(0 to 15);
  signal out_Data_FIFO       : std_logic_vector(0 to 15);
  signal out_FIFO_Full       : std_logic;
  signal out_Data_Exists     : std_logic;
  signal out_FIFO_Half_Full  : std_logic;
  signal out_FIFO_Half_Empty : std_logic;

  -- Read Only
  signal status_Reg : std_logic_vector(7 downto 0);
  -- bit 7 '1' if out_FIFO hade a overrun condition
  -- bit 6 '1' if in_FIFO hade a underrun condition
  -- bit 5 If the CODEC is ready for commands
  -- bit 4 Register Access is finished and if it was a read the data
  --       is in AC97_Reg_Read register, reading AC97_Reg_Read_Register will clear
  --       this bit
  -- bit 3 out_FIFO_Empty
  -- bit 2 out_FIFO_Full
  -- bit 1 in_FIFO_Empty
  -- bit 0 in_FIFO_Full

  signal out_FIFO_Overrun : std_logic;
  signal in_FIFO_Underrun : std_logic;
  
  signal clear_in_fifo  : std_logic;
  signal clear_out_fifo : std_logic;
  
  signal ac97_Reg_Addr       : std_logic_vector(0 to 6);
  signal ac97_Reg_Read       : std_logic;
  signal ac97_Reg_Write_Data : std_logic_vector(0 to 15);
  signal ac97_Reg_Read_Data  : std_logic_vector(0 to 15);
  signal ac97_Reg_Access     : std_logic;
  signal ac97_Got_Request    : std_logic;
  signal ac97_reg_access_S   : std_logic;
  signal ac97_Reg_Finished   : std_logic;
  signal ac97_Reg_Finished_i : std_logic;

  signal register_Access_Finished     : std_logic;
  signal register_Access_Finished_Set : std_logic;

  signal codec_rdy : std_logic;

  attribute syn_noclockbuf : boolean;
  attribute syn_noclockbuf of IMP : architecture is true;

begin  -- architecture IMP


  -----------------------------------------------------------------------------
  -- Handling the OPB bus interface
  -----------------------------------------------------------------------------

  -- Do the OPB address decoding
  pselect_I : pselect
    generic map (
      C_AB  => C_AB,                    -- [integer]
      C_AW  => C_OPB_AWIDTH,            -- [integer]
      C_BAR => C_BASEADDR)              -- [std_logic_vector]
    port map (
      A      => OPB_ABus,               -- [in  std_logic_vector(0 to C_AW-1)]
      AValid => OPB_select,             -- [in  std_logic]
      ps     => opb_ac97_controller_CS);  -- [out std_logic]

  OPB_AC97_CONTROLLER_errAck  <= '0';
  OPB_AC97_CONTROLLER_retry   <= '0';
  OPB_AC97_CONTROLLER_toutSup <= '0';

  -----------------------------------------------------------------------------
  -- Decoding the OPB control signals
  -----------------------------------------------------------------------------
  opb_ac97_controller_CS_1_DFF : FDR
    port map (
      Q => opb_ac97_controller_CS_1,    -- [out std_logic]
      C => OPB_Clk,                     -- [in  std_logic]
      D => OPB_AC97_CONTROLLER_CS,      -- [in  std_logic]
      R => xfer_Ack);                   -- [in std_logic]

  opb_ac97_controller_CS_2_DFF : process (OPB_Clk, OPB_Rst) is
  begin  -- process opb_ac97_controller_CS_2_DFF
    if OPB_Rst = '1' then               -- asynchronous reset (active high)
      opb_ac97_controller_CS_2 <= '0';
      opb_ac97_controller_CS_3 <= '0';
      opb_RNW_1                <= '0';
    elsif OPB_Clk'event and OPB_Clk = '1' then  -- rising clock edge
      opb_ac97_controller_CS_2 <= opb_ac97_controller_CS_1
                                  and not opb_ac97_controller_CS_2
                                  and not opb_ac97_controller_CS_3;
      opb_ac97_controller_CS_3 <= opb_ac97_controller_CS_2;
      opb_RNW_1                <= OPB_RNW;
    end if;
  end process opb_ac97_controller_CS_2_DFF;

  Read_Mux : process (status_reg, OPB_ABus, out_Data_Read, ac97_Reg_Read_Data) is
  begin  -- process Read_Mux
    OPB_AC97_CONTROLLER_Dbus_i <= (others => '0');
    if (OPB_ABus(ADDR_CHK) = FIFO_STATUS_ADR) then
      OPB_AC97_CONTROLLER_Dbus_i(15-status_reg'length+1 to 15) <= status_reg;
    elsif (OPB_ABus(ADDR_CHK) = AC97_READ_ADR) then
      OPB_AC97_CONTROLLER_Dbus_i(0 to 15) <= ac97_Reg_Read_Data;
    else
      OPB_AC97_CONTROLLER_Dbus_i(0 to 15) <= out_Data_Read;
    end if;
  end process Read_Mux;

  DWIDTH_gt_16 : if (C_OPB_DWIDTH > 16) generate
    OPB_AC97_CONTROLLER_Dbus(0 to C_OPB_DWIDTH-17) <= (others => '0');
  end generate DWIDTH_gt_16;

  OPB_rdDBus_DFF : for I in C_OPB_DWIDTH-16 to C_OPB_DWIDTH-1 generate
    OPB_rdBus_FDRE : FDRE
      port map (
        Q  => OPB_AC97_CONTROLLER_DBus(I),  -- [out std_logic]
        C  => OPB_Clk,                  -- [in  std_logic]
        CE => opb_ac97_controller_CS_2,     -- [in  std_logic]
        D  => OPB_AC97_CONTROLLER_Dbus_i(I-(C_OPB_DWIDTH-16)),  -- [in  std_logic]
        R  => xfer_Ack);                -- [in std_logic]
  end generate OPB_rdDBus_DFF;

  -- Generating read and write pulses to the FIFOs
  in_FIFO_write <= opb_ac97_controller_CS_2 and (not OPB_RNW_1) when (OPB_ABus(ADDR_CHK) = IN_FIFO_ADR)  else '0';
  out_FIFO_read <= opb_ac97_controller_CS_2 and OPB_RNW_1       when (OPB_ABus(ADDR_CHK) = OUT_FIFO_ADR) else '0';

  clear_in_fifo <= OPB_DBus(31) and opb_ac97_controller_CS_2 and (not OPB_RNW_1) when (OPB_ABus(ADDR_CHK) = FIFO_CTRL_ADR)  else '0';
  clear_out_fifo <= OPB_DBus(30) and opb_ac97_controller_CS_2 and (not OPB_RNW_1) when (OPB_ABus(ADDR_CHK) = FIFO_CTRL_ADR)  else '0';
  
  XFER_Control : process (OPB_Clk, OPB_Rst) is
  begin  -- process XFER_Control
    if OPB_Rst = '1' then               -- asynchronous reset (active high)
      xfer_Ack <= '0' after 100 ps;     -- delay for sim
    elsif OPB_Clk'event and OPB_Clk = '1' then  -- rising clock edge
      xfer_Ack <= opb_ac97_controller_CS_2 after 100 ps;  -- delay for sim
    end if;
  end process XFER_Control;

  OPB_AC97_CONTROLLER_xferAck <= xfer_Ack;

  -----------------------------------------------------------------------------
  -- Status register
  -----------------------------------------------------------------------------
  FIFO_Error_Handle: process (OPB_Clk, OPB_Rst) is
  begin  -- process FIFO_Error_Handle
    if OPB_Rst = '1' then                 -- asynchronous reset (active high)
      out_FIFO_Overrun <= '0';
      in_FIFO_Underrun <= '0';
    elsif OPB_Clk'event and OPB_Clk = '1' then  -- rising clock edge
      -- Reading FIFO_Status register will clear the error flags
      if (clear_in_fifo = '1') then
        in_FIFO_Underrun <= '0';
      elsif (in_Data_Exists = '0') and (in_FIFO_Read = '1') then
        in_FIFO_Underrun <= '1';
      end if;
      if (clear_out_fifo = '1') then
        out_FIFO_Overrun <= '0';
      elsif (out_FIFO_Full = '1') and (out_FIFO_Write = '1') and (out_FIFO_read = '0') then
        out_FIFO_Overrun <= '1';
      end if;
    end if;
  end process FIFO_Error_Handle;

  status_reg(7) <= out_FIFO_Overrun;
  status_reg(6) <= in_FIFO_Underrun;
  status_reg(5) <= codec_rdy;
  status_reg(4) <= register_Access_Finished;
  status_reg(3) <= not(out_Data_Exists);
  status_reg(2) <= out_FIFO_Full;
  status_reg(1) <= in_FIFO_Half_Full;
  status_reg(0) <= in_FIFO_Full;

  -----------------------------------------------------------------------------
  -- AC97 Register Handling
  -----------------------------------------------------------------------------
  AC97_Write_Reg_Data : process (OPB_Clk, OPB_Rst) is
  begin  -- process AC97_Write_Reg_Data
    if OPB_Rst = '1' then               -- asynchronous reset (active high)
      ac97_reg_write_data <= (others => '0');
    elsif OPB_Clk'event and OPB_Clk = '1' then  -- rising clock edge
      if (opb_ac97_controller_CS_2 = '1') and (OPB_RNW_1 = '0') and (OPB_ABus(ADDR_CHK) = AC97_WRITE_ADR) then
        ac97_reg_write_data <= OPB_DBus(C_OPB_DWIDTH-16 to C_OPB_DWIDTH-1);
      end if;
    end if;
  end process AC97_Write_Reg_Data;

  AC97_Access_Reg : process (OPB_Clk, OPB_Rst) is
  begin  -- process AC97_Access_Reg
    if OPB_Rst = '1' then               -- asynchronous reset (active high)
      ac97_reg_addr     <= (others => '0');
      ac97_reg_read     <= '0';
      ac97_reg_access_S <= '0';
    elsif OPB_Clk'event and OPB_Clk = '1' then  -- rising clock edge
      ac97_reg_access_S <= '0';
      if (opb_ac97_controller_CS_2 = '1') and (OPB_RNW_1 = '0') and (OPB_ABus(ADDR_CHK) = AC97_CTRL_ADR) then
        ac97_reg_addr     <= OPB_DBus(C_OPB_DWIDTH-7 to C_OPB_DWIDTH-1);
        ac97_reg_read     <= OPB_DBus(C_OPB_DWIDTH-8);
        ac97_reg_access_S <= '1';
      end if;
    end if;
  end process AC97_Access_Reg;

  ac97_reg_access_FDCE : FDCE
    port map (
      Q   => ac97_reg_access,           -- [out std_logic]
      C   => OPB_Clk,                   -- [in  std_logic]
      CE  => ac97_reg_access_S,         -- [in  std_logic]
      D   => '1',                       -- [in  std_logic]
      CLR => ac97_Got_Request);         -- [in std_logic]

  ac97_reg_access_FDSE : FDSE
    port map (
      Q  => register_Access_Finished,       -- [out std_logic]
      C  => OPB_Clk,                        -- [in  std_logic]
      CE => ac97_reg_access_S,              -- [in  std_logic]
      D  => '0',                            -- [in  std_logic]
      S  => register_Access_Finished_Set);  -- [in std_logic]

  AC97_Register_SM : process (OPB_Clk, OPB_Rst) is
  begin  -- process AC97_Register_SM
    if OPB_Rst = '1' then               -- asynchronous reset (active high)
      ac97_Reg_Finished_i          <= '0';
      register_Access_Finished_Set <= '0';
    elsif OPB_Clk'event and OPB_Clk = '1' then  -- rising clock edge
      register_Access_Finished_Set <= '0';
      if (ac97_Reg_Finished = '1' and ac97_Reg_Finished_i = '0') then
        register_Access_Finished_Set <= '1';
      end if;
      ac97_Reg_Finished_i <= ac97_Reg_Finished;
    end if;
  end process AC97_Register_SM;

  -----------------------------------------------------------------------------
  -- Instanciating the FIFOs
  -----------------------------------------------------------------------------

in_FIFO_Read_gated <= in_FIFO_Read and in_Data_Exists;


  Using_Playback : if (C_PLAYBACK = 1) generate
    IN_FIFO : playback_fifo_generator_v4_4
		port map (
			clk => OPB_Clk,
			din => OPB_DBus(C_OPB_DWIDTH-16 to C_OPB_DWIDTH-1),
			rd_en => in_FIFO_Read_gated,
			rst => clear_in_fifo,
			wr_en => in_FIFO_Write,
			almost_full => in_FIFO_Half_Full,
			dout => in_Data_FIFO,
			empty => in_FIFO_empty,
			full => in_FIFO_Full,
			prog_empty => in_FIFO_Half_Empty);
			in_Data_Exists <= not in_FIFO_empty;
  end generate Using_Playback;
--    IN_FIFO : SRL_FIFO
--      generic map (
--        C_DATA_BITS => 16,              -- [integer]
--        C_DEPTH     => 256)              -- [integer]
--      port map (
--        Clk         => OPB_Clk,         -- [in  std_logic]
--        Reset       => OPB_Rst,         -- [in  std_logic]
--        Clear_FIFO  => clear_in_fifo,  -- [in  std_logic]
--        FIFO_Write  => in_FIFO_Write,   -- [in  std_logic]
--        Data_In     => OPB_DBus(C_OPB_DWIDTH-16 to C_OPB_DWIDTH-1),  -- [in  std_logic_vector(0 to C_OPB_DWIDTH-1)]
--        FIFO_Read   => in_FIFO_Read_gated,    -- [in  std_logic]
--        Data_Out    => in_Data_FIFO,  -- [out std_logic_vector(0 to C_OPB_DWIDTH-1)]
--        FIFO_Full   => in_FIFO_Full,    -- [out std_logic]
--        Data_Exists => in_Data_Exists,  -- [out std_logic]
--        Half_Full   => in_FIFO_Half_Full,    -- [out std_logic]
--        Half_Empty  => in_FIFO_Half_Empty);  -- [out std_logic]

  No_Playback : if (C_PLAYBACK = 0) generate
    in_Data_FIFO   <= (others => '0');
    in_FIFO_Full   <= '0';
    in_Data_Exists <= '0';
  end generate No_Playback;

  Using_Recording : if (C_RECORD = 1) generate
    OUT_FIFO : fifo_generator_v4_4
		port map (
			clk => OPB_Clk,
			din => OPB_DBus(C_OPB_DWIDTH-16 to C_OPB_DWIDTH-1),
			rd_en => out_FIFO_Read,
			rst => clear_out_fifo,
			wr_en => out_FIFO_Write,
			almost_empty => out_FIFO_Half_Empty,
			almost_full => out_FIFO_Half_Full,
			dout => out_Data_Read,
			empty => out_FIFO_empty,
			full => out_FIFO_Full);
			out_Data_Exists <= not out_FIFO_empty;
  end generate Using_Recording;
--    OUT_FIFO : SRL_FIFO
--      generic map (
--        C_DATA_BITS => 16,              -- [integer]
--        C_DEPTH     => 256)              -- [integer]
--      port map (
--        Clk         => OPB_Clk,         -- [in  std_logic]
--        Reset       => OPB_Rst,         -- [in  std_logic]
--        Clear_FIFO  => clear_out_fifo,  -- [in  std_logic]
--        FIFO_Write  => out_FIFO_Write,  -- [in  std_logic]
--        Data_In     => out_Data_FIFO,  -- [in  std_logic_vector(0 to C_OPB_DWIDTH-1)]
--        FIFO_Read   => out_FIFO_Read,   -- [in  std_logic]
--        Data_Out    => out_Data_Read,  -- [out std_logic_vector(0 to C_OPB_DWIDTH-1)]
--        FIFO_Full   => out_FIFO_Full,   -- [out std_logic]
--        Data_Exists => out_Data_Exists,       -- [out std_logic]
--        Half_Full   => out_FIFO_Half_Full,    -- [out std_logic]
--        Half_Empty  => out_FIFO_Half_Empty);  -- [out std_logic]


  No_Recording : if (C_RECORD = 0) generate
    out_Data_Read   <= (others => '0');
    out_FIFO_Full   <= '0';
    out_Data_Exists <= '0';
  end generate No_Recording;

  -----------------------------------------------------------------------------
  -- Instanciating the OPB_AC97_CONTROLLER core
  -----------------------------------------------------------------------------
  opb_ac97_core_I : opb_ac97_core
    generic map (
      C_PLAYBACK => C_PLAYBACK,
      C_RECORD   => C_RECORD
      )
    port map (
      -- signals belonging to Clk clock region
      Clk   => OPB_Clk,                 -- [in  std_logic]
      Reset => OPB_Rst,                 -- [in  std_logic]

      AC97_Reg_Addr         => ac97_Reg_Addr,  -- [in  std_logic_vector(0 to 6)]
      AC97_Reg_Read         => ac97_Reg_Read,  -- [in  std_logic]
      AC97_Reg_Write_Data   => ac97_Reg_Write_Data,  -- [in  std_logic_vector(0 to 15)]
      AC97_Reg_Read_Data    => ac97_Reg_Read_Data,  -- [out std_logic_vector(0 to 15)]
      AC97_Reg_Access       => ac97_Reg_Access,     -- [in  std_logic]
      AC97_Got_Request      => ac97_Got_Request,    -- [out  std_logic]
      AC97_Reg_Finished     => ac97_Reg_Finished,   -- [out std_logic]
      AC97_Request_Finished => register_Access_Finished,  -- [in std_logic]
      CODEC_RDY             => codec_rdy,      -- [out std_logic]

      In_Data_FIFO   => In_Data_FIFO,    -- [in  std_logic_vector(0 to 15)]
      In_Data_Exists => In_Data_Exists,  -- [in  std_logic]
      in_FIFO_Read   => in_FIFO_Read,    -- [out std_logic]

      Out_Data_FIFO  => Out_Data_FIFO,   -- [out std_logic_vector(0 to 15)]
      Out_FIFO_Full  => Out_FIFO_Full,   -- [in  std_logic]
      Out_FIFO_Write => Out_FIFO_Write,  -- [out std_logic]

      -- signals belonging to Bit_Clk clock region
      Bit_Clk   => Bit_Clk,             -- [in  std_logic]
      Sync      => Sync,                -- [out std_logic]
      SData_Out => SData_Out,           -- [out std_logic]
      SData_In  => SData_In);           -- [out std_logic]

  -----------------------------------------------------------------------------
  -- Handling the interrupts
  -----------------------------------------------------------------------------
  Playback_Interrupt_Handle: process (in_FIFO_Half_Full, in_FIFO_Half_Empty,
                                      in_FIFO_Full, In_Data_Exists) is
  begin  -- process Playback_Interrupt_Handle
    if (C_PLAY_INTR_LEVEL = 1) then
      Playback_Interrupt <=  not(In_Data_Exists);
    elsif (C_PLAY_INTR_LEVEL = 2) then
      Playback_Interrupt <=  in_FIFO_Half_Empty;
    elsif (C_PLAY_INTR_LEVEL = 3) then
      Playback_Interrupt <=  in_FIFO_Half_Full;
    elsif (C_PLAY_INTR_LEVEL = 4) then
      Playback_Interrupt <=  in_FIFO_Full;
    else
      Playback_Interrupt <= '0';
    end if;
  end process Playback_Interrupt_Handle;
  
  Record_Interrupt_Handle: process (out_FIFO_Half_Full, out_FIFO_Half_Empty,
                                    out_FIFO_Full, Out_Data_Exists) is
  begin  -- process Record_Interrupt_Handle
    if (C_REC_INTR_LEVEL = 1) then
      Record_Interrupt <=  not(Out_Data_Exists);
    elsif (C_REC_INTR_LEVEL = 2) then
      Record_Interrupt <=  out_FIFO_Half_Empty;
    elsif (C_REC_INTR_LEVEL = 3) then
      Record_Interrupt <=  out_FIFO_Half_Full;
    elsif (C_REC_INTR_LEVEL = 4) then
      Record_Interrupt <=  out_FIFO_Full;
    else
      Record_Interrupt <= '0';
    end if;
  end process Record_Interrupt_Handle;

end architecture IMP;



