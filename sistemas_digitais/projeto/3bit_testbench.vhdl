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
        -- toogle switchs input
        SW : in std_logic_vector(9 downto 0);
        -- led output
        LEDR: out std_logic_vector(3 downto 0);
        HEX0: out std_logic_vector(6 downto 0)
    );
end component;

signal SW: std_logic_vector(9 downto 0);
signal LEDR: std_logic_vector(3 downto 0);
signal HEX0: std_logic_vector(6 downto 0);

begin
  -- Connect DUT
  DUT: ula_3_bit port map(SW, LEDR, HEX0);

  process
  begin
    -- TEMPLATE: AAA BBB M Ci S0 S1
    -- THE FOLLOWING 4 CASES REFER TO THE LOGIC COMPONENT
    -- I.E: M = 0
    
    -- SOME CASES OF LOGIC OPERATION 0 => Fi = Ai
    SW <= "000---0-00";

    wait for 1 ns;
    assert(LEDR="1111") report "LED FAIL IN LOGIC OPERATION 0 => Fi = Ai" severity error;
    assert(HEX0="1000000") report "7 SEGMENT FAIL IN LOGIC OPERATION 0 => Fi = Ai" severity error;

    SW <= "010---0-00";

    wait for 1 ns;
    assert(LEDR="1101") report "LED FAIL IN LOGIC OPERATION 0 => Fi = Ai" severity error;
    assert(HEX0="0100100") report "7 SEGMENT FAIL IN LOGIC OPERATION 0 => Fi = Ai" severity error;

    SW <= "110---0-00";

    wait for 1 ns;
    assert(LEDR="1001") report "LED FAIL IN LOGIC OPERATION 0 => Fi = Ai" severity error;
    assert(HEX0="0000010") report "7 SEGMENT FAIL IN LOGIC OPERATION 0 => Fi = Ai" severity error;
    

    SW <= "111---0-00";

    wait for 1 ns;
    assert(LEDR="1000") report "LED FAIL IN LOGIC OPERATION 0 => Fi = Ai" severity error;
    assert(HEX0="1111000") report "7 SEGMENT FAIL IN LOGIC OPERATION 0 => Fi = Ai" severity error;

    -- SOME CASES OF LOGIC OPERATION 1 => Fi = not Ai

    SW <= "010---0-10";

    wait for 1 ns;
    assert(LEDR="1010") report "LED FAIL IN LOGIC OPERATION 1 => Fi = not Ai" severity error;
    assert(HEX0="0010010") report "7 SEGMENT FAIL IN LOGIC OPERATION 1 => Fi = not Ai" severity error;
    

    SW <= "101---0-10";

    wait for 1 ns;
    assert(LEDR="1101") report "LED FAIL IN LOGIC OPERATION 1 => Fi = not Ai" severity error;
    assert(HEX0="0100100") report "7 SEGMENT FAIL IN LOGIC OPERATION 1 => Fi = not Ai" severity error;
    
    assert false report "Test done." severity note;
    wait;
  end process;
end tb;