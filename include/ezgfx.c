
/*******************************************************
*                                                      *
*    ezgfx v1.0  -  written in 21/04/2000 by adlroc    *
*                                                      *
*******************************************************/


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "ezgfx.h"

#define NColors 16

int ezMouseX=0, ezMouseY=0;
static Display *mydisplay;
static Window mywindow;
static GC mygc;
static int myscreen;
static int ezWinOpen=0;  
static int ezColor[16];
static char wnm[100];
static int lasterrorcode=0;
static char *colorname[] = {"Black", "White", "Gray", "Red", "Green", "Blue", "Yellow", "Brown", "Cyan", "Orange", "Gold", "Salmon", "Navy", "Pink", "Orchid", "MediumSeaGreen"};
static char *errorstr[] = {"Ok", "Unable to open X Display", "Unable to open window", "Can't create GraphicContext"};
 

int ezOpenWin(int Width, int Height, char *wname){
  int px, py, i;
  XColor mycolor, mycolor2;
  XSizeHints myhint;
  XSetWindowAttributes myattributes;
  Colormap mycmap;
  unsigned long myforeground, mybackground;

  if ((mydisplay = XOpenDisplay(NULL)) == NULL) {
     lasterrorcode=1;
     return 0;
  }
  myscreen = DefaultScreen(mydisplay);
  mycmap = DefaultColormap(mydisplay,myscreen);
  px = (XDisplayWidth(mydisplay,myscreen)-Width)/2;
  py = (XDisplayHeight(mydisplay,myscreen)-Height)/2;
  if (px<0) px=0;
  if (py<0) py=0;
  mybackground = BlackPixel(mydisplay,myscreen);
  myforeground = WhitePixel(mydisplay,myscreen);

  if (DefaultDepth(mydisplay,myscreen)==1){
	for (i=0; i<NColors; i += 2) {
		ezColor[i] = mybackground;
		ezColor[i+1] = myforeground;
	}
  } else {
       for (i=0; i<NColors; i++) {
          if (!XAllocNamedColor(mydisplay, mycmap, colorname[i], &mycolor, &mycolor2))
	  	ezColor[i] = (i%2)?mybackground:myforeground;
	  else
		ezColor[i] = mycolor.pixel;
       }
  }		
  
  myhint.x = px; myhint.y = py;
  myhint.width = myhint.min_width = myhint.max_width = Width;
  myhint.height = myhint.min_height = myhint.max_height  = Height;
  myhint.flags = PPosition|PSize|PMinSize|PMaxSize;
  mywindow = XCreateSimpleWindow(mydisplay,DefaultRootWindow(mydisplay),myhint.x, myhint.y, myhint.width, myhint.height,5, mybackground, mybackground);
  if (!mywindow) {
	XCloseDisplay(mydisplay);
        lasterrorcode=2;
        return 0;
  }
 
  strncpy(wnm, wname, 99);
  wnm[99]=0;
  XSetStandardProperties(mydisplay, mywindow, wnm, wnm, None, NULL,
0, &myhint);
  myattributes.backing_store = Always;
  XChangeWindowAttributes(mydisplay,mywindow,CWBackingStore,&myattributes);  
  mygc = XCreateGC(mydisplay, mywindow, 0, 0);
  if (!mygc) {
     XCloseDisplay(mydisplay);
     XDestroyWindow(mydisplay, mywindow);
     lasterrorcode=3;
     return 0;
  }
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);
  
  XSelectInput(mydisplay, mywindow, ButtonPressMask|ButtonReleaseMask|ButtonMotionMask|KeyPressMask);
  XMapRaised(mydisplay, mywindow);
  XFlush(mydisplay);
  ezWinOpen=1;
  lasterrorcode=0;
  usleep(1);
  return 1;
}


int ezCheckKey(void){
   XEvent myevent;
   KeySym mykey;
   char txt[10];

   if (!ezWinOpen) return 0;
   usleep(1);
   if (!XCheckWindowEvent(mydisplay, mywindow, KeyPressMask, &myevent)){
   	return 0;
   }
   if (XLookupString(&myevent.xkey, txt, 10, &mykey, 0)==0) return 0;
   return txt[0];
}


void ezClearKeyBuf(void){
   XEvent myevent;

   if (!ezWinOpen) return;
   usleep(1);
   while (XCheckWindowEvent(mydisplay, mywindow, KeyPressMask, &myevent));
}


int ezCheckMouse(void){
   XEvent myevent;
 
   if (!ezWinOpen) return 0;
   usleep(1);
   if (!XCheckWindowEvent(mydisplay, mywindow, ButtonPressMask|ButtonReleaseMask|ButtonMotionMask, &myevent)){
   	return 0;
   }
   ezMouseX=myevent.xbutton.x;
   ezMouseY=myevent.xbutton.y;
   if (myevent.type==ButtonPress)
	return myevent.xbutton.button;
   else if (myevent.type==ButtonRelease)
   	return -(myevent.xbutton.button);
   else while (XCheckWindowEvent(mydisplay, mywindow,ButtonMotionMask, &myevent)){
   	ezMouseX=myevent.xbutton.x;
   	ezMouseY=myevent.xbutton.y;
   }
   return 0;
}


