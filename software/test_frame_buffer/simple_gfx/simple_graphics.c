/***********************************************************************
 *                                                                     *
 * File:     simple_graphics.c                                         *
 *                                                                     *
 * Purpose:  Contains some useful graphics routines                    *
 *                                                                     *
 * Author:   N. Knight                                                 *
 *           Altera Corporation                                        *
 *           Apr 2006                                                  *
 **********************************************************************/

#include <string.h>
#include <io.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "simple_graphics.h"
#include "sys/alt_alarm.h"
#include "sys/alt_cache.h"
#include "system.h"

/******************************************************************
*  Function: vid_print_string
*
*  Purpose: Prints a string to the specified location of the screen
*           using the specified font and color.
*           Calls vid_print_char
*
******************************************************************/
int vid_print_string(alt_up_pixel_buffer_dma_dev* buffer, int horiz_offset, int vert_offset, int color, char *font, char string[])
{
  int i = 0;
  int original_horiz_offset;

  original_horiz_offset = horiz_offset;

  // Print until we hit the '\0' char.
  while (string[i]) {
    //Handle newline char here.
    if (string[i] == '\n') {
      horiz_offset = original_horiz_offset;
      vert_offset += 12;
      i++;
      continue;
    }
    // Lay down that character and increment our offsets.
    vid_print_char (buffer, horiz_offset, vert_offset, color, string[i], font);
    i++;
    horiz_offset += 8;
  }
  return (0);
}

/******************************************************************
*  Function: vid_print_char
*
*  Purpose: Prints a character to the specified location of the
*           screen using the specified font and color.
*
******************************************************************/

int vid_print_char (alt_up_pixel_buffer_dma_dev* buffer, int horiz_offset, int vert_offset, int color, char character, char *font)
{

  int i, j;

  char temp_char, char_row;

  // Convert the ASCII value to an array offset
  temp_char = (character - 0x20);

  //Each character is 8 pixels wide and 11 tall.
  for(i = 0; i < 11; i++) {
      char_row = *(font + (temp_char * FONT_10PT_ROW) + i);
    for (j = 0; j < 8; j++) {
      //If the font table says the pixel in this location is on for this character, then set it.
      if (char_row & (((unsigned char)0x80) >> j)) {
    	  alt_up_pixel_buffer_dma_draw(buffer, color, (horiz_offset + j), (vert_offset + i)); // plot the pixel
      }
    }
  }
  return(0);
}


/******************************************************************
*  Function: vid_draw_circle
*
*  Purpose: Draws a circle on the screen with the specified center
*  and radius.  Draws symetric circles only.  The fill parameter
*  tells the function whether or not to fill in the box.  1 = fill,
*  0 = do not fill.
*
******************************************************************/
int vid_draw_circle(alt_up_pixel_buffer_dma_dev* buffer, int Hcenter, int Vcenter, int radius, int color, char fill)
{
/*
  int x = 0;
  int y = radius;
  int p = (5 - radius*4)/4;

  // Start the circle with the top, bottom, left, and right pixels.
  vid_round_corner_points(Hcenter, Vcenter, x, y, 0, 0, color, fill, display);

  // Now start moving out from those points until the lines meet
  while (x < y) {
    x++;
    if (p < 0) {
      p += 2*x+1;
    } else {
      y--;
      p += 2*(x-y)+1;
    }
    vid_round_corner_points(Hcenter, Vcenter, x, y, 0, 0, color, fill, display);
  }
  return (0);
  */

    int x = radius;
    int y = 0;
    int xChange = 1 - (radius << 1);
    int yChange = 0;
    int radiusError = 0;
    int i;
    int p = 3 - 2 * radius;

    if (fill!=0)
    {
        while (x >= y)
        {
            for (i = Hcenter - x; i <= Hcenter + x; i++)
            {
            	alt_up_pixel_buffer_dma_draw(buffer, color, i, Vcenter + y);
            	alt_up_pixel_buffer_dma_draw(buffer, color, i, Vcenter - y);
            }
            for (i = Hcenter - y; i <= Hcenter + y; i++)
            {
            	alt_up_pixel_buffer_dma_draw(buffer, color, i, Vcenter + x);
            	alt_up_pixel_buffer_dma_draw(buffer, color, i, Vcenter - x);
            }

            y++;
            radiusError += yChange;
            yChange += 2;
            if (((radiusError << 1) + xChange) > 0)
            {
                x--;
                radiusError += xChange;
                xChange += 2;
            }
        }
    }
    else
    {//do not fill
        if (!radius) return 0;
        x = 0;
        y = radius;

        while (y >= x) // only formulate 1/8 of circle
        {
        	alt_up_pixel_buffer_dma_draw(buffer, color, Hcenter-x, Vcenter-y);
        	alt_up_pixel_buffer_dma_draw(buffer, color, Hcenter-y, Vcenter-x);
        	alt_up_pixel_buffer_dma_draw(buffer, color, Hcenter+y, Vcenter-x);
        	alt_up_pixel_buffer_dma_draw(buffer, color, Hcenter+x, Vcenter-y);
        	alt_up_pixel_buffer_dma_draw(buffer, color, Hcenter-x, Vcenter+y);
        	alt_up_pixel_buffer_dma_draw(buffer, color, Hcenter-y, Vcenter+x);
        	alt_up_pixel_buffer_dma_draw(buffer, color, Hcenter+y, Vcenter+x);
        	alt_up_pixel_buffer_dma_draw(buffer, color, Hcenter+x, Vcenter+y);

            if (p < 0) p += 4*x++ + 6;
                  else p += 4*(x++ - y--) + 10;
         }
    }


	return (0);

}

