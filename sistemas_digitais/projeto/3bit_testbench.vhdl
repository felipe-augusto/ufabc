-- Testbench for
-- 3-BIT ALU

library IEEE;
use IEEE.std_logic_1164.all;
 
entity testbench is
-- empty
end testbench; 

architecture tb of testbench is

-- DUT component
component ula_3_bit is
  port(
    -- 3-bit inputs in ULA
    A : in std_logic_vector(2 downto 0);
    B : in std_logic_vector(2 downto 0);
    -- flag for arithmetic MODE
    M : in std_logic;
    -- carry in
    Ci : in std_logic;
    -- 4 operation chooser
    S0: in std_logic;
    S1: in std_logic;

    -- carry out output
    Co: out std_logic;
    -- 3-bit result output
    F: out std_logic_vector(2 downto 0)
  );
end component;

signal A, B: std_logic_vector(2 downto 0);
signal M, Ci, S0, S1, Co: std_logic;
signal F: std_logic_vector(2 downto 0);

begin
  -- Connect DUT
  DUT: ula_3_bit port map(A, B, M, Ci, S0, S1, Co, F);

  process
  begin
    -- THE FOLLOWING 4 CASES REFER TO THE LOGIC COMPONENT
    -- I.E: M = 0
    
    -- LOGIC OPERATION 0 => Fi = Ai
    M <= '0';
    S0 <= '0';
    S1 <= '0';
    A <= "000";

    wait for 1 ns;
    assert(F="000") report "LOGIC OPERATION 0 => Fi = Ai" severity error;

    M <= '0';
    S0 <= '0';
    S1 <= '0';
    A <= "100";

    wait for 1 ns;
    assert(F="100") report "LOGIC OPERATION 0 => Fi = Ai" severity error;

    assert false report "Test done." severity note;
    wait;
  end process;
end tb;