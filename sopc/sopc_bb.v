
module sopc (
	clk_clk,
	clock_bridge_1_out_clk_clk,
	clock_bridge_2_out_clk_clk,
	new_sdram_controller_0_wire_addr,
	new_sdram_controller_0_wire_ba,
	new_sdram_controller_0_wire_cas_n,
	new_sdram_controller_0_wire_cke,
	new_sdram_controller_0_wire_cs_n,
	new_sdram_controller_0_wire_dq,
	new_sdram_controller_0_wire_dqm,
	new_sdram_controller_0_wire_ras_n,
	new_sdram_controller_0_wire_we_n,
	nios2_gen2_0_debug_conduit_debug_ack,
	nios2_gen2_0_debug_conduit_debug_req,
	reset_reset_n,
	video_sync_generator_0_sync_RGB_OUT,
	video_sync_generator_0_sync_HD,
	video_sync_generator_0_sync_VD,
	video_sync_generator_0_sync_DEN,
	clock_bridge_0_out_clk_clk);	

	input		clk_clk;
	output		clock_bridge_1_out_clk_clk;
	output		clock_bridge_2_out_clk_clk;
	output	[11:0]	new_sdram_controller_0_wire_addr;
	output	[1:0]	new_sdram_controller_0_wire_ba;
	output		new_sdram_controller_0_wire_cas_n;
	output		new_sdram_controller_0_wire_cke;
	output		new_sdram_controller_0_wire_cs_n;
	inout	[7:0]	new_sdram_controller_0_wire_dq;
	output		new_sdram_controller_0_wire_dqm;
	output		new_sdram_controller_0_wire_ras_n;
	output		new_sdram_controller_0_wire_we_n;
	output		nios2_gen2_0_debug_conduit_debug_ack;
	input		nios2_gen2_0_debug_conduit_debug_req;
	input		reset_reset_n;
	output	[7:0]	video_sync_generator_0_sync_RGB_OUT;
	output		video_sync_generator_0_sync_HD;
	output		video_sync_generator_0_sync_VD;
	output		video_sync_generator_0_sync_DEN;
	output		clock_bridge_0_out_clk_clk;
endmodule
