# N-Body Simulation

This program simulates gravitational interactions between particles.

## How to Compile
```
make
```

## How to Run
```
./nbody <input_file> <dt> <num_steps>
```

Example:
```
./nbody solar.tsv 86400 100
```

This runs the solar system simulation for 100 days.

## Arguments
- input_file: file with particle data (like solar.tsv)
- dt: time step in seconds
- num_steps: how many iterations to run

## Input File Format

TSV format (tab separated):
- First number: how many particles
- Then for each particle: mass, x, y, z, vx, vy, vz, fx, fy, fz

## Output

Creates output.tsv with the same format, one line per timestep.

## Visualize
```
python3 plot.py output.tsv output.pdf
```

## Clean Up
```
make clean
```
