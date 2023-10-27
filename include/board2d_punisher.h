
#include <stdlib.h>
#include <ctype.h>
#include "ezgfx.h"

#define xpage  600     /*  suggested window width/height  */
#define ypage  600

int symbol_size, border_size;
char *gfxbuf=NULL;


void waitmouse(void){
      ezClearMouseBuf();
      do {
      } while(ezCheckMouse()<1);
}

void init_board_2d(int lsize){
   int i;
   
   if (xpage<ypage)
      symbol_size = xpage/lsize;
   else
      symbol_size = ypage/lsize;  /* symbol size */
   if (symbol_size<1) symbol_size = 1;
   if (symbol_size>3) {
      border_size=1;
      symbol_size--;
   } else border_size=0;

   gfxbuf=(char *)malloc(lsize*lsize*sizeof(char));
   if (!gfxbuf){
      fprintf(stderr,"Error: no memory for buffer!\n");
      exit(1);
   }
   for (i=0; i<lsize*lsize; i++) gfxbuf[i]=127;

   if (!ezOpenWin(lsize*(symbol_size+border_size), lsize*(symbol_size+border_size), "Diffusion")){
      ezErrorMsg();
      exit(1);
   }
}


void dispose_board_2d(void){
   ezFlush();
   ezChangeWindowTitle("Press a mouse button to continue");
   do{} while ((!ezCheckMouse()) && (toupper(ezCheckKey())!='Q'));
   free(gfxbuf);
   ezClose();
}
void update_board_2d_act(int lsize, int *s, int *stemp){
 int i,j,x,y,c=0;

   for(i=0 ; i< lsize; ++i){
      for(j=0; j< lsize; ++j){
         switch (s[i*lsize+j]){
	 case  1: if (stemp[i*lsize+j]==1) c=5;
	   else c=4;
	   break;
            case -1: if (stemp[i*lsize+j]==-1)c=3; 
	   else c=6;
	      break;
            case  0: c=0; break;
         }
        /* if (gfxbuf[lsize*i+j]!=c) */
	   {
	      gfxbuf[lsize*i+j]=c;
	      x=(symbol_size+border_size)*j;
	      y=(symbol_size+border_size)*i;
	      ezBoxF(border_size+x,border_size+y,x+symbol_size,y+symbol_size,c);
	   }
     }
   }
   ezFlush();
}


void update_board_2d_punisher(int lsize, int *s, int tempo, int p){
   int i,j,x,y,c=0;
   
   char titulo[100];
   

	sprintf(titulo,"t = %d p= %d",tempo,p);
	ezChangeWindowTitle(titulo);
   for(i=0 ; i< lsize; ++i){
      for(j=0; j< lsize; ++j){
         switch (s[i*lsize+j]){
            case  1: c=5; break;
            case  0: c=3; break;
            case  2: c=4; break;
         }
        /* if (gfxbuf[lsize*i+j]!=c) */
	   {
	      gfxbuf[lsize*i+j]=c;
	      x=(symbol_size+border_size)*j;
	      y=(symbol_size+border_size)*i;
	      ezBoxF(border_size+x,border_size+y,x+symbol_size,y+symbol_size,c);
	   }
     }
   }
   ezFlush();
}

void update_board_2d_special(int lsize, int *s, int *payoff){
   int i,j,x,y,c=0;
      
   for(i=0 ; i< lsize; ++i){
     for(j=0; j< lsize; ++j){
       switch (s[i*lsize+j])
	 {
	 case  1: {
	   switch (payoff[i*lsize+j])
	     {
	     case 0: c=2; break;
	     case 1: c=1; break;
	     case 2: c=8; break;
	     case 3: c=5; break;
	     case 4: c=14; break;
	     }
	 } 
	   break;
	 case -1: {
	   switch (payoff[i*lsize+j])
	     {
	     case 0: c=3; break;
	     case 1: c=7; break;
	     case 2: c=11; break;
	     case 3: c=9; break;
	     case 4: c=10; break;
	     }
	   
	 } 
	   break;
	 case  0: c=0; break;
         }
       /* if (gfxbuf[lsize*i+j]!=c) */
       {
	 gfxbuf[lsize*i+j]=c;
	 x=(symbol_size+border_size)*j;
	 y=(symbol_size+border_size)*i;
	 ezBoxF(border_size+x,border_size+y,x+symbol_size,y+symbol_size,c);
       }
     }
   }
   ezFlush();
}


void update_site_2d(int lsize, int site){
   int i,j,x,y,c=0;

   i = site/lsize;
   j = site%lsize;
   c = 5; /*blue*/
   x=(symbol_size+border_size)*j;
   y=(symbol_size+border_size)*i;
   ezBoxF(border_size+x,border_size+y,x+symbol_size,y+symbol_size,c);	
   ezFlush();
/*   do{} while ((!ezCheckMouse()) && (toupper(ezCheckKey())!='N'));*/
}
