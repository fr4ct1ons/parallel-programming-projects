#!/bin/bash

#SBATCH --partition=cluster
#SBATCH --job-name=MatrizQuadradaTeste_Lucena
#SBATCH --output=MatrizQuadradaOutput_Teste_Lucena.out
#SBATCH --error=MatrizQuadradaError_Teste_Lucena.err
#SBATCH --time=0-00:10
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


	./MatMult_SRL -serial 2000 #atualizar de acordo com OpenMP

exit 
