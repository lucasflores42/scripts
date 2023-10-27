#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define A 100


int main()
{

	int i, j, h, k;

	srand((unsigned)time(NULL));
	
	double r=0.4;
	//scanf("%lf", &r);
	
	
	double R = 1, T = 1 + r, S = -r, P = 0, L = 0.5; 
	double matriz_payoff[3][3];

	int state [A*A];

	double payoff_x, payoff_y;
	int flag = 0;

	double payoff_total [A*A];
	int histC [1 + A*A]; // contador histograma
	int histD [1 + A*A];
	int histL [1 + A*A];
	int viz[A*A][4]; 
	int K=10000; 
	const int N_viz = 4;  
	int p;
	double l;      
	int x;	
	int y;  
	double ruido=0.1;	
	int ND;
	int NC;
	int NL;

	matriz_payoff[1][1] = R; //1

	matriz_payoff[0][1] = T; // 1+r

	matriz_payoff[1][0] = S; //-r

	matriz_payoff[0][0] = P; //0

	matriz_payoff[2][0] = L;
	
	matriz_payoff[2][1] = L;

	matriz_payoff[2][2] = L;

	matriz_payoff[0][2] = L;

	matriz_payoff[1][2] = L;



	for(i=0; i < A; i++)
	{
		for(j=0; j < A; j++)
		{

			viz[j+i*A][1] = j + i * A - A; //vizinho acima de i
			viz[j+i*A][2] = j + i * A + 1; //vizinho Ã  direita de i
			viz[j+i*A][3] = j + i * A + A; //vizinho abaixo de i
			viz[j+i*A][4] = j + i * A - 1; //vizinho Ã  esquerda i*/

			if (i == 0) viz[j+i*A][1] = j + A * A - A ; //ajuste do vizinho de cima dos elementos da fronteira superior
			if (j == 0) viz[j+i*A][4] = i * A + A - 1; //ajuste do vizinho Ã  esquerda dos elementos da fronteira esquerda
			if (i == A-1) viz[j+i*A][3] = j; //ajuste do vizinho abaixo dos elementos da fronteira inferior
			if (j == A-1) viz[j+i*A][2] = i * A ; //ajuste do vizinho Ã  direita dos elementos da fronteira direita
		}

	}


//-------------------------------------------gera states iniciais----------------
	for(i=0;i<A;i++)
	{
		for(j=0;j<A;j++)
		{	
			state[j+i*A] = rand()%3; 
			printf("%d ",state[i+j*A]);
		}
	}

//----------------------------------------visualizaçao states iniciais----------    
	
	/*printf("set autoscale keepfix\n");
	printf("set palette model RGB\n");
	printf("unset colorbox\n");
	printf("unset border\n");
	printf("unset xtics\n");
	printf("unset ytics\n");
	printf("set palette defined ( 0 \"purple\", 1 \"black\",  2 \"white\",  3 \"dark-green\", 4 \"dark-red\", 5 \"green\", 7 \"blue\",  9 \"red\")\n");
	printf("set cbrange[0:8]\n");
	printf("set xrange[0:100]\n");
	printf("set yrange[0:100]\n");
	printf("set size square\n");
			
	printf("plot \"-\" matrix with image\n");*/

    	for(j=0;j<A;j++) 
	{
      		for(i=0;i<A;i++) 
		{
	// imprimo todos os elementos de uma linha
	printf("%d ",state[i+j*A]);
      		}
      // e so depois dou enter
     	printf("\n");
    	}		
	printf("\n"); //printf("e\n");    printf("pause(0.01)\n");
  
    	//    ./a.out | gnuplot

//-----------------------------------------------------------------------------	


	for(k=0;k<K;k++)
        {

			NC = 0.0;
			ND = 0.0;
			NL = 0.0;

		//escolha aleatoria de quem interage
		for(p=0;p < A*A;p++)
		{					
			
		x = rand()%(A*A); //sitio i			
		y = rand()%(N_viz) + 1; // vizinho do i
		//printf("x=%d state=%d y=%d state=%d\n", x,state[x],viz[x][y],state[viz[x][y]]);
	

		payoff_x  = matriz_payoff[state[x]][state[viz[x][1]]];
		payoff_x += matriz_payoff[state[x]][state[viz[x][2]]];
		payoff_x += matriz_payoff[state[x]][state[viz[x][3]]];
		payoff_x += matriz_payoff[state[x]][state[viz[x][4]]];

		double Px = payoff_x;

		
	
		payoff_y  = matriz_payoff[state[viz[x][y]]][state[viz[viz[x][y]][1]]];
		payoff_y += matriz_payoff[state[viz[x][y]]][state[viz[viz[x][y]][2]]];
		payoff_y += matriz_payoff[state[viz[x][y]]][state[viz[viz[x][y]][3]]];
		payoff_y += matriz_payoff[state[viz[x][y]]][state[viz[viz[x][y]][4]]];

		double Py = payoff_y;           
		
	

		double Wxy = pow ( 1+exp(-(Py-Px)/ruido),-1);
		//printf("%lf %lf\n",Px, Py);

			
		//l= rand()%101;
		//l = l/100; 
		l = drand48();

		//printf("x=%d state=%d Px=%lf y=%d state=%d Py=%lf W=%lf l=%lf\n", x, state[x], Px, viz[x][y], state[viz[x][y]], Py, Wxy, l);
	

			if(state[x] == 1)
				NC += 1;

			if(state[x] == 0)
				ND += 1;

			if(state[x] == 2)
				NL += 1;

			
			if(Wxy > l)
                	{      	 state[x] = state[viz[x][y]];
		
		
		//printf("x=%d state=%d Px=%lf y=%d state=%d Py=%lf W=%lf l=%lf\n", x, state[x], Px, viz[x][y], state[viz[x][y]], Py, Wxy, l);

			}//printf("\n");
			


//-------------------------------------------------------------gaussiana-----------------

		}
			if (k < 100 && NC != 0.0 && ND != 0.0 && NL != 0.0) // a partir MCS 2000, o sistema entra em "equilibro" (verificado pelos gráficos)
			{
			// conta quantas vezes aparece certo numero de cooperators a cada MCS				
			histC[NC]++; 		
			histD[ND]++;
			histL[NL]++;
			//printf("%d %d %d %d\n", k, NC, ND, NL); 
			//printf("%d %d\n", hist[NC], NC);
			// aqui após plotar, preciso verificar uma gaussiana e assim verificar qual a média para o r atual
			}


//-------------------------------------------------visualizaçao troca de states----------    
//gnuplot> plot 'matriz.dat' matrix with image


	//printf("set size square\n");
	//printf("plot \"-\" matrix with image\n");
	
	flag = flag + 1;

	//if (flag == 10)
	//if (k < 10)
	{
	    	/*printf("set size square\n");
    		printf("plot \"-\" matrix with image\n");*/

    		for(j=0;j<A;j++) 
		{
      			for(i=0;i<A;i++) 
			{
				// imprimo todos os elementos de uma linha
				printf("%d ",state[i+j*A]);
      			}
      			// e so depois dou enter
      		printf("\n");
    		} 
		printf("\n");  // printf("e\n");    printf("pause(0.01)\n");
		
		flag = 0;

	}

//-----------------------------------------------------------------------------	

		

		//printf("%d %d %d\n", k, NC, ND);	


	
	

	}

/*

//---------------------------------------------state final----------------

//gnuplot> plot 'matriz.dat' matrix with image



    	for(j=0;j<A;j++) 
	{
      		for(i=0;i<A;i++) 
		{
	// imprimo todos os elementos de uma linha
	printf("%d ",state[i+j*A]);
      		}
     	 // e so depois dou enter
     	 printf("\n");
    	}


*/














}




















