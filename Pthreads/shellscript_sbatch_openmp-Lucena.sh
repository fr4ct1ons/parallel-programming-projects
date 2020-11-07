#!/bin/bash

#SBATCH --partition=cluster
#SBATCH --job-name=MatrizQuadrada_Lucena
#SBATCH --output=MatrizQuadradaOutput_Lucena.out
#SBATCH --error=MatrizQuadradaError_Lucena.err
#SBATCH --time=0-00:2
#SBATCH --hint=compute_bound 

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32

#No Supercomputador, 1 nó = 32 Cores (ou CPUs)
#Lembrar que: TASK = PROCESSO

#A configuração acima reserva 1 nó inteiro (32 cpus no mesmo processador), vai rodar apenas 1 processo por vez,
# mas este processo terá acesso a 32 cores

#Loop principal de execuções. São 10 tentativas

	tentativas=10 #Quantas vezes o código será executado

	for cores in 4 8 16 32 #números de cores utilizados
	do
			for size in 10 20 30 40 #tamanho do problema
			do   	
				for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
				do
					srun --mpi=pmi2 -n $cores mpi_mm $size #atualizar de acordo com OpenMP
				done
			done

	done
	
	exit 

