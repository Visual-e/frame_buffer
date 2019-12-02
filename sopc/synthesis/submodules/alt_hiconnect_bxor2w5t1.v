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
// Bus XOR gate, 2 words of 5 bits.  Latency 1.
// Generated by one of Gregg's toys.   Share And Enjoy.

module alt_hiconnect_bxor2w5t1 #(
    parameter SIM_EMULATE = 1'b0
) (
    input clk,
    input [9:0] din,
    output [4:0] dout
);

// combine 2 words of 5 bits
genvar i,k;
generate
    for (i=0; i<5; i=i+1) begin : g0
        wire [1:0] local_din;
        for (k=0; k<2; k=k+1) begin : g1
            assign local_din[k] = din[k*5+i];
        end

        alt_hiconnect_xor2t1 c0 (
            .clk(clk),
            .din(local_din),
            .dout(dout[i])
        );
        defparam c0 .SIM_EMULATE = SIM_EMULATE;

    end
endgenerate

endmodule

