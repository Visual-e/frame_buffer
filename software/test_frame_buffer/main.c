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

	alt_up_pixel_buffer_dma_dev* my_pixel_buffer;
	// Use the name of your pixel buffer DMA core
	my_pixel_buffer = alt_up_pixel_buffer_dma_open_dev(
				"/dev/video_pixel_buffer_dma_0");

	// Check for error and output to the console
	if ( my_pixel_buffer == NULL)
	  printf ("Error: could not open pixel buffer device \n");
	else
	  printf ("Opened pixel buffer device \n");

	//Очистили основной буфер экрана
	alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);
	//Очистили дополнительный буфер экрана
	alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,1);

	//Инициализация переменных
	color1=0;
	color2=0;
	x1=200;
	y1=150;
	r=30;
	x2=10;
	y2=10;
	dx=1;
	dy=1;

	while(1)
		{
		//Рисуем окружность в дополнительном буфере
		vid_draw_circle(my_pixel_buffer, x1, y1, r, color1, 1);

		//Рисуем прямоугольник для надписи в дополнительном буфере
		alt_up_pixel_buffer_dma_draw_box(my_pixel_buffer,x2-1,y2-1,x2+80,y2+10,0x0000,1);
		//Выводим надпись visuale.ru
		vid_print_string(my_pixel_buffer, x2, y2, color2, cour10_font, "visuale.ru");

		//Swap buffers and clear---------------------------------------------------------
		alt_up_pixel_buffer_dma_swap_buffers(my_pixel_buffer);
		while(alt_up_pixel_buffer_dma_check_swap_buffers_status(my_pixel_buffer));

		//Рисуем окружность в основном буфере
		vid_draw_circle(my_pixel_buffer, x1, y1, r, color1, 1);

		//Рисуем прямоугольник для надписи в основном буфере
		alt_up_pixel_buffer_dma_draw_box(my_pixel_buffer,x2-1,y2-1,x2+80,y2+10,0x0000,1);
		//Выводим надпись visuale.ru
		vid_print_string(my_pixel_buffer, x2, y2, color2, cour10_font, "visuale.ru");

		//Swap buffers and clear---------------------------------------------------------
		alt_up_pixel_buffer_dma_swap_buffers(my_pixel_buffer);
		while(alt_up_pixel_buffer_dma_check_swap_buffers_status(my_pixel_buffer));

		//Вычислили новые координаты и цвета
		color1 = rand()%65535;
		color2++;
		x1 = abs(rand()%400);
		y1 = abs(rand()%300);
		r = abs(rand()%30);
		if(x2>320)dx=-1;
		if(x2<2)dx=1;
		if(y2>290)dy=-1;
		if(y2<2)dy=1;
		x2=x2+dx;
		y2=y2+dy;
		color2++;
	}

}