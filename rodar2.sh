#!/bin/bash
#SBATCH -n 1 # Numero de CPU cores a serem alocados 
#SBATCH -N 1 # Numero de nodes a serem alocados
#SBATCH -t 7-00:05 # Tempo limite de execucao (D-HH:MM)
#SBATCH -p long # Particao (fila) a ser submetido
#SBATCH --qos qos_long # QOS 

export LC_ALL="en_US.UTF-8"
LANG=en_US.UTF-8
for k in $(seq 1 1 10) #repetiçoes
do
#for j in $(seq 0. 0.1 1.5) #gama
#do
	for i in $(seq 4.5 0.1 6.5) #r
	do
	./a.out $i 0.0 0.0   #> dados_r"$i".dat
	#echo $i $j 
	done
#done
done
