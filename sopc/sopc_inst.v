	sopc u0 (
		.clk_clk                              (<connected-to-clk_clk>),                              //                         clk.clk
		.clock_bridge_1_out_clk_clk           (<connected-to-clock_bridge_1_out_clk_clk>),           //      clock_bridge_1_out_clk.clk
		.clock_bridge_2_out_clk_clk           (<connected-to-clock_bridge_2_out_clk_clk>),           //      clock_bridge_2_out_clk.clk
		.new_sdram_controller_0_wire_addr     (<connected-to-new_sdram_controller_0_wire_addr>),     // new_sdram_controller_0_wire.addr
		.new_sdram_controller_0_wire_ba       (<connected-to-new_sdram_controller_0_wire_ba>),       //                            .ba
		.new_sdram_controller_0_wire_cas_n    (<connected-to-new_sdram_controller_0_wire_cas_n>),    //                            .cas_n
		.new_sdram_controller_0_wire_cke      (<connected-to-new_sdram_controller_0_wire_cke>),      //                            .cke
		.new_sdram_controller_0_wire_cs_n     (<connected-to-new_sdram_controller_0_wire_cs_n>),     //                            .cs_n
		.new_sdram_controller_0_wire_dq       (<connected-to-new_sdram_controller_0_wire_dq>),       //                            .dq
		.new_sdram_controller_0_wire_dqm      (<connected-to-new_sdram_controller_0_wire_dqm>),      //                            .dqm
		.new_sdram_controller_0_wire_ras_n    (<connected-to-new_sdram_controller_0_wire_ras_n>),    //                            .ras_n
		.new_sdram_controller_0_wire_we_n     (<connected-to-new_sdram_controller_0_wire_we_n>),     //                            .we_n
		.nios2_gen2_0_debug_conduit_debug_ack (<connected-to-nios2_gen2_0_debug_conduit_debug_ack>), //  nios2_gen2_0_debug_conduit.debug_ack
		.nios2_gen2_0_debug_conduit_debug_req (<connected-to-nios2_gen2_0_debug_conduit_debug_req>), //                            .debug_req
		.reset_reset_n                        (<connected-to-reset_reset_n>),                        //                       reset.reset_n
		.video_sync_generator_0_sync_RGB_OUT  (<connected-to-video_sync_generator_0_sync_RGB_OUT>),  // video_sync_generator_0_sync.RGB_OUT
		.video_sync_generator_0_sync_HD       (<connected-to-video_sync_generator_0_sync_HD>),       //                            .HD
		.video_sync_generator_0_sync_VD       (<connected-to-video_sync_generator_0_sync_VD>),       //                            .VD
		.video_sync_generator_0_sync_DEN      (<connected-to-video_sync_generator_0_sync_DEN>),      //                            .DEN
		.clock_bridge_0_out_clk_clk           (<connected-to-clock_bridge_0_out_clk_clk>)            //      clock_bridge_0_out_clk.clk
	);

