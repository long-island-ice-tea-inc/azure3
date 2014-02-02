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
 -- File Name         : tlc4950.c
 -- Author            : Manu
 -- Description       :
 --------------------------------------------------------------------------
*/
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <tlc5940.h>

void setupTLC5940() {

    //Setup GPCLK0 to drive GSCLK of TLC5940
    pinMode (GSCLK, GPIO_CLOCK) ;
    gpioClockSet (GSCLK, GSCLK_FREQ); //2.4MHz ~= PLLmax 19.2MHz/8
    //pinMode (GSCLK, OUTPUT) ;

    //Setup the GPIO pins to interface TLC5940
    pinMode (VPRG, OUTPUT) ;
    pinMode (XLAT, OUTPUT) ;
    pinMode (SIN, OUTPUT) ;
    pinMode (SCLK, OUTPUT) ;
    pinMode (BLANK, OUTPUT) ;
}

void initTLC5940 () {
    clrSCLK();
    clrXLAT();
    dotCorrectTLC5940();
}

void dotCorrectTLC5940 () {
    int i;

    clrBLANK();
    //setVPRG();
    digitalWrite (0, HIGH) ;
    clrSIN();

    for(i=0; i < NUM_CHANNELS*NUM_DCBITS*NUM_CHIP; i++){
        setSCLK();
        clrSCLK();
    }

    setXLAT();
    clrXLAT();

    FirstCycle = true;

    printf ("Finished Dot Correction \n");
}

void updateTLC5940 (gsArray_t (*gsBuffer)[NUM_CHIP]) {

    int dataCount;
    int chanCount;
    int chipCount;

    clrVPRG();

    for(chipCount=0; chipCount < NUM_CHIP; chipCount++) {
        for(chanCount=NUM_CHANNELS-1; chanCount >= 0; chanCount--) {
            //if(chipCount == 3)
            //printf("((*gsBuffer)[%d].chan[%d]): %x \n", chipCount, chanCount, ((*gsBuffer)[chipCount].chan[chanCount]));

            for(dataCount=NUM_GSBITS-1; dataCount >= 0; dataCount--) {
                //Shift out MSB
                if( (1 << (dataCount-1)) & ((*gsBuffer)[chipCount].chan[chanCount]) ) {
                    setSIN();
                    //printf("1");
                } else {
                    clrSIN();
                    //printf("0");
                }

                setSCLK();
                clrSCLK();
            }
            //printf("\n");
        }
    }

    //Pulse the XLAT
    setXLAT();
    clrXLAT();

    //First GS cycle after DC requires an additional SCLK pulse
    if(FirstCycle == true) {
        setSCLK();
        clrSCLK();
        FirstCycle = false;
        printf ("Applied Extra SCLK \n");
    }
}

PI_THREAD (driveGSCLK_BLANK) {

    int gsclkCount;

    printf ("Starting GSCLK Thread \n");

    for (;;) {
            //--for (gsclkCount=0; gsclkCount < NUM_GSCLK; gsclkCount++) {
            //--        setGSCLK();delay(1);
            //--        clrGSCLK();delay(1);
            //--}
            #ifndef BLANK_USE_NANO
                delay(BLANK_DELAY);
            #else
                nanosleep(0,500);
            #endif

            //Pulse the Blanking signal
            setBLANK();
            clrBLANK();
    }
} 

void setVPRG () {
    digitalWrite (VPRG, HIGH) ;
}

void clrVPRG () {
    digitalWrite (VPRG, LOW) ;
}

void setXLAT () {
    digitalWrite (XLAT, HIGH) ;
}

void clrXLAT () {
    digitalWrite (XLAT, LOW) ;
}

void setSIN () {
    digitalWrite (SIN, HIGH) ;
}

void clrSIN () {
    digitalWrite (SIN, LOW) ;
}

void setSCLK () {
    digitalWrite (SCLK, HIGH) ;
}

void clrSCLK () {
    digitalWrite (SCLK, LOW) ;
}

void setBLANK () {
    digitalWrite (BLANK, HIGH) ;
}

void clrBLANK () {
    digitalWrite (BLANK, LOW) ;
}

void setGSCLK () {
    digitalWrite (GSCLK, HIGH) ;
}

void clrGSCLK () {
    digitalWrite (GSCLK, LOW) ;
}
