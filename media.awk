# Comments:
#
# Tira a media de dados com ate 3 parametros que estão no mesmo arquivo e os parametros iguais estao em sequencia

# se plotar com virgular escrever no terminal: export LC_NUMERIC="en_US.UTF-8"
# se tiver que usar menos parametros botar o inicial e final no fixo que ta no arquivo

#usar uma vez dentro do calcular_media.sh para juntar as evoluçoes em um mesmo arquivo
#usar denovo nesse novo arquivo com todas evoluçoes para tirar media

BEGIN{
i=1;
parametro1_inicial = 0;
parametro1_final = 99999;
parametro1_var = 1;

a = 0.0
parametro2_inicial = a;
parametro2_final = a; # tem que botar uma variaçao a mais do que o valor maximo (?)
parametro2_var = 0.1;

b = 0.0
parametro3_inicial = b;
parametro3_final = b;
parametro3_var = 1.0;

}

{
# If not a comment, read record: 
 #if ($1 !~ /#/)
    #{

	parametro1 = $1 + 0;
    	parametro2 = 0 + 0;  #quando usar em evoluçao temporal mudar esse valor para zero
    	parametro3 = 0 + 0;
	for(j=1;j<=NF;j++)
	{
		media[parametro1,parametro2,parametro3,j] += $j; 
		
	}   		
	imax[parametro1,parametro2,parametro3] += 1;		


	desvio1[parametro1,parametro2,parametro3] += $2;
	desvio2[parametro1,parametro2,parametro3] += $2*$2; 	
	
}
END {

	for(i=parametro1_inicial;i<=parametro1_final;i=i+parametro1_var) 
	{  
		for(k=parametro2_inicial;k<=parametro2_final;k=k+parametro2_var) 
		{
			for(w=parametro3_inicial;w<=parametro3_final;w=w+parametro3_var) 
			{ 
				a=imax[i,k,w];
				desvio = sqrt( (desvio2[i,k,w] - (desvio1[i,k,w]*desvio1[i,k,w])/a)/a );
				
			   	for(j=1;j<=NF;j++)
				{
					media[i,k,w,j] = media[i,k,w,j]/a
					printf "%f ",media[i,k,w,j]
				}  	
				printf "%f ",desvio
				printf "%d \n",a      
			}
		}
        #printf("\n");
	}

}


