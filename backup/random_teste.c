#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "pointers.h"
//#include "redes.h"

//#define DEBUG
unsigned long rseed;
const gsl_rng_type * T;
gsl_rng * rand_vec;
double measure_time = 1;

void set_gsl_rng(void) // gsl stuf
{
#ifdef DEBUG
	rseed=422;
#else
	rseed=time(NULL);
#endif
  
	gsl_rng_env_setup();
	T    = gsl_rng_default;
	rand_vec = gsl_rng_alloc (T);
	gsl_rng_set (rand_vec, rseed);

  return;
}

void main ()
{
	int G=5;
	long int N  = 100;

	set_gsl_rng(); 	
	int x,a,b,y,i,j,k,t;
	int viz[N][G],state[N];
	int count;


	for(x=0;x<N;x++) // rede quadrada
	{	
		state[x] = x + 1;
		viz[x][0] = x; // autointeraçao
		viz[x][1] = 10; //vizinho acima de i
		viz[x][2] = 10; //vizinho à direita de i
		viz[x][3] = 10; //vizinho abaixo sito de i
		viz[x][4] = 10; //vizinho à esquerda i
				
		//printf("%d %d %d %d %d %d %d\n",viz[x][0],viz[x][1],viz[x][2],viz[x][3],viz[x][4],viz[x][G],viz[x][6]);
	}
	

	for(y=1;y<G;y++)
	{	

		for(x=0;x<N;x++)
		{
			state[x] = x + 1;	
		}

		t = 1;
		//x = 0;

		do{
	
			int l;
			l = (int) N*gsl_rng_uniform(rand_vec); 
			x = (int) N*gsl_rng_uniform(rand_vec); 

			for(j=1;j<G;j++) // conta se um sitio x tem 2 vizinhos iguais
			{
				if(viz[x][j] == l && y != j)
				{
					//printf("t=%d x=%d y=%d l=%d viz[x][y]=%d\n",t,x,y,l,viz[x][y]);
					l = x;
					break;
				}
			}
			
			if(state[x] != 0 && state[l] != 0 && l != x)	//state[0] = 1
			{
				viz[x][y] = l; 
				viz[l][y] = x;
				
				state[l] = 0;
				state[x] = 0;

				//printf("t=%d x=%d y=%d l=%d viz[x][y]=%d\n",t,x,y,l,viz[x][y]);					

				t = t + 1;
					
			}				


		}while(t<=N/2.);
	}
	for(x=0;x<N;x++)
	{
		printf("%d %d %d %d %d \n",viz[x][0],viz[x][1],viz[x][2],viz[x][3],viz[x][4]);
	}

	return;		
}
