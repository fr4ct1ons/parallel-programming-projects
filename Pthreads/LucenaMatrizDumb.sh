#!/bin/bash

#SBATCH --partition=cluster
#SBATCH --job-name=MatrizQuadradaDumb_Lucena
#SBATCH --output=MatrizQuadradaDumbOutput_Lucena.out
#SBATCH --error=MatrizQuadradaDumbError_Lucena.err
#SBATCH --time=0-00:2
#SBATCH --hint=compute_bound 

#### ALTERADO

#SBATCH --mail-user=gabriellucena23@gmail.com
#SBATCH --mail-type=ALL

#### ALTERADO

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32

#No Supercomputador, 1 nó = 32 Cores (ou CPUs)
#Lembrar que: TASK = PROCESSO

#A configuração acima reserva 1 nó inteiro (32 cpus no mesmo processador), vai rodar apenas 1 processo por vez,
# mas este processo terá acesso a 32 cores

#Loop principal de execuções. São 10 tentativas

	tentativas=10 #Quantas vezes o código será executado


	for size in 135 215 150 80 #tamanho do problema
	do   	
		for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
		do
			./MatMult_SRL -random $size  #atualizar de acordo com OpenMP
		done
	done


	for size in 135 215 150 80 #tamanho do problema
	do   	
		for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
		do
			./MatMult_SRL -serial $size  #atualizar de acordo com OpenMP
		done
	done
	
	exit 

