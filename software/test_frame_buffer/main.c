#include "main.h"
#include "simple_gfx/simple_graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "system.h"
#include "sys/alt_log_printf.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"

int main(void)
{
	unsigned int x1,y1,x2,y2,r;
	signed char dx,dy;
	unsigned int color1, color2;

	//unsigned char *memPoint1=(unsigned char*)0x01000000;
	//unsigned char *memPoint2=(unsigned char*)0x01000000;

	alt_up_pixel_buffer_dma_dev* my_pixel_buffer;
	// Use the name of your pixel buffer DMA core
	my_pixel_buffer = alt_up_pixel_buffer_dma_open_dev(
				"/dev/video_pixel_buffer_dma_0");

	// Check for error and output to the console
	//
	if ( my_pixel_buffer == NULL)
	  printf ("Error: could not open pixel buffer device \n");
	else
	  printf ("Opened pixel buffer device \n");

	alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);
	alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,1);

	color2=0;
	x2=10;
	y2=10;
	dx=1;
	dy=1;
	while(1)
		{

		color1 = rand()%65535;
		color2++;
		x1 = abs(rand()%400);
		y1 = abs(rand()%300);
		r = abs(rand()%30);

		vid_draw_circle(my_pixel_buffer, x1, y1, r, color1, 1);

		alt_up_pixel_buffer_dma_draw_box(my_pixel_buffer,x2-1,y2-1,x2+80,y2+10,0x0000,1);
		vid_print_string(my_pixel_buffer, x2, y2, color2, cour10_font, "visuale.ru");
		//Swap buffers and clear
		alt_up_pixel_buffer_dma_swap_buffers(my_pixel_buffer);
		while(alt_up_pixel_buffer_dma_check_swap_buffers_status(my_pixel_buffer));

		vid_draw_circle(my_pixel_buffer, x1, y1, r, color1, 1);

		alt_up_pixel_buffer_dma_draw_box(my_pixel_buffer,x2-1,y2-1,x2+80,y2+10,0x0000,1);
		vid_print_string(my_pixel_buffer, x2, y2, color2, cour10_font, "visuale.ru");
		//Swap buffers and clear
		alt_up_pixel_buffer_dma_swap_buffers(my_pixel_buffer);
		while(alt_up_pixel_buffer_dma_check_swap_buffers_status(my_pixel_buffer));

		if(x2>320)dx=-1;
		if(x2<2)dx=1;
		if(y2>290)dy=-1;
		if(y2<2)dy=1;
		x2=x2+dx;
		y2=y2+dy;
		color2++;

		/*for(unsigned char u=0; u<255; u++)
			{
			memPoint1 = memPoint2;
			for(unsigned int i=0; i<65535; i++)
				 {
				 *memPoint1=u+i;
				 memPoint1++;
				 }
		}*/
	}

}
