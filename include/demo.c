#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ezgfx.h"

#define W 600
#define H 448
#define C 16


void waitmouse(void){
   ezClearMouseBuf();
   do {} while(ezCheckMouse()<1);
}


int main(void){
   int i,j,x,y;
   char s[100];
   
   if (!ezOpenWin(W,H,"ezgfx demo")){
      ezErrorMsg();
      return 1;
   }

   ezChangeWindowTitle("ezgfx demo v1.0  -  written by adlroc in 22/04/00  -  Press a mouse key to begin!");
   waitmouse();
   
   ezChangeWindowTitle("ezgfx demo  -  ezPlot function");
   for (i=0; i<30000; i++) ezPlot(rand()%W, rand()%H, rand()%C);
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();
   
   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  ezLine function");
   for (i=0; i<10000; i++) ezLine(rand()%W, rand()%H, rand()%W, rand()%H, rand()%C);
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();

   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  ezBox function");
   for (i=0; i<10000; i++) ezBox(rand()%W, rand()%H, rand()%W, rand()%H, rand()%C);
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();

   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  ezBoxF function");
   for (i=0; i<1000; i++) ezBoxF(rand()%W, rand()%H, rand()%W, rand()%H, rand()%C);
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();

   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  ezEllipse function");
   for (i=0; i<2000; i++) ezEllipse(rand()%W, rand()%H, rand()%(W/2), rand()%(H/2), rand()%C);
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();

   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  ezEllipseF function");
   for (i=0; i<1000; i++) ezEllipseF(rand()%W, rand()%H, rand()%(W/2), rand()%(H/2), rand()%C);
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();

   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  ezText function");
   for (i=0; i<200; i++) ezText(rand()%W, rand()%H, rand()%C,"ezText()");
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();

   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  Colors");
   for (i=0; i<C; i++) {
      ezBoxF(0,i*(H/C),W-1,(i+1)*(H/C),i);
      sprintf(s,"Color %d",i);
      ezText((W-strlen(s)*8)/2,i*(H/C)+H/C/2+5,(i+1)%2,s);
   }
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();

   ezCls();
   for (i=0; i<50; i++) ezEllipseF(rand()%(W/10),rand()%(H/10),rand()%10,rand()%10,rand()%C);
   ezFlush();
   ezChangeWindowTitle("ezgfx demo  -  ezCopyArea function : press a mouse button to copy");
   waitmouse();
   for (i=0; i<10; i++)
      for (j=0; j<10; j++)
         if (i || j) ezCopyArea(0,0,W/10,H/10,i*W/10,j*H/10);
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();


   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  ezCheckKey function");
   ezText(20,50,1,"Press a key from the keyboard:");
   ezClearKeyBuf();
   do {} while((i=ezCheckKey())==0);
   if (i>31)
      sprintf(s,"You pressed the %c key",i);
   else
      sprintf(s,"You pressed the key with code %d",i);
   ezText(20,70,4,s);
   ezChangeWindowTitle("Press a mouse key to continue");
   waitmouse();
   
   ezCls();
   ezChangeWindowTitle("ezgfx demo  -  ezCheckMouse function");
   ezText(20,50,1,"Press the mouse buttons and drag the mouse");
   ezText(20,65,1,"Press Enter to finish");
   ezClearKeyBuf();
   x=y=j=0;
   do {
      i=ezCheckMouse();
      if (i>0) {
         j=i;
         x=ezMouseX;
         y=ezMouseY;
      }
      if (i<0) j=0;
      if (j) {
         ezLine(x,y,ezMouseX,ezMouseY,j+2);
         x=ezMouseX;
         y=ezMouseY;
      }
   } while(ezCheckKey()!=13);

   ezClose();
   puts("Goodbye!");
   return 0;
}


