# Comments:
#
# Tira a media de dados com 2 parametros que estão no mesmo arquivo e os parametros iguais estao em sequencia
# Para botar varias no mesmo arquivo usar calcular_media_lucas.sh

# se plotar com virgular escrever no terminal: export LC_NUMERIC="en_US.UTF-8"
# se tiver que usar menos parametros botar o inicial e final no fixo que ta no arquivo

BEGIN{
i=1;
parametro1_inicial = 1.0;
parametro1_final = 5.0;
parametro1_var = 0.1;

a = 0.0
parametro2_inicial = 0.0;
parametro2_final = 0.2; # tem que botar uma variaçao a mais do que o valor maximo (?)
parametro2_var = 0.01;

parametro3_inicial = 0.0;
parametro3_final = 5.0;
parametro3_var = 1.0;

}

{
# If not a comment, read record: 
 #if ($1 !~ /#/)
    #{

	parametro1 = $1 + 0;
    	parametro2 = $3 + 0;  #quando uasr em evoluçao temporal mudar esse valor
    	parametro3 = $4 + 0;
    	

	media[parametro1,parametro2,parametro3] = $13; 
		
 		
	
}
END {

	for(i=parametro1_inicial;i<=parametro1_final;i=i+parametro1_var) 
	{  
		for(k=parametro2_inicial;k<=parametro2_final;k=k+parametro2_var) 
		{
			for(w=parametro3_inicial;w<=parametro3_final;w=w+parametro3_var) 
			{ 
				for(z=parametro3_inicial;z<=parametro3_final;z=z+parametro3_var) 
				{ 
					if(z!=w)
					{
						if(media[i,k,w] <= media[i,k,z]){media[i,k,w]=0.;}
						
		
					}
					
				} 	
  			if(media[i,k,w]!=0.){printf("%f %f %f \n",i,k,w);}
			} #printf("\n");
		} printf("\n");
	}

}


