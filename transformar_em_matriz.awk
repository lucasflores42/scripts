BEGIN{
col1 = 2.
col2 = 0.
i=0;
}
{
if ($1 != col1)
 {
	printf("\n");
	col1 = $1
	#if($4+$6 !=0)
	#{
 	#printf("%f ",$4/($4+$6));
	#}
	#else{printf("0 ");} 
	printf("%f ",$3);
}
else 
{
     #if ($2 !=1.3 )

	#if($4+$6 !=0)
	#{
 	#printf("%f ",$4/($4+$6));
	#}
	#else{printf("0 ");} 
	printf("%f ",$3);

#   ++i;
#   if (i==16)
#   {
#	  printf("\n");
#	i=0;
#   }
}

}
END{
 printf("\n");
}
