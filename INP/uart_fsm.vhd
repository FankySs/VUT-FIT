-- uart_fsm.vhd: UART controller - finite state machine
-- Author(s): 
--
library ieee;
use ieee.std_logic_1164.all;

-------------------------------------------------
entity UART_FSM is
port(
   CLK:		in std_logic;
   RST:		in std_logic;
   DIN:		in std_logic;
   CNT:		in std_logic_vector(4 downto 0);
   CNT2:	in std_logic_vector(3 downto 0);
   RX_OUT:	out std_logic;
   CNT_OUT:	out std_logic;
   DOUT_VLD:	out std_logic
   );
end entity UART_FSM;

-------------------------------------------------
architecture behavioral of UART_FSM is
type STATE_TYPE is (WAIT_START_BIT, WAIT_FIRST_BIT, DATA_LOAD, WAIT_STOP_BIT, DATA_FINAL);
signal state: STATE_TYPE := WAIT_START_BIT;
begin
	RX_OUT <= '1' when state = DATA_LOAD ELSE '0';
	CNT_OUT <= '1' when state = WAIT_FIRST_BIT or state = DATA_LOAD else '0';
	process (CLK) begin
		if (rising_edge(CLK)) then
			if (RST = '1') then
				state <= WAIT_FIRST_BIT;
			else
				case state is
				when WAIT_START_BIT =>  if (DIN = '0') then
								state <= WAIT_FIRST_BIT;
							end if;
				when WAIT_FIRST_BIT =>  if (CNT = "11000") then
								state <= DATA_LOAD;
							end if;
				when WAIT_STOP_BIT  =>  if (DIN = '1') then
								DOUT_VLD <= '1';
								state <= DATA_FINAL;
							end if;
				when DATA_LOAD      =>  if CNT2 = "1000" then
								state <= WAIT_STOP_BIT;
							end if;
				when DATA_FINAL     =>  DOUT_VLD <= '0';
							state <= WAIT_START_BIT;
				when others => null;
				end case;
			end if;
		end if;
	end process;
end behavioral;