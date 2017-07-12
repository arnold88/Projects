library verilog;
use verilog.vl_types.all;
entity md5 is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        load            : in     vl_logic;
        ready           : out    vl_logic;
        text            : in     vl_logic;
        datain          : in     vl_logic_vector(127 downto 0);
        dataout         : out    vl_logic_vector(127 downto 0)
    );
end md5;
