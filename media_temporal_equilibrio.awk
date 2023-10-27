# Comments:
# plota densidade media no equilibrio pra uma evoluçao temporal

# se plotar com virgular escrever no terminal: export LC_NUMERIC="en_US.UTF-8"

BEGIN { 
        #printf export LC_NUMERIC="en_US.UTF-8"      
	i=0;

      }
{
	

	if ($1 >=70000) 
     	{
		for(j=1;j<=NF;j++)
		{
			media[j] += $j; 
			#print media[j]
		}  						
		++i;
	}    
		 
}
END { 

	for(j=2;j<=NF;j++)
	{
		#media[j] += $j; 
		printf "%s ",media[j]/i
		#print media[j]/i
	}  printf "\n"
	

    }


