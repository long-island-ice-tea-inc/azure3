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
 -- Header Name       : cube.h
 -- Author            : manu
 -- Description       : This file contains the mapping from XYZ -> TCL array,
                        as well as the cube refresh functions.
 --------------------------------------------------------------------------
*/

#ifndef CUBE_H_
#define CUBE_H_

#include <wiringPi.h>
#include "tlc5940.h"

#define CUBE_X  8
#define CUBE_Y  8
#define CUBE_Z  8

#define CUBE_REFRESH_DELAY_MS  2

//Structure of TLC Array
typedef struct  TLC_plane {
  gsArray_t  chip[NUM_CHIP];
}  TLC_plane_t;

typedef struct  TLC_Cube  {
  TLC_plane_t  plane[CUBE_Z];
}  TLC_Cube_t;


//Structure of Graphics Cube
typedef struct line     {
  unsigned short led[CUBE_X];
}  line_t;

typedef struct plane    {
 line_t line[CUBE_Y];
}  plane_t;

typedef struct  cube    {
  plane_t plane[CUBE_Z];
} cube_t;


//Function to update TLC_Cube
void update_TLC_Cube_Element(unsigned char x, unsigned char y, unsigned char z, short val);

//Thread to refresh the TLC PWM with TLC_Cube contents
PI_THREAD (refreshCube); 

#endif /* CUBE_H_ */
