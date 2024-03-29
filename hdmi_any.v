
module HDMI_ANY(
	input reset,
	input pixclk,  
	input clk_TMDS2,
	input wire [7:0] red, green, blue,
	input wire rstX,rstY,
	output TMDS_bh,TMDS_bl,TMDS_gh,TMDS_gl,TMDS_rh,TMDS_rl,
	output reg [10:0] CounterX, CounterY
);

//800*600p60 
//pixclk=40 MHz
//Horizontal Timings
parameter hActivePixels        =800;
parameter hFrontPorch           =40;
parameter hSyncWidth           =128;
parameter hBackPorch            =88;
parameter hBlankingTotal       =256;
parameter hTotalPixels        =1056;

//Vertical Timings
parameter vActiveLines         =600;
parameter vFrontPorch            =1;
parameter vSyncWidth             =4;
parameter vBackPorch            =23;
parameter vBlankingTotal        =28;
parameter vTotalLines          =628;

/*//1280*720p60 
//pixclk=75 MHz
//Horizontal Timings
parameter hActivePixels       =1280;
parameter hFrontPorch          =110;
parameter hSyncWidth            =40;
parameter hBackPorch           =220;
parameter hBlankingTotal       =370;
parameter hTotalPixels        =1650;

//Vertical Timings
parameter vActiveLines         =720;
parameter vFrontPorch            =5;
parameter vSyncWidth             =5;
parameter vBackPorch            =20;
parameter vBlankingTotal        =30;
parameter vTotalLines          =750;*/

reg hSync, vSync, DrawArea;
always @(posedge pixclk) DrawArea <= (CounterX<hActivePixels) && (CounterY<vActiveLines);
always @(posedge pixclk) CounterX <= (CounterX==hTotalPixels-1) ? 0 : CounterX+1;
always @(posedge pixclk) if(CounterX==hTotalPixels-1) CounterY <= (CounterY==vTotalLines-1) ? 0 : CounterY+1;
always @(posedge pixclk) hSync <= (CounterX>=hActivePixels+hFrontPorch) && (CounterX<hActivePixels+hFrontPorch+hSyncWidth);
always @(posedge pixclk) vSync <= (CounterY>=vActiveLines+vFrontPorch) && (CounterY<vActiveLines+vFrontPorch+vSyncWidth);

wire [9:0] TMDS_red, TMDS_green, TMDS_blue;
TMDS_encoder encode_R(.clk(pixclk), .VD(red  ), .CD(2'b00)        , .VDE(DrawArea), .TMDS(TMDS_red));
TMDS_encoder encode_G(.clk(pixclk), .VD(green), .CD(2'b00)        , .VDE(DrawArea), .TMDS(TMDS_green));
TMDS_encoder encode_B(.clk(pixclk), .VD(blue ), .CD({vSync,hSync}), .VDE(DrawArea), .TMDS(TMDS_blue));

reg [2:0] TMDS_mod5=0;  // modulus 5 counter
reg [4:0] TMDS_shift_bh=0, TMDS_shift_bl=0;
reg [4:0] TMDS_shift_gh=0, TMDS_shift_gl=0;
reg [4:0] TMDS_shift_rh=0, TMDS_shift_rl=0;

wire [4:0] TMDS_blue_l = {TMDS_blue[9],TMDS_blue[7],TMDS_blue[5],TMDS_blue[3],TMDS_blue[1]};
wire [4:0] TMDS_blue_h= {TMDS_blue[8],TMDS_blue[6],TMDS_blue[4],TMDS_blue[2],TMDS_blue[0]};
wire [4:0] TMDS_green_l = {TMDS_green[9],TMDS_green[7],TMDS_green[5],TMDS_green[3],TMDS_green[1]};
wire [4:0] TMDS_green_h= {TMDS_green[8],TMDS_green[6],TMDS_green[4],TMDS_green[2],TMDS_green[0]};
wire [4:0] TMDS_red_l = {TMDS_red[9],TMDS_red[7],TMDS_red[5],TMDS_red[3],TMDS_red[1]};
wire [4:0] TMDS_red_h= {TMDS_red[8],TMDS_red[6],TMDS_red[4],TMDS_red[2],TMDS_red[0]};

always @(posedge clk_TMDS2)
begin
if(reset==1)
	begin
	TMDS_shift_bh  <= TMDS_mod5[2] ? TMDS_blue_h   : TMDS_shift_bh  [4:1];
	TMDS_shift_bl  <= TMDS_mod5[2] ? TMDS_blue_l   : TMDS_shift_bl  [4:1];
	TMDS_shift_gh  <= TMDS_mod5[2] ? TMDS_green_h   : TMDS_shift_gh  [4:1];
	TMDS_shift_gl  <= TMDS_mod5[2] ? TMDS_green_l   : TMDS_shift_gl  [4:1];
	TMDS_shift_rh  <= TMDS_mod5[2] ? TMDS_red_h   : TMDS_shift_rh  [4:1];
	TMDS_shift_rl  <= TMDS_mod5[2] ? TMDS_red_l   : TMDS_shift_rl  [4:1];
	TMDS_mod5 <= (TMDS_mod5[2]) ? 3'd0 : TMDS_mod5+3'd1;
	end
end

assign TMDS_bh = TMDS_shift_bh[0];
assign TMDS_bl = TMDS_shift_bl[0];
assign TMDS_gh = TMDS_shift_gh[0];
assign TMDS_gl = TMDS_shift_gl[0];
assign TMDS_rh = TMDS_shift_rh[0];
assign TMDS_rl = TMDS_shift_rl[0];

endmodule

module TMDS_encoder(
	input clk,
	input [7:0] VD,  // video data (red, green or blue)
	input [1:0] CD,  // control data
	input VDE,  // video data enable, to choose between CD (when VDE=0) and VD (when VDE=1)
	output reg [9:0] TMDS = 0
);

wire [3:0] Nb1s = VD[0] + VD[1] + VD[2] + VD[3] + VD[4] + VD[5] + VD[6] + VD[7];
wire XNOR = (Nb1s>4'd4) || (Nb1s==4'd4 && VD[0]==1'b0);
wire [8:0] q_m = {~XNOR, q_m[6:0] ^ VD[7:1] ^ {7{XNOR}}, VD[0]};

reg [3:0] balance_acc = 0;
wire [3:0] balance = q_m[0] + q_m[1] + q_m[2] + q_m[3] + q_m[4] + q_m[5] + q_m[6] + q_m[7] - 4'd4;
wire balance_sign_eq = (balance[3] == balance_acc[3]);
wire invert_q_m = (balance==0 || balance_acc==0) ? ~q_m[8] : balance_sign_eq;
wire [3:0] balance_acc_inc = balance - ({q_m[8] ^ ~balance_sign_eq} & ~(balance==0 || balance_acc==0));
wire [3:0] balance_acc_new = invert_q_m ? balance_acc-balance_acc_inc : balance_acc+balance_acc_inc;
wire [9:0] TMDS_data = {invert_q_m, q_m[8], q_m[7:0] ^ {8{invert_q_m}}};
wire [9:0] TMDS_code = CD[1] ? (CD[0] ? 10'b1010101011 : 10'b0101010100) : (CD[0] ? 10'b0010101011 : 10'b1101010100);

always @(posedge clk) TMDS <= VDE ? TMDS_data : TMDS_code;
always @(posedge clk) balance_acc <= VDE ? balance_acc_new : 4'h0;
endmodule


