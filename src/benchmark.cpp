#include <fstream>
#include <iostream>
#include "solver.hpp"
#include "global.hpp"

void benchmark(const Mission missions[], const Employee employees[], const float distances[], std::default_random_engine &generator, std::chrono::steady_clock::time_point begin_exec)
{
    std::fstream file;
    file.open("benchmark.txt", std::ios::out);
    if(!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    
    float fitness_average[4*4] = {0};
    int k;
    for(int i = 0; i < 2; i++) {
        for(float i=0.2; i< 1.0; i+=0.2){
            for(float j=0.2; j<0.6; j+=0.1){
                crossover_rate = i;
                mutation_rate = j;
                Chromosome solution = genetic_algorithm(missions, employees, distances, generator, begin_exec);
                fitness_average[k++] += solution.evaluate_employees();
            }
        }
        k=0;
    }

    for(int i = 0; i < 4*4; ++i) {
        fitness_average[i] /= 2;
    }

    k=0;
    for(float i=0.2; i< 1.0; i+=0.2){
        for(float j=0.2; j<0.6; j+=0.1){
            file << i << "," << j << "," << fitness_average[k] << "\n";
            ++k;
        }
    }
    file.close();
    std::cout << "Benchmark done" << std::endl;
}