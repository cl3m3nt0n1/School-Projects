
--------------MUX----------------

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

entity transcode is
		PORT(input: IN std_logic_vector(2 downto 0);
			  offset : IN integer;
			  output: OUT std_logic_vector(2 downto 0));
END transcode;

architecture arch_trans of transcode is

type t_muc is array (0 to 4) of std_logic_vector(2 downto 0);

signal muc : t_muc;

signal indice_0, indice_1, indice_2, indice_3, indice_4 : integer;

begin


	muc(0) <= "011";
	muc(1) <= "000";
	muc(2) <= "001";
	muc(3) <= "010";
	muc(4) <= "010";
	

	indice_0 <= offset;
	indice_1 <= (offset + 1) mod 5;
	indice_2 <= (offset + 2) mod 5;
	indice_3 <= (offset + 3) mod 5;
	indice_4 <= (offset + 4) mod 5;
			  
	process(input)
	begin 
		
		case input is
			
			when "000"  => output <= muc(indice_0);
			when "001"  => output <= muc(indice_1); 
			when "010"  => output <= muc(indice_2);
			when "011"  => output <= muc(indice_3);
			when "100"	=> output <= muc(indice_4);
			when others => output <= "111";

		end case;
		
	end process;

end arch_trans;



--------------SEG----------------

LIBRARY ieee;
USE ieee.std_logic_1164.all; 


entity seg is
	Port
		(
			input: IN std_logic_vector(2 downto 0);
			output : OUT std_logic_vector(6 downto 0)
		);
END seg;

architecture arch_seg of seg is



begin

	process(input)
	begin 
		
		case input is
			
			when "000"  => output <= "0001001";
			when "001"  => output <= "0000110"; 
			when "010"  => output <= "1000111"; 
			when "011"  => output <= "1000000"; 
		 when others	=> output <= "1111111"; 

		end case;
		
	end process;

END arch_seg;

--------------SEVEN SEG----------------

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

entity seven_seg_decoder is
	Port
		(
			S1,S2,S3: IN std_logic;
			out1, out2, out3, out4, out5 : OUT std_logic_vector(6 downto 0)
		);
END seven_seg_decoder;


architecture arch_seven of seven_seg_decoder is



	component seg
		Port
			(
				input: IN std_logic_vector(2 downto 0);
				output : OUT std_logic_vector(6 downto 0)
			);
	END component;
	
	
	component transcode
		Port
			(
				input: IN std_logic_vector(2 downto 0);
				offset : IN integer;
				output : OUT std_logic_vector(2 downto 0)
			);
	END component;
	
	
	signal out_trans1, out_trans2, out_trans3, out_trans4, out_trans5 :std_logic_vector(2 downto 0);

	
BEGIN 
	
	
	trans1:transcode port map(input(0)=>S1, input(1)=>S2,input(2)=>S3, offset =>1, output=> out_trans1);
	trans2:transcode port map(input(0)=>S1, input(1)=>S2,input(2)=>S3, offset =>2, output=> out_trans2);
	trans3:transcode port map(input(0)=>S1, input(1)=>S2,input(2)=>S3, offset =>3, output=> out_trans3);
	trans4:transcode port map(input(0)=>S1, input(1)=>S2,input(2)=>S3, offset =>4, output=> out_trans4);
	trans5:transcode port map(input(0)=>S1, input(1)=>S2,input(2)=>S3, offset =>0, output=> out_trans5);
	
	
	seg_1:seg port map(input => out_trans1, output=>out5);
	seg_2:seg port map(input => out_trans2, output=>out4);
	seg_3:seg port map(input => out_trans3, output=>out3);
	seg_4:seg port map(input => out_trans4, output=>out2);
	seg_5:seg port map(input => out_trans5, output=>out1);

	
end arch_seven;