/******************************************************************
*  Data: cour10_font
*
*  Purpose: Data array that represents a 10-point courier font.
*
******************************************************************/
char cour10_font_array[95][11] =

 {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00, 0x00},
 {0x28, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x14, 0x14, 0x7E, 0x28, 0x28, 0x28, 0xFC, 0x50, 0x50, 0x00, 0x00},
 {0x10, 0x38, 0x44, 0x40, 0x38, 0x04, 0x44, 0x38, 0x10, 0x00, 0x00},
 {0x40, 0xA2, 0x44, 0x08, 0x10, 0x20, 0x44, 0x8A, 0x04, 0x00, 0x00},
 {0x30, 0x40, 0x40, 0x20, 0x60, 0x92, 0x94, 0x88, 0x76, 0x00, 0x00},
 {0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x08, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x08},
 {0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20},
 {0x00, 0x00, 0x6C, 0x38, 0xFE, 0x38, 0x6C, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x10, 0x10, 0x10, 0xFE, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00},
 {0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00},
 {0x38, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0x10, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00},
 {0x38, 0x44, 0x04, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7C, 0x00, 0x00},
 {0x38, 0x44, 0x04, 0x04, 0x18, 0x04, 0x04, 0x44, 0x38, 0x00, 0x00},
 {0x08, 0x18, 0x18, 0x28, 0x28, 0x48, 0x7C, 0x08, 0x1C, 0x00, 0x00},
 {0x7C, 0x40, 0x40, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38, 0x00, 0x00},
 {0x18, 0x20, 0x40, 0x40, 0x78, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0x7C, 0x44, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x00, 0x00},
 {0x38, 0x44, 0x44, 0x44, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0x38, 0x44, 0x44, 0x44, 0x3C, 0x04, 0x04, 0x08, 0x30, 0x00, 0x00},
 {0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00},
 {0x00, 0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x20, 0x10, 0x08, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00},
 {0x38, 0x44, 0x04, 0x04, 0x08, 0x10, 0x10, 0x00, 0x10, 0x00, 0x00},
 {0x3C, 0x42, 0x9A, 0xAA, 0xAA, 0xAA, 0x9C, 0x40, 0x38, 0x00, 0x00},
 {0x30, 0x10, 0x10, 0x28, 0x28, 0x44, 0x7C, 0x44, 0xEE, 0x00, 0x00},
 {0xFC, 0x42, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x42, 0xFC, 0x00, 0x00},
 {0x3C, 0x42, 0x80, 0x80, 0x80, 0x80, 0x80, 0x42, 0x3C, 0x00, 0x00},
 {0xF8, 0x44, 0x42, 0x42, 0x42, 0x42, 0x42, 0x44, 0xF8, 0x00, 0x00},
 {0xFE, 0x42, 0x40, 0x48, 0x78, 0x48, 0x40, 0x42, 0xFE, 0x00, 0x00},
 {0xFE, 0x42, 0x40, 0x48, 0x78, 0x48, 0x40, 0x40, 0xF0, 0x00, 0x00},
 {0x3C, 0x42, 0x80, 0x80, 0x80, 0x8E, 0x82, 0x42, 0x3C, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x44, 0xEE, 0x00, 0x00},
 {0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00},
 {0x1E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0xE6, 0x44, 0x48, 0x48, 0x50, 0x70, 0x48, 0x44, 0xE6, 0x00, 0x00},
 {0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0xFE, 0x00, 0x00},
 {0xC6, 0x44, 0x6C, 0x6C, 0x54, 0x54, 0x44, 0x44, 0xEE, 0x00, 0x00},
 {0xCE, 0x44, 0x64, 0x64, 0x54, 0x4C, 0x4C, 0x44, 0xE4, 0x00, 0x00},
 {0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00},
 {0xFC, 0x42, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40, 0xF0, 0x00, 0x00},
 {0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x36, 0x00},
 {0xFC, 0x42, 0x42, 0x42, 0x7C, 0x48, 0x48, 0x44, 0xE6, 0x00, 0x00},
 {0x7C, 0x82, 0x80, 0x80, 0x7C, 0x02, 0x02, 0x82, 0x7C, 0x00, 0x00},
 {0xFE, 0x92, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x44, 0x28, 0x28, 0x28, 0x10, 0x10, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x44, 0x54, 0x54, 0x54, 0x28, 0x28, 0x00, 0x00},
 {0xEE, 0x44, 0x28, 0x28, 0x10, 0x28, 0x28, 0x44, 0xEE, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00},
 {0xFE, 0x84, 0x08, 0x08, 0x10, 0x20, 0x20, 0x42, 0xFE, 0x00, 0x00},
 {0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00, 0x00},
 {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00},
 {0x1C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1C, 0x00, 0x00},
 {0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00},
 {0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x78, 0x04, 0x7C, 0x84, 0x84, 0x7A, 0x00, 0x00},
 {0xC0, 0x40, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x42, 0xFC, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x82, 0x80, 0x80, 0x82, 0x7C, 0x00, 0x00},
 {0x0C, 0x04, 0x04, 0x7C, 0x84, 0x84, 0x84, 0x84, 0x7E, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x82, 0xFE, 0x80, 0x82, 0x7C, 0x00, 0x00},
 {0x30, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x40, 0x40, 0xF0, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7E, 0x84, 0x84, 0x84, 0x7C, 0x04, 0x04, 0x78},
 {0xC0, 0x40, 0x40, 0x58, 0x64, 0x44, 0x44, 0x44, 0xEE, 0x00, 0x00},
 {0x08, 0x00, 0x00, 0x38, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00},
 {0x08, 0x00, 0x00, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x70},
 {0xC0, 0x40, 0x40, 0x4C, 0x48, 0x50, 0x70, 0x48, 0xC6, 0x00, 0x00},
 {0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xE8, 0x54, 0x54, 0x54, 0x54, 0xD6, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xD8, 0x64, 0x44, 0x44, 0x44, 0xEE, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x82, 0x82, 0x82, 0x82, 0x7C, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xFC, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x40, 0xE0},
 {0x00, 0x00, 0x00, 0x7E, 0x84, 0x84, 0x84, 0x7C, 0x04, 0x0E, 0x00},
 {0x00, 0x00, 0x00, 0xEC, 0x32, 0x20, 0x20, 0x20, 0xF8, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x82, 0x70, 0x0C, 0x82, 0x7C, 0x00, 0x00},
 {0x00, 0x20, 0x20, 0x78, 0x20, 0x20, 0x20, 0x24, 0x18, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xCC, 0x44, 0x44, 0x44, 0x4C, 0x36, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xEE, 0x44, 0x44, 0x28, 0x28, 0x10, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xEE, 0x44, 0x54, 0x54, 0x28, 0x28, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xEE, 0x44, 0x38, 0x38, 0x44, 0xEE, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xEE, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x60},
 {0x00, 0x00, 0x00, 0xFC, 0x88, 0x10, 0x20, 0x44, 0xFC, 0x00, 0x00},
 {0x0C, 0x10, 0x10, 0x10, 0x10, 0x60, 0x10, 0x10, 0x10, 0x10, 0x0C},
 {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10},
 {0x60, 0x10, 0x10, 0x10, 0x10, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x60},
 {0x00, 0x00, 0x62, 0x92, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};

//Pointer to our font table
char* cour10_font = &cour10_font_array[0][0];