module RGB8_RGB24(
       input  wire [7:0]RGB,
		 output wire [7:0]R,
		 output wire [7:0]G,
		 output wire [7:0]B
		 );
		 
assign R={RGB[7:5],5'b00000};
assign G={RGB[4:3],6'b000000};
assign B={RGB[2:0],5'b00000};

endmodule