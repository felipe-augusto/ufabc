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
        -- toogle switchs input
        SW : in std_logic_vector(9 downto 0);
        -- led output
        LEDR: out std_logic_vector(3 downto 0);
        -- 7-segments
        HEX0: out std_logic_vector(6 downto 0)
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
-- this signals are not necessary, but they make clearer which
-- SW entry maps to what input in ula_1_bit
signal M, Ci, S0, S1, Co: std_logic;
signal A, B, F: std_logic_vector(2 downto 0);

begin
    -- drive SW inputs to variables
    -- this is not necessary, just to make it clearer
    A <=  SW(9 downto 7);
    B <=  SW(6 downto 4);
    M <=  SW(3);
    Ci <= SW(2);
    S0 <= SW(1);
    S1 <= SW(0);
    -- drive carry in for signal C
    C(0) <= Ci;
    -- use 3 ULAs to calculate F
    ULA0: ula_1_bit port map(A(0), B(0), M, C(0), S0, S1, C(1), F(0));
    ULA1: ula_1_bit port map(A(1), B(1), M, C(1), S0, S1, C(2), F(1));
    ULA2: ula_1_bit port map(A(2), B(2), M, C(2), S0, S1, C(3), F(2));
    -- drive C(3) to output Co
    Co <= C(3);

    -- LED
    -- drive F to LEDR to show in the board
    -- since the LED display uses 1 -> off and 0 -> on
    -- we need to negate the output
    LEDR(3) <= not Co;
    LEDR(2 downto 0) <= not F(2 downto 0);

    -- 7-segment-display
    process (F, Co) -- sensitivity list
    begin
        -- first we check if there's a carry out element
        case Co is
            -- if not, we will output in display a number from 0 to 7
            when '0' =>
                case F is
                when "000" => HEX0 <= "1000000"; -- 0
                when "001" => HEX0 <= "1111001"; -- 1
                when "010" => HEX0 <= "0100100"; -- 2
                when "011" => HEX0 <= "0110000"; -- 3
                when "100" => HEX0 <= "0011001"; -- 4
                when "101" => HEX0 <= "0010010"; -- 5
                when "110" => HEX0 <= "0000010"; -- 6
                when "111" => HEX0 <= "1111000"; -- 7
                when others => null;
                end case;
            -- if true, we will output in display a number
            -- from 8 to 15 (hexadecimal)
            when '1' =>
                case F is
                when "000" => HEX0 <= "0000000"; -- 8
                when "001" => HEX0 <= "0011000"; -- 9
                when "010" => HEX0 <= "0001000"; -- A
                when "011" => HEX0 <= "0000011"; -- B
                when "100" => HEX0 <= "1000110"; -- C
                when "101" => HEX0 <= "0100001"; -- D
                when "110" => HEX0 <= "0000110"; -- E
                when "111" => HEX0 <= "0001110"; -- F
                when others => null;
                end case;
            when others => null;
        end case;
    end process;
end behavior_3;