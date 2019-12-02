// (C) 2001-2018 Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files from any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License Subscription 
// Agreement, Intel FPGA IP License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Intel and sold by 
// Intel or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


// Copyright 2014 Altera Corporation. All rights reserved.
// Altera products are protected under numerous U.S. and foreign patents, 
// maskwork rights, copyrights and other intellectual property laws.  
//
// This reference design file, and your use thereof, is subject to and governed
// by the terms and conditions of the applicable Altera Reference Design 
// License Agreement (either as signed by you or found at www.altera.com).  By
// using this reference design file, you indicate your acceptance of such terms
// and conditions between you and Altera Corporation.  In the event that you do
// not agree with such terms and conditions, you may not use the reference 
// design file and please promptly destroy any copies you have made.
//
// This reference design file is being provided on an "as-is" basis and as an 
// accommodation and therefore all warranties, representations or guarantees of 
// any kind (whether express, implied or statutory) including, without 
// limitation, warranties of merchantability, non-infringement, or fitness for
// a particular purpose, are specifically disclaimed.  By making this reference
// design file available, Altera expressly does not recommend, suggest or 
// require that this reference design file be used in combination with any 
// other product not provided by Altera.
/////////////////////////////////////////////////////////////////////////////


`timescale 1ps/1ps

// DESCRIPTION
// 5 bit counter.
// Generated by one of Gregg's toys.   Share And Enjoy.

module alt_hiconnect_cnt5il #(
    parameter SIM_EMULATE = 1'b0
) (
    input clk,
    input inc,
    input sload,
    input [4:0] sload_data,
    output [4:0] dout
);

wire [4:0] dout_w;

alt_hiconnect_lut6 t0 (
    .din({6'h0 | dout | ({6{inc}} & 6'h20)}),
    .dout(dout_w[0])
);
defparam t0 .MASK = 64'h55555555aaaaaaaa;
defparam t0 .SIM_EMULATE = SIM_EMULATE;

alt_hiconnect_lut6 t1 (
    .din({6'h0 | dout | ({6{inc}} & 6'h20)}),
    .dout(dout_w[1])
);
defparam t1 .MASK = 64'h66666666cccccccc;
defparam t1 .SIM_EMULATE = SIM_EMULATE;

alt_hiconnect_lut6 t2 (
    .din({6'h0 | dout | ({6{inc}} & 6'h20)}),
    .dout(dout_w[2])
);
defparam t2 .MASK = 64'h78787878f0f0f0f0;
defparam t2 .SIM_EMULATE = SIM_EMULATE;

alt_hiconnect_lut6 t3 (
    .din({6'h0 | dout | ({6{inc}} & 6'h20)}),
    .dout(dout_w[3])
);
defparam t3 .MASK = 64'h7f807f80ff00ff00;
defparam t3 .SIM_EMULATE = SIM_EMULATE;

alt_hiconnect_lut6 t4 (
    .din({6'h0 | dout | ({6{inc}} & 6'h20)}),
    .dout(dout_w[4])
);
defparam t4 .MASK = 64'h7fff8000ffff0000;
defparam t4 .SIM_EMULATE = SIM_EMULATE;

// hypothetical problem - this is state info and should really be don't replicate
alt_hiconnect_wys_reg r0 (
	.clk(clk),
	.arst(1'b0),
	.d(dout_w),
	.ena(1'b1),
	.sclr(1'b0),
	.sload(sload),
	.sdata(sload_data),
	.q(dout)
);
defparam r0 .WIDTH = 5;
defparam r0 .SIM_EMULATE = SIM_EMULATE;

endmodule
