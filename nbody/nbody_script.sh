#!/bin/bash
#SBATCH --job-name=nbody
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
make
./nbody solar.tsv 200 5000000
./nbody 100 1 10000
./nbody 1000 1 10000
