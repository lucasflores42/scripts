#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "pointers.h"



//#define mobil
#define prob_mobil 0.00
#define EPSILON (1e-8)
#define c 1
//#define N_viz 10

const int tmax=1000;
unsigned long rseed;
const gsl_rng_type * T;
gsl_rng * rand_vec;
double measure_time = 1;




void set_gsl_rng(void)
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



/********************************************************************
***                          Main                                 ***
********************************************************************/
int main(int argc, char *argv[])
{	
	//gera arquivo
	char filename[200];
	char REDE_ATUAL_NAME[50];	
	FILE *fp;		
  	int t=0;	
	double payoff[5], gama, delta,r;//,Px,Py;
 	double Emedia = 0;
 	double Emedia2 = 0;		
 	double Hmedia = 0;
 	double Hmedia2 = 0;
 		
	set_gsl_rng();    
	int N= 1000;
	int state[N],viz[N][3];


	fp=fopen(filename,"w");
	int n,x;
	for(n=0; n < N; n++)
	{	
		double temp = gsl_rng_uniform(rand_vec);
		if (temp < 0.5){state[n] = 1;}
		else{state[n] = -1;} 
	}
	
	for(x=0;x<N;x++)
	{	
		viz[x][0] = x; // autointeraçao
		viz[x][1] = x - 1; //vizinho acima de i
		viz[x][2] = x + 1; //vizinho à direita de i
				
		/****************************************************
		***                     C.C.P.                    ***
		****************************************************/
		if(x == 0){ viz[x][1] = N - 1;}
		if(x == N - 1){ viz[x][2] = 0;}
	}
	double Temperatura = 1.;
	double J=1.;
	//MCS		
	for(t=1; t < tmax; t++)
	{	
		
		for(n=0; n<N; n++)
		{		
			int i,j;


			double beta=1./Temperatura;
			double Ei = 0.;
			double Ef = 0.;	
			
			x = (int) N*gsl_rng_uniform(rand_vec); 
			
			Ei = -J*(state[x]*state[viz[x][1]] + state[x]*state[viz[x][2]]);
				
			state[x] = (-1)*state[x];

			Ef = -J*(state[x]*state[viz[x][1]] + state[x]*state[viz[x][2]]);

			double deltaE = Ef - Ei; 		//printf("%lf \n", deltaE);
			double l = gsl_rng_uniform(rand_vec);
			double p = exp(-beta*deltaE);

			
			if(deltaE > 0 && l > p)
			//if(Py > Px)
			{      
				state[x] = (-1)*state[x];

			}

			Emedia = -J*(state[x]*state[viz[x][1]] + state[x]*state[viz[x][2]]);			//printf("%lf %lf\n", Emedia, Emedia2);


			Hmedia += Emedia;
			Hmedia2 += Emedia*Emedia;	
			//printf("%d %lf %lf \n",t,Hmedia, Hmedia2);
			
  		}	



	

	}//MCS

	Hmedia = Hmedia/(2*tmax*N);
	Hmedia2 = Hmedia2/(2*tmax*N);		
	double C = (1./(Temperatura*Temperatura))*(Hmedia2 - (Hmedia*Hmedia));
	
	printf("%lf %lf %lf\n",Hmedia, Hmedia2, C);
fclose(fp);

return 0;


} //main
