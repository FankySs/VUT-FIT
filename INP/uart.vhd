-- uart.vhd: UART controller - receiving part
-- Author(s):
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

-------------------------------------------------
entity UART_RX is
port(	
        CLK: 	    in std_logic;
	RST: 	    in std_logic;
	DIN: 	    in std_logic;
	DOUT: 	    out std_logic_vector(7 downto 0);
	DOUT_VLD:   out std_logic
);
end UART_RX;  

-------------------------------------------------
architecture behavioral of UART_RX is
signal CNT:	std_logic_vector(4 downto 0);
signal CNT2:	std_logic_vector(3 downto 0);
signal RX_OUT:	std_logic;
signal CNT_OUT:	std_logic;
signal DVLD:	std_logic;
begin
FSM: entity work.UART_FSM(behavioral)
port map
(
	CLK => CLK,
	RST => RST,
	DIN => DIN,
	CNT => CNT,
	CNT2 => CNT2,
	RX_OUT => RX_OUT,
	CNT_OUT => CNT_OUT,
	DOUT_VLD => DVDL
);
process (CLK, RST) begin
	if (rising_edge(CLK)) then
		if (CNT_OUT = '1') then
			CNT <= CNT + 1;
		else
			CNT <= "00000";
		end if;
		if (RX_OUT = '1') then
			if (CNT(4) = '1') then
				CNT <= "00000";
				case cnt2 is
				when "0000" => DOUT(0) <= DIN;
				when "0001" => DOUT(1) <= DIN;
				when "0010" => DOUT(2) <= DIN;
				when "0011" => DOUT(3) <= DIN;
				when "0100" => DOUT(4) <= DIN;
				when "0101" => DOUT(5) <= DIN;
				when "0110" => DOUT(6) <= DIN;
				when "0111" => DOUT(7) <= DIN;
				when others => DOUT <= "0000";
				end case;
				CNT2 <= CNT2 + 1;
			end if;
		end if;
	end if;
end process;
end behavioral;