#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

double gravity = 6.674e-11;

struct Particle {
    double mass;
    double x, y, z;
    double vx, vy, vz;
    double fx, fy, fz;
};

int main(int argc, char* argv[]) {

    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <input_file or num_particles> <dt> <numSteps>" << endl;
        return 1;
    }

    int n; // number of particles
    Particle particles[10000]; // Max array size 10,000

    // Get arguments from command line
    string inputArg = argv[1];   // File or number
    double dt = atof(argv[2]);    // Convert string to double
    int numSteps = atoi(argv[3]); // Convert string to int

    // Check if first argument is a number or filename
    // Try to convert to integer
    char* endptr;
    long numParticles = strtol(argv[1], &endptr, 10);

    if (*endptr == '\0') {
        // It's a number - generate random particles
        n = (int)numParticles;
        cout << "Generating " << n << " random particles..." << endl;
        
        srand(time(NULL));  // Seed random number generator
        
        for (int i = 0; i < n; i++) {
            particles[i].mass = (rand() % 1000 + 1) * 1e24;  // Random mass
            particles[i].x = (rand() % 2000 - 1000) * 1e9;   // Random position
            particles[i].y = (rand() % 2000 - 1000) * 1e9;
            particles[i].z = (rand() % 2000 - 1000) * 1e9;
            particles[i].vx = (rand() % 100 - 50) * 1e3;     // Random velocity
            particles[i].vy = (rand() % 100 - 50) * 1e3;
            particles[i].vz = (rand() % 100 - 50) * 1e3;
            particles[i].fx = 0;
            particles[i].fy = 0;
            particles[i].fz = 0;
        }
    } else {    
        
        ifstream infile(inputArg);

        if (!infile.is_open()) {
        cout << "Error: Could not open file " << inputArg << endl;
        return 1;
        }

        infile >> n; // Reads the number of particles
        cout << "Loading " << n << " particles from file..." << endl;

        // Read each particle's data
        for (int i = 0; i < n; i++) {
            infile >> particles[i].mass
                >> particles[i].x >> particles[i].y >> particles[i].z
                >> particles[i].vx >> particles[i].vy >> particles[i].vz
                >> particles[i].fx >> particles[i].fy >> particles[i].fz;
        }

        infile.close();
    }



    ofstream outfile("output.tsv");
    
    for (int step = 0; step < numSteps; step++) {
        
        // Initialize all forces to zero
        for (int i = 0; i < n; i++) {
            particles[i].fx = 0;
            particles[i].fy = 0;
            particles[i].fz = 0;
        }
        
        // Calculate force between every pair
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {  // j starts at i+1 to avoid duplicates
                // Calculate distance between particle i and particle j
                double dx = particles[j].x - particles[i].x;
                double dy = particles[j].y - particles[i].y;
                double dz = particles[j].z - particles[i].z;
                
                double distSq = dx*dx + dy*dy + dz*dz;
                double dist = sqrt(distSq);
                
                double forceMag = gravity * particles[i].mass * particles[j].mass / distSq;
                
                double fx = forceMag * dx / dist;
                double fy = forceMag * dy / dist;
                double fz = forceMag * dz / dist;
                
                // Apply force to both particles
                particles[i].fx += fx;
                particles[i].fy += fy;
                particles[i].fz += fz;
                
                particles[j].fx -= fx;  // Opposite direction
                particles[j].fy -= fy;
                particles[j].fz -= fz;
            }
        }
        
        // Update velocities for ALL particles
        for (int i = 0; i < n; i++) {
            double ax = particles[i].fx / particles[i].mass;
            double ay = particles[i].fy / particles[i].mass;
            double az = particles[i].fz / particles[i].mass;
            
            particles[i].vx += ax * dt;
            particles[i].vy += ay * dt;
            particles[i].vz += az * dt;
        }
        
        // Update positions for ALL particles
        for (int i = 0; i < n; i++) {
            particles[i].x += particles[i].vx * dt;
            particles[i].y += particles[i].vy * dt;
            particles[i].z += particles[i].vz * dt;
        }
        
        // Write to file
        outfile << n;  // Write number of particles
        for (int i = 0; i < n; i++) {
            outfile << "\t" << particles[i].mass
                    << "\t" << particles[i].x << "\t" << particles[i].y << "\t" << particles[i].z
                    << "\t" << particles[i].vx << "\t" << particles[i].vy << "\t" << particles[i].vz
                    << "\t" << particles[i].fx << "\t" << particles[i].fy << "\t" << particles[i].fz;
        }
        outfile << endl;  // New line after each timestep
    }
    outfile.close();
    cout << "Simulation complete! Output saved to output.tsv" << endl;

    return 0;
}