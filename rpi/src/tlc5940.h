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
 -- Header Name       : tlc5940.h
 -- Author            : Manu
 -- Description       :
 --------------------------------------------------------------------------
*/

#ifndef tlc5940_H_
#define tlc5940_H_

#include <wiringPi.h>
#include <stdbool.h>

#define VPRG  0
#define XLAT  1
#define SIN   2
#define SCLK  3
#define BLANK 4
#define GSCLK 7

#define NUM_CHANNELS  16 
#define NUM_DCBITS    8
#define NUM_GSBITS    12
#define NUM_CHIP      4
#define NUM_GSCLK     4096

#define GSCLK_FREQ    2400000
#define BLANK_DELAY   1
//#define BLANK_USE_NANO

typedef struct gsArray  {
        short chan[NUM_CHANNELS];
} gsArray_t;

bool FirstCycle;

PI_THREAD (driveGSCLK_BLANK); 

void setupTLC5940 ();

void dotCorrectTLC5940 ();

void initTLC5940 ();

void updateTLC5940 ();

void setVPRG ();

void clrVPRG ();

void setXLAT ();

void clrXLAT ();

void setSIN ();

void clrSIN ();

void setSCLK ();

void clrSCLK ();

void setBLANK ();

void clrBLANK ();

void setGSCLK ();

void clrGSCLK ();

#endif /* tlc5940_H_ */
