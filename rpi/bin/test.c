#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <tlc5940.h>
#include <cube.h>
#include <math.h>


int main () {
  if (wiringPiSetup () == -1)
         exit (1) ;

  if(!piThreadCreate (driveGSCLK_BLANK))
      printf ("driveGSCLK_BLANK thread didn't start \n");


  gsArray_t gsBuf [NUM_CHIP];
  int i,j,k;

  setupTLC5940();
  initTLC5940();

  delay(1000);

  if(!piThreadCreate (refreshCube))
      printf ("refreshCube thread didn't start \n");


  //for(;;);

  for(;;) {
    update_TLC_Cube_Element(1,6,0, 0xfff);
    update_TLC_Cube_Element(1,4,0, 0x0);

    delay(1000);

    update_TLC_Cube_Element(1,6,0, 0x0);
    update_TLC_Cube_Element(1,4,0, 0xfff);

    delay(1000);
  }
}

