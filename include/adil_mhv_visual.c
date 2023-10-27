#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <mc.h> 
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#ifdef USEGFX
#include<X11/Xlib.h>
#include <board2d_punisher.h>
#endif

#define L          50        // tamanho da população = L*L
#define N_viz      4
#define EPSILON    (1e-8)
//#define GNUPLOT    //se GNUPLOT estiver definido matrizes serao plotadas
//#define densidade	
#define repeticoes 1

#define c          1.0
#define K          0.1//0.0001

const int tmax=100000;

//long int state [L*L]; // estado do sitio, 0 = Cooperator, 1 = Defector(criminal) e 2 = Punisher  %ld
// long int viz [L*L][4]; // matriz de vizinhos [sitio] [posição_do_vizinho]

const int L2=L*L;

unsigned long rseed;
const gsl_rng_type * T;
gsl_rng * rand_vec;

double measure_time = 1;

/*************************************************************************************
 *  Pseudo Random numbers
 *************************************************************************************/
void set_gsl_rng(void)
{
#ifdef DEBUG
	rseed=422;//441;
#else
	rseed=time(NULL);
#endif
  
	gsl_rng_env_setup();
	T    = gsl_rng_default;
	rand_vec = gsl_rng_alloc (T);
	gsl_rng_set (rand_vec, rseed);

  return;
}

/*************************************************************************************
 *  Find densities
 *************************************************************************************/
void count_states(int *NC, int *NP, int *ND, int *state)
{
	int k; 
	
	*NC = 0;
	*ND = 0;
	*NP = 0;
	for(k=0;k<L2;k++)
	{
		if(state[k] == 1)
			*NC=*NC+1;
		else
		{	
			if(state[k] == 2)	
				*NP=*NP+1;
			else // if(state[k] == 0)
				*ND=*ND+1;
		}
		
		
	}	
	
	
	
	
	
	return; 
}

/*************************************************************************************
 *  Calculate payoffs
 *************************************************************************************/
//void f (double *payoff,int state[1], int viz[1][5], int sitio,double r, double gama )
void f (double *payoff,int *state, int viz[1][5], int sitio, double r, double gama )
{
	int i=0;//,j=0;

	double nd = 0;
	double nc = 0;
	double np = 0;


	//printf("%lf %lf %lf\n",nc,nd,np);
	for(i=0;i<5;i++) 
	{
		if(state[viz[sitio][i]]==0) 
			nd = nd+1; // nc sitio x		
	  	else
		{	
			if(state[viz[sitio][i]]==2) 
				np = np+1; 	
			else //		if(state[viz[sitio][i]]==1) 
				nc = nc+1; 	
	  	}
	}
	/*//grupo de 2 (n: numero de vizinhos)
	payoff[1] = (1./(2))*r*c* (np+nc) + 4*((r/2.) - COST);
	payoff[2] = (1./(2))*r*c* (np+nc) + 4*((r/2.) - COST) - gama*nd;
	payoff[0] = (1./(2))*r*c* (np+nc) - gama*np;*/

	//grupo de 5 (n: numero total)
	payoff[1] = (1./(N_viz+1))*r*c* (np+nc) - c;
	payoff[2] = (1./(N_viz+1))*r*c* (np+nc) - c -gama*nd;
	payoff[0] = (1./(N_viz+1))*r*c* (np+nc) - gama*np;

	/*//grupo de 5 (n: numero de vizinhos)
	payoff[1] = (1./(N_viz+1)) *r*c* (np+nc) + r*c/5. - c;
	payoff[2] = (1./(N_viz+1)) *r*c* (np+nc) - c - gama*nd;
	payoff[0] = (1./(N_viz+1)) *r*c* (np+nc) - gama*np;*/

	
}


/*************************************************************************************
 *  Main program
 *************************************************************************************/
