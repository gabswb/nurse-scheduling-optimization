
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <list>
#include <iterator>
#include <chrono>
#include <random>
#include "global.hpp"
#include "gene.hpp"
#include "Chromosome.hpp"
#include "gene.hpp"
#include "utils.hpp"
#include "solver.hpp"
#include "benchmark.cpp"

int n_employee = 0; // number of employee
int n_mission = 0;  // number of missions
int n_location = 0; // number of locations


int population_size = 5;
float crossover_rate = 0.5;
float mutation_rate = 0.5;
int max_execution_time = (3 * 60 * 60); // 3h
int max_iteration_number = 100000;
bool verbose = false;

/*
 * Usage: ./argv[0] [options] <distance_file> <employee_file> <mission_file>
    options:
 *  [-p arg1 arg2 arg2] ,arg1 = population size, arg2 = crossover rate, arg3 = mutation rate
 *  [-t arg3]           ,arg3 = max execution time
 *  [-i arg4]           ,arg4 = max iteration number
 *  [-v]                ,verbose mode
 *  [-h]                ,print this usage message and exit
 *
 * 45-4j:    ./it45-operation-research -i 100000 -p 100 0.5 0.1 ../instances/45-4/Distances.csv ../instances/45-4/Intervenants.csv ../instances/45-4/Missions.csv
 * 96-6j:    ./it45-operation-research -i 100000 -p 100 0.5 0.1 ../instances/96-6/Distances.csv ../instances/96-6/Intervenants.csv ../instances/96-6/Missions.csv
 * 100-10j:  ./it45-operation-research -i 100000 -p 100 0.5 0.1 ../instances/100-10/Distances.csv ../instances/100-10/Intervenants.csv ../instances/100-10/Missions.csv
 */
int main(int argc, char *argv[])
{
    extract_options(argc, argv);

    n_employee = extract_rows_nb_csv(argv[argc - 2]);
    n_mission = extract_rows_nb_csv(argv[argc - 1]);
    n_location = n_mission + 1; //+1 for sessad

    const float *distances = extract_distance_matrix_csv(n_location, argv[argc - 3]);
    const Employee *employees = extract_employee_csv(n_employee, argv[argc - 2]);
    const Mission *missions = extract_mission_csv(n_mission, argv[argc - 1]);
    std::cout << "Extraction done" << std::endl;


    std::random_device rd;
    std::default_random_engine generator(rd());

    
    //benchmark(missions, employees, distances, generator, std::chrono::steady_clock::now());
    /* Solving problem */
    std::cout << "Optimization of the solution ..." << std::endl;
    auto begin_exec = std::chrono::steady_clock::now(); // benchmark algorithm's execution time
    Chromosome solution = genetic_algorithm(missions, employees, distances, generator, begin_exec);
    auto end_exec = std::chrono::steady_clock::now();
    
    
    std::chrono::duration<double> diff = end_exec - begin_exec;
    std::cout << "\nFinal solution :\n" << solution
              << "Execution time : " << diff.count() << "s"
              << "\nEmployee fitness = "<< solution.evaluate_employees()
              << "\nClient fitness = " << solution.evaluate_clients()
              << "\nSESSAD fitness = " << solution.evaluate_sessad() << std::endl;


    delete[] missions;
    delete[] employees;
    delete[] distances;
    return 0;
}
