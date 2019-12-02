	component sopc is
		port (
			clk_clk                              : in    std_logic                     := 'X';             -- clk
			clock_bridge_1_out_clk_clk           : out   std_logic;                                        -- clk
			clock_bridge_2_out_clk_clk           : out   std_logic;                                        -- clk
			new_sdram_controller_0_wire_addr     : out   std_logic_vector(11 downto 0);                    -- addr
			new_sdram_controller_0_wire_ba       : out   std_logic_vector(1 downto 0);                     -- ba
			new_sdram_controller_0_wire_cas_n    : out   std_logic;                                        -- cas_n
			new_sdram_controller_0_wire_cke      : out   std_logic;                                        -- cke
			new_sdram_controller_0_wire_cs_n     : out   std_logic;                                        -- cs_n
			new_sdram_controller_0_wire_dq       : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- dq
			new_sdram_controller_0_wire_dqm      : out   std_logic;                                        -- dqm
			new_sdram_controller_0_wire_ras_n    : out   std_logic;                                        -- ras_n
			new_sdram_controller_0_wire_we_n     : out   std_logic;                                        -- we_n
			nios2_gen2_0_debug_conduit_debug_ack : out   std_logic;                                        -- debug_ack
			nios2_gen2_0_debug_conduit_debug_req : in    std_logic                     := 'X';             -- debug_req
			reset_reset_n                        : in    std_logic                     := 'X';             -- reset_n
			video_sync_generator_0_sync_RGB_OUT  : out   std_logic_vector(7 downto 0);                     -- RGB_OUT
			video_sync_generator_0_sync_HD       : out   std_logic;                                        -- HD
			video_sync_generator_0_sync_VD       : out   std_logic;                                        -- VD
			video_sync_generator_0_sync_DEN      : out   std_logic;                                        -- DEN
			clock_bridge_0_out_clk_clk           : out   std_logic                                         -- clk
		);
	end component sopc;

	u0 : component sopc
		port map (
			clk_clk                              => CONNECTED_TO_clk_clk,                              --                         clk.clk
			clock_bridge_1_out_clk_clk           => CONNECTED_TO_clock_bridge_1_out_clk_clk,           --      clock_bridge_1_out_clk.clk
			clock_bridge_2_out_clk_clk           => CONNECTED_TO_clock_bridge_2_out_clk_clk,           --      clock_bridge_2_out_clk.clk
			new_sdram_controller_0_wire_addr     => CONNECTED_TO_new_sdram_controller_0_wire_addr,     -- new_sdram_controller_0_wire.addr
			new_sdram_controller_0_wire_ba       => CONNECTED_TO_new_sdram_controller_0_wire_ba,       --                            .ba
			new_sdram_controller_0_wire_cas_n    => CONNECTED_TO_new_sdram_controller_0_wire_cas_n,    --                            .cas_n
			new_sdram_controller_0_wire_cke      => CONNECTED_TO_new_sdram_controller_0_wire_cke,      --                            .cke
			new_sdram_controller_0_wire_cs_n     => CONNECTED_TO_new_sdram_controller_0_wire_cs_n,     --                            .cs_n
			new_sdram_controller_0_wire_dq       => CONNECTED_TO_new_sdram_controller_0_wire_dq,       --                            .dq
			new_sdram_controller_0_wire_dqm      => CONNECTED_TO_new_sdram_controller_0_wire_dqm,      --                            .dqm
			new_sdram_controller_0_wire_ras_n    => CONNECTED_TO_new_sdram_controller_0_wire_ras_n,    --                            .ras_n
			new_sdram_controller_0_wire_we_n     => CONNECTED_TO_new_sdram_controller_0_wire_we_n,     --                            .we_n
			nios2_gen2_0_debug_conduit_debug_ack => CONNECTED_TO_nios2_gen2_0_debug_conduit_debug_ack, --  nios2_gen2_0_debug_conduit.debug_ack
			nios2_gen2_0_debug_conduit_debug_req => CONNECTED_TO_nios2_gen2_0_debug_conduit_debug_req, --                            .debug_req
			reset_reset_n                        => CONNECTED_TO_reset_reset_n,                        --                       reset.reset_n
			video_sync_generator_0_sync_RGB_OUT  => CONNECTED_TO_video_sync_generator_0_sync_RGB_OUT,  -- video_sync_generator_0_sync.RGB_OUT
			video_sync_generator_0_sync_HD       => CONNECTED_TO_video_sync_generator_0_sync_HD,       --                            .HD
			video_sync_generator_0_sync_VD       => CONNECTED_TO_video_sync_generator_0_sync_VD,       --                            .VD
			video_sync_generator_0_sync_DEN      => CONNECTED_TO_video_sync_generator_0_sync_DEN,      --                            .DEN
			clock_bridge_0_out_clk_clk           => CONNECTED_TO_clock_bridge_0_out_clk_clk            --      clock_bridge_0_out_clk.clk
		);

