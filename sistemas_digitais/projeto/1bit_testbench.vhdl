-- Testbench for
-- 1-BIT ALU

library IEEE;
use IEEE.std_logic_1164.all;
 
entity testbench is
-- empty
end testbench; 

architecture tb of testbench is

-- DUT component
component ula_1_bit is
  port(
    -- inputs in ULA
    A: in std_logic;
    B: in std_logic;
    -- flag for arithmetic MODE
    M: in std_logic;
    -- carry in
    Ci: in std_logic;
    -- 4 operation chooser
    S0: in std_logic;
    S1: in std_logic;
    
    -- carry out output
    Co: out  std_logic;
    -- result output
    F: out  std_logic
  );
end component;

signal A, B, M, Ci, S0, S1, Co, F: std_logic;

begin

  -- Connect DUT
  DUT: ula_1_bit port map(A, B, M, Ci, S0, S1, Co, F);

  process
  begin
    -- THE FOLLOWING 4 CASES REFER TO THE LOGIC COMPONENT
    -- I.E: M = 0
    
    -- LOGIC OPERATION 0 => Fi = Ai
    M <= '0';
    S0 <= '0';
    S1 <= '0';
    A <= '0';

    wait for 1 ns;
    assert(F='0') report "LOGIC OPERATION 0 => Fi = Ai" severity error;
    
    M <= '0';
    S0 <= '0';
    S1 <= '0';
    A <= '1';

    wait for 1 ns;
    assert(F='1') report "LOGIC OPERATION 0 => Fi = Ai" severity error;
    
    -- LOGIC OPERATION 1 => Fi = not Ai
    
    M <= '0';
    S0 <= '1';
    S1 <= '0';
    A <= '0';

    wait for 1 ns;
    assert(F='1') report "LOGIC OPERATION 1 => Fi = not Ai" severity error;

    M <= '0';
    S0 <= '1';
    S1 <= '0';
    A <= '1';

    wait for 1 ns;
    assert(F='0') report "LOGIC OPERATION 1 => Fi = not Ai" severity error;

    -- LOGIC OPERATION 2 => Fi = Ai xor Bi

    M <= '0';
    S0 <= '0';
    S1 <= '1';
    A <= '0';
    B <= '0';

    wait for 1 ns;
    assert(F='0') report "LOGIC OPERATION 2 => Fi = Ai xor Bi" severity error;

    M <= '0';
    S0 <= '0';
    S1 <= '1';
    A <= '0';
    B <= '1';

    wait for 1 ns;
    assert(F='1') report "LOGIC OPERATION 2 => Fi = Ai xor Bi" severity error;

    M <= '0';
    S0 <= '0';
    S1 <= '1';
    A <= '1';
    B <= '0';

    wait for 1 ns;
    assert(F='1') report "LOGIC OPERATION 2 => Fi = Ai xor Bi" severity error;

    M <= '0';
    S0 <= '0';
    S1 <= '1';
    A <= '1';
    B <= '1';

    wait for 1 ns;
    assert(F='0') report "LOGIC OPERATION 2 => Fi = Ai xor Bi" severity error;

    -- LOGIC OPERATION 3 => Fi =  Ai xnor Bi

    M <= '0';
    S0 <= '1';
    S1 <= '1';
    A <= '0';
    B <= '0';

    wait for 1 ns;
    assert(F='1') report "LOGIC OPERATION 3 => Fi =  Ai xnor Bi" severity error;

    M <= '0';
    S0 <= '1';
    S1 <= '1';
    A <= '0';
    B <= '1';

    wait for 1 ns;
    assert(F='0') report "LOGIC OPERATION 3 => Fi =  Ai xnor Bi" severity error;

    M <= '0';
    S0 <= '1';
    S1 <= '1';
    A <= '1';
    B <= '0';

    wait for 1 ns;
    assert(F='0') report "LOGIC OPERATION 3 => Fi =  Ai xnor Bi" severity error;

    M <= '0';
    S0 <= '1';
    S1 <= '1';
    A <= '1';
    B <= '1';

    wait for 1 ns;
    assert(F='1') report "LOGIC OPERATION 3 => Fi =  Ai xnor Bi" severity error;

    -- THE FOLLOWING 8 CASES REFER TO THE ARITHMETIC COMPONENT
    -- I.E: M = 1

    -- THE FIRST FOUR CASES HAVE Ci = 0

    -- ARITHMETIC OPERATION 0 => F = A

    M <= '1';
    S1 <= '0';
    S0 <= '0';
    Ci <= '0';
    A <= '0';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 0 => F = A" severity error;

    M <= '1';
    S1 <= '0';
    S0 <= '0';
    Ci <= '0';
    A <= '1';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 0 => F = A" severity error;

    -- ARITHMETIC OPERATION 1 => F = not A

    M <= '1';
    S1 <= '0';
    S0 <= '1';
    Ci <= '0';
    A <= '0';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 1 => F = not A" severity error;

    M <= '1';
    S1 <= '0';
    S0 <= '1';
    Ci <= '0';
    A <= '1';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 1 => F = not A" severity error;

    -- ARITHMETIC OPERATION 2 => F = A plus B 

    M <= '1';
    S1 <= '1';
    S0 <= '0';
    Ci <= '0';
    A <= '0';
    B <= '0';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 2 => F = A plus B " severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 2 => F = A plus B " severity error;


    M <= '1';
    S1 <= '1';
    S0 <= '0';
    Ci <= '0';
    A <= '0';
    B <= '1';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 2 => F = A plus B " severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 2 => F = A plus B " severity error;


    M <= '1';
    S1 <= '1';
    S0 <= '0';
    Ci <= '0';
    A <= '1';
    B <= '0';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 2 => F = A plus B " severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 2 => F = A plus B " severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '0';
    Ci <= '0';
    A <= '1';
    B <= '1';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 2 => F = A plus B " severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 2 => F = A plus B " severity error;

    -- ARITHMETIC OPERATION 3 => F = (not A) plus B

    M <= '1';
    S1 <= '1';
    S0 <= '1';
    Ci <= '0';
    A <= '0';
    B <= '0';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 3 => F = (not A) plus B" severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 3 => F = (not A) plus B" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '1';
    Ci <= '0';
    A <= '0';
    B <= '1';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 3 => F = (not A) plus B" severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 3 => F = (not A) plus B" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '1';
    Ci <= '0';
    A <= '1';
    B <= '0';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 3 => F = (not A) plus B" severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 3 => F = (not A) plus B" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '1';
    Ci <= '0';
    A <= '1';
    B <= '1';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 3 => F = (not A) plus B" severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 3 => F = (not A) plus B" severity error;

    -- ARITHMETIC OPERATION 4 => F = A plus 1

    M <= '1';
    S1 <= '0';
    S0 <= '0';
    Ci <= '1';
    A <= '0';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 4 => F = A plus 1" severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 4 => F = A plus 1" severity error;

    M <= '1';
    S1 <= '0';
    S0 <= '0';
    Ci <= '1';
    A <= '1';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 4 => F = A plus 1" severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 4 => F = A plus 1" severity error;

    -- ARITHMETIC OPERATION 5 => F = (not A) plus 1 

    M <= '1';
    S1 <= '0';
    S0 <= '1';
    Ci <= '1';
    A <= '0';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 5 => F = (not A) plus 1 " severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 5 => F = (not A) plus 1 " severity error;

    M <= '1';
    S1 <= '0';
    S0 <= '1';
    Ci <= '1';
    A <= '1';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 5 => F = (not A) plus 1 " severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 5 => F = (not A) plus 1 " severity error;

    -- ARITHMETIC OPERATION 6 => F = A plus B plus 1

    M <= '1';
    S1 <= '1';
    S0 <= '0';
    Ci <= '1';
    A <= '0';
    B <= '0';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 6 => F = A plus B plus 1" severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 6 => F = A plus B plus 1" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '0';
    Ci <= '1';
    A <= '0';
    B <= '1';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 6 => F = A plus B plus 1" severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 6 => F = A plus B plus 1" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '0';
    Ci <= '1';
    A <= '1';
    B <= '0';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 6 => F = A plus B plus 1" severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 6 => F = A plus B plus 1" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '0';
    Ci <= '1';
    A <= '1';
    B <= '1';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 6 => F = A plus B plus 1" severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 6 => F = A plus B plus 1" severity error;

    -- ARITHMETIC OPERATION 7 => F = A plus B plus 1

    M <= '1';
    S1 <= '1';
    S0 <= '1';
    Ci <= '1';
    A <= '0';
    B <= '0';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 7 => F = A plus B plus 1" severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 7 => F = A plus B plus 1" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '1';
    Ci <= '1';
    A <= '0';
    B <= '1';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 7 => F = A plus B plus 1" severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 7 => F = A plus B plus 1" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '1';
    Ci <= '1';
    A <= '1';
    B <= '0';

    wait for 1 ns;
    assert(F='1') report "ARITHMETIC OPERATION 7 => F = A plus B plus 1" severity error;
    assert(Co='0') report "ARITHMETIC OPERATION 7 => F = A plus B plus 1" severity error;

    M <= '1';
    S1 <= '1';
    S0 <= '1';
    Ci <= '1';
    A <= '1';
    B <= '1';

    wait for 1 ns;
    assert(F='0') report "ARITHMETIC OPERATION 7 => F = A plus B plus 1" severity error;
    assert(Co='1') report "ARITHMETIC OPERATION 7 => F = A plus B plus 1" severity error;

    assert false report "Test done." severity note;
    wait;
  end process;
end tb;