int main(int argc, char *argv[])
{
	char filename[200];
	FILE *fp;
	
	double gama, r;
	int i,t,p,x,y,init_conf;
	int state [L*L];
	int viz [L*L][5];
	int NC; // numero de Cooperadores
	int ND; // numero de Dfectors (criminals)
	int NP; // numero de punhishers
	int vizinho,vizinho1;//,vizinho2;
	
	unsigned long left[L2],right[L2],up[L2],down[L2];
	//int flag = 0; // contador para printar estados intermediários

	double temp;
	double payoff[3]; // matriz 3x3, pois há 3 estratégias
	double Px,Py;//,Pz; // payoff do sitio i / vizinho do sitio i
	double Wxy; // probabilidade do sitio i assumir o estado de seu vizinho
  
    //unsigned long int seed = time(NULL); 
    //    srand((unsigned)seed);   
	if (argc!=3)
		{
			printf("O programa precisa de 2 argumentos: r e gama\n");
			exit(1);
		}
	r=atof(argv[1]);
	gama=atof(argv[2]);

	set_gsl_rng();
	
	//printf("%s %s  %f\n\n",argv[0],argv[1],M);
	
//	sprintf(filename,"dados_r%f_g%f_seed%ld.txt",r,gama,seed);
	sprintf(filename,"dados_r%f_g%f_K_%f_seed%ld.txt",r,gama,K,rseed);
	fp=fopen(filename,"w");

#ifdef USEGFX
	init_board_2d(L);
	waitmouse();
#endif		
	
	neighbours_2d(right,left,up,down,L);	
	for(i=0; i < L2; i++)
	{
		viz[i][0] = i;     // autointeraçao
		viz[i][1] = up[i]; 
		viz[i][2] = right[i]; 
		viz[i][3] = down[i]; 
		viz[i][4] = left[i];
	}


//----------- "SORTEIO" DOS ESTADOS DOS SITIOS (ORDIN, CRIM, PUNISH) -------------------
	for(init_conf=0;init_conf<repeticoes;init_conf++)
	{
		measure_time = 1;

		for(i=0; i< L2; ++i)
		{
			/*double temp = gsl_rng_uniform(rand_vec);
			if( temp < 1./3) //0.5) 
				state[i] = 0;
			else 
			{
				if( temp < 2./3)//0.75)
					state[i]  = 1;
				else state[i] = 2;
			}	
			*/
		state[i]=0;
		
		if (
			(i==(L2+L)/2+L-1)||  (i==(L2+L)/2 +L) ||  (i==(L2+L)/2+L+1) || //punisher
			(i==(L2+L)/2 -1) ||  (i==(L2+L)/2)    ||  (i==(L2+L)/2 +1) ||  //punisher
			(i==(L2+L)/2-L-1)||  (i==(L2+L)/2 -L) ||  (i==(L2+L)/2-L+1)    //punisher			
			)
			state[i] = 2; 
			
		if (
				(i==(L2+L)/2 + 2*L -2) || (i==(L2+L)/2 + 2*L-1)||  (i==(L2+L)/2 +2*L) ||  (i==(L2+L)/2+2*L+1) ||(i==(L2+L)/2+2*L+2) ||
				(i==(L2+L)/2 +   L -2) || (i==(L2+L)/2 +   L+2) ||
				(i==(L2+L)/2       -2) || (i==(L2+L)/2 +2) 	 ||
				(i==(L2+L)/2 -   L -2) || (i==(L2+L)/2 -   L+2) ||
				(i==(L2+L)/2 - 2*L -2) || (i==(L2+L)/2- 2*L-1)||  (i==(L2+L)/2 -2*L) ||  (i==(L2+L)/2-2*L+1) ||(i==(L2+L)/2-2*L+2)
				)
				state[i]=1;
				
				
		
		}
#ifdef USEGFX
		//printf("ALO\n");fflush(stdout);
		update_board_2d_punisher(L,state,0,0);
		//printf("ALO 1\n");fflush(stdout);
		//waitmouse();
#endif	
		count_states(&NC,&NP,&ND,state);
		fprintf(fp,"%f %lf %lf %lf\n", 0.01, (double)NC/L2, (double)ND/L2, (double)NP/L2);
	
//--------------------------------------visualizaçao states iniciais----------
#ifdef GNUPLOT
		int j;
		//printf("set autoscale xfix\n");
		printf("set autoscale keepfix\n");
		printf("set palette model RGB\n");
		printf("set palette defined ( 0 \"black\", 1 \"red\", 2 \"yellow\")\n");
		printf("set cbrange[0:2]\n");
		//printf("set title \'gama=0.75 , R=0.4\'\n");
		printf("set xrange[0:%d]\n",L);
		printf("set yrange[0:%d]\n",L);
		printf("set size square\n");
		printf("plot \"-\" matrix with image\n");

		for(j=0;j<L;j++)
		{
			for(i=0;i<L;i++)
				printf("%d ",state[j+i*L]);
			printf("\n");
		}	
		printf("\n"); printf("e\n");    printf("pause(0.5)\n");

		//    ./a.out | gnuplot
#endif

		// MCS
		for(t=1; t < tmax; t++)
		{			
			//interaçao individual
			for(p=0;p<L2;p++)
			{					
				Px = 0;
				Py = 0;
		
				x = (int) L*L*gsl_rng_uniform(rand_vec);
				y = 1 + (int) 4*gsl_rng_uniform(rand_vec);
		
				vizinho  = viz[x][y];
				vizinho1 = x;
				if (state[x] != state[vizinho])
				{
					f(payoff,state,viz,vizinho1,r,gama);
					Px = payoff[state[x]];
				
					f(payoff,state,viz,vizinho,r,gama);
					Py = payoff[state[vizinho]];
				//}

					Wxy = 1./( 1. + exp(-(Py-Px)/K));
			
					temp = gsl_rng_uniform(rand_vec);
					//drand48();
					if((state[x]+state[vizinho])==3){Wxy=0.;}

					//troca de estado
					if(temp < Wxy)
					{      	//e = state[x]; 
						state[x] = state[vizinho];	
						//state[viz[x][y]] = e;	
						if (Py<Px)
						{
							printf("%f %f  - RUIDO!!!\n", Py, Px);
#ifdef USEGFX	
							update_board_2d_punisher(L,state,t,p);
							waitmouse();
#endif											
						
						}
						else
							printf("%f %f\n", Py, Px);			
					}
#ifdef USEGFX
					
					//update_board_2d_punisher(L,state,t,p);
					//waitmouse();
#endif					
				}
			}
	
	
			if ( t >= measure_time)
			{
				count_states(&NC,&NP,&ND,state);
	
#ifdef densidade
		//densidades por passo
		//printf("%d %lf %lf %lf\n", t, (double)NC/(L*L), (double)ND/(L*L), (double)NP/(L*L));
		
				fprintf(fp,"%d %lf %lf %lf\n", t, (double)NC/L2, (double)ND/L2, (double)NP/L2);
		
#endif
				measure_time *= 1.1;
				if (floor(measure_time)-t < EPSILON) measure_time=ceil(measure_time);
			}
//--------------------------visualizaçao troca de states intermediários ----------


#ifdef GNUPLOT
			//printf("set size square\n");
			printf("set title \' MCS=%d \' \n", t);
			printf("plot \"-\" matrix with image\n");

			//printf("set left key \'%d\'\n",t);

			for(j=0;j<L;j++)
			{
				for(i=0;i<L;i++)
					printf("%d ",state[j+i*L]);
				printf("\n");
			}
			printf("\n"); printf("e\n");    printf("pause(0.0001)\n");

			//    ./a.out | gnuplot
#endif	
	}
	
	//return 0;
	}

#ifdef USEGFX
	ezChangeWindowTitle("Press a mouse button to end");
	waitmouse();
	dispose_board_2d();
#endif

	fclose(fp);

	return 0;
}

