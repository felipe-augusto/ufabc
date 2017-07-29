library IEEE;
use IEEE.std_logic_1164.all;

entity ula_1_bit is 
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
end ula_1_bit;

architecture behavior of ula_1_bit is
begin
    -- this logic is in the slide
    F <= (S1 and B) xor ((S0 xor A) xor (M and Ci));
    Co <= ((S0 xor A) and (M and Ci)) or ((S1 and B) and ((S0 xor A) xor (M and Ci)));
end behavior;

library ieee;
use ieee.std_logic_1164.all;

-- 3-bit ALU using 1-bit ALU's

entity ula_3_bit is
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
end ula_3_bit;

architecture behavior_3 of ula_3_bit is
component ula_1_bit
    port(
        A, B, M, Ci, S0, S1: in std_logic;
        Co, F: out std_logic
    );
end component;

signal C: std_logic_vector(3 downto 0);
begin
    -- use 3 ULAs to calculate the F output
    ULA0: ula_1_bit port map(A(0), B(0), M, C(0), S0, S1, C(1), F(0));
    ULA1: ula_1_bit port map(A(1), B(1), M, C(1), S0, S1, C(2), F(1));
    ULA2: ula_1_bit port map(A(2), B(2), M, C(2), S0, S1, C(3), F(2));
    -- copy carry in for signal C
    C(0) <= Ci; -- SW(2)
    -- copy C(3) to output Co
    Co <= C(3);
end behavior_3;