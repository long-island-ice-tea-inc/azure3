/*
 --------------------------------------------------------------------------
   Azure Cube - Copyright (C) 2014 Long Island Ice Tea Inc.

   This file is part of Azure Cube.

   Azure Cube is free; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   Azure Cube is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.
 --------------------------------------------------------------------------
*/

/*
 --------------------------------------------------------------------------
 -- Project Code      : azure3
 -- File Name         : cube.c
 -- Author            : manu
 -- Description       : This file describes the cube refresh & mapping
                        functions.
 --------------------------------------------------------------------------
*/

#include "wiringPi.h"
#include "tlc5940.h"
#include "cube.h"

//Global Buffer to hold LED PWM data for the cube
static  TLC_Cube_t  cube_bffr;


PI_THREAD (refreshCube)  {
  int plane_num,line,led;

  plane_num = 0;

  for(;;) {

    updateTLC5940(cube_bffr.plane[plane_num].chip);

    //Add switch for plane here!!!!!!!!

    //delay(CUBE_REFRESH_DELAY_MS);

    if(plane_num == CUBE_Z-1)
      plane_num = 0;
    else
      plane_num++;
  }
}

void update_TLC_Cube_Element(unsigned char x, unsigned char y, unsigned char z, short val) {

  cube_bffr.plane[z].chip[y >> 1].chan[((y & 0x1) << 3) + x]  = val;

  return;
}
