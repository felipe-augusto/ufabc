Trocar os inputs de A, B, M, S0 e S1 para SW (que sao os switches direto na placa, algo do tipo)

SW(9 down to 0)
A, B, M, Ci, S0, S1

A -> 9, 8, 7 antes A -> 2, 1, 0
B -> 6, 5, 4 antes B -> 2, 1, 0
M -> SW(3)
Ci -> SW(2)
S0 -> SW(1)
S1 -> SW(0)

signal C: std_logic_vector(3 downto 0);

ULA0: ula_1_bit port map(SW(7), SW(4), SW(3), C(0), SW(1), SW(0), C(1), F(0));
ULA1: ula_1_bit port map(SW(8), SW(5), SW(3), C(1), SW(1), SW(0), C(2), F(1));
ULA2: ula_1_bit port map(SW(9), SW(6), SW(3), C(2), SW(1), SW(0), C(3), F(2));

C(0) <= SW(2)
Co <= C(3)

o F pode transferir diretamente para os LEDG ou LEDR assim como o Co
Inclusive o F  pode ser LEDG(2 down to 0)
          e Co pode ser LEDG(3) ?? é possivel declarar assim

talvez daria para bater um switch case:

7-segments display (ideia)

process(F)
  begin
      when "000" => HEX0 <= "0000001"; // assumindo 0 eh acesso
      when "001" => HEX0 <= "1001111";
      when "010" => HEX0 <= "0010010";
      when "011" => HEX0 <= "0000110";
      when "100" => HEX0 <= "1001100";
      when "101" => HEX0 <= "0100100";
      when "110" => HEX0 <= "0100000";
      when "111" => HEX0 <= "0001111";
    end case;
  end process;

LEGG = "00001111" // 0 = on, 1 = OFF


==== SIGNALS

REPRESENTS WIRES WITHIN A CIRCUIT
AFTER ARCHITECTURE AND BEFORE BEGIN
YOU CAN CONNECT ENTITIES TOGETHER AND COMMUNICATE CHANGES
YOU CAN ALSO CONNECT COMPONENTS USING SIGNALS

==== PROCCESS
THE INSIDE OF A PROCESS EXECUTES IN ORDER
BUT TWO DIFFERENTE PROCESSES EXECUTES CONCURRENTLY