void ezClearMouseBuf(void){
   XEvent myevent;
 
   if (!ezWinOpen) return;
   usleep(1);
   while (XCheckWindowEvent(mydisplay, mywindow, ButtonPressMask|ButtonReleaseMask|ButtonMotionMask, &myevent));
}


void ezChangeWindowTitle(char *wname){
  XSizeHints myhint;
  long l;

  if (!ezWinOpen) return;  
  myhint.flags=0;
  usleep(1);
  XGetWMNormalHints(mydisplay, mywindow, &myhint, &l);
  XSetStandardProperties(mydisplay, mywindow, wname, wnm, None, NULL,0, &myhint);
  XFlush(mydisplay);
  usleep(1);
}
		

void ezPlot(int x, int y, int c){
  if (!ezWinOpen) return;  
  XSetForeground(mydisplay,mygc, ezColor[c%NColors]);
  XDrawPoint(mydisplay,mywindow,mygc,x,y);
}


void ezLine(int x1, int y1, int x2, int y2, int c){
  if (!ezWinOpen) return;  
  XSetForeground(mydisplay,mygc, ezColor[c%NColors]);
  XDrawLine(mydisplay, mywindow, mygc, x1, y1, x2, y2);
} 


void ezCls(void){
    if (!ezWinOpen) return;  
    XClearWindow(mydisplay,mywindow);
    XFlush(mydisplay);
}


void ezBox(int x1, int y1, int x2, int y2, int c){
    int sx,sy,wx,wy;
    if (!ezWinOpen) return;
    XSetForeground(mydisplay,mygc, ezColor[c%NColors]);
    if (x1<x2) {
	sx=x1;
	wx=x2-x1;
    } else {
	sx=x2;
	wx=x1-x2;
    }
    if (y1<y2) {
	sy=y1;
        wy=y2-y1;
    } else {
        sy=y2;
        wy=y1-y2;
    }
    XDrawRectangle(mydisplay,mywindow,mygc,sx,sy,wx+1,wy+1);
}
	

void ezBoxF(int x1, int y1, int x2, int y2, int c){
    int sx,sy,wx,wy;
    if (!ezWinOpen) return;
    XSetForeground(mydisplay,mygc, ezColor[c%NColors]);
    if (x1<x2) {
	sx=x1;
	wx=x2-x1;
    } else {
	sx=x2;
	wx=x1-x2;
    }
    if (y1<y2) {
	sy=y1;
        wy=y2-y1;
    } else {
        sy=y2;
        wy=y1-y2;
    }
    XFillRectangle(mydisplay,mywindow,mygc,sx,sy,wx+1,wy+1);
}


void ezEllipse(int x, int y, int rx, int ry, int c){
  if (!ezWinOpen) return;  
  XSetForeground(mydisplay,mygc, ezColor[c%NColors]);
  XDrawArc(mydisplay,mywindow,mygc,x-rx,y-ry,rx*2,ry*2,0,23040);
} 


void ezEllipseF(int x, int y, int rx, int ry, int c){
  if (!ezWinOpen) return;  
  XSetForeground(mydisplay,mygc, ezColor[c%NColors]);
  XFillArc(mydisplay,mywindow,mygc,x-rx,y-ry,rx*2,ry*2,0,23040);
} 


void ezCopyArea(int x1, int y1, int x2, int y2, int destx, int desty){
    int sx,sy,wx,wy;
    if (!ezWinOpen) return;
    if (x1<x2) {
	sx=x1;
	wx=x2-x1;
    } else {
	sx=x2;
	wx=x1-x2;
    }
    if (y1<y2) {
	sy=y1;
        wy=y2-y1;
    } else {
        sy=y2;
        wy=y1-y2;
    }
    XCopyArea(mydisplay, mywindow, mywindow, mygc, sx, sy, wx+1, wy+1, destx, desty);
}


void ezText(int x, int y, int c, char *text){
  if (!ezWinOpen) return;  
  XSetForeground(mydisplay,mygc, ezColor[c%NColors]);
  XDrawString(mydisplay,mywindow,mygc,x,y,text,strlen(text));
} 


void ezFlush(void){
    if (!ezWinOpen) return;
    XFlush(mydisplay);
}


void ezClose(void){
  if (!ezWinOpen) return;
  ezWinOpen=0;
  XFreeGC(mydisplay, mygc);
  XDestroyWindow(mydisplay, mywindow);
  XCloseDisplay(mydisplay);
  usleep(1);
}


void ezErrorMsg(void){
   if (lasterrorcode==0) return;
   fprintf(stderr,"Error: %s\n",errorstr[lasterrorcode]);
}


/*   No comments at all because the code is self-explaining :)   */


