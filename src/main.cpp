
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <list>
#include "global.hpp"
#include "Gene.hpp"
#include "Employee.hpp"
#include "Chromosome.hpp"
#include "Mission.hpp"
#include "utils.hpp"

int n_employee = 0;//number of employee
int n_mission = 0;//number of missions
int n_location = 0;//number of locations

int population_size = 20;
float crossover_rate = 0.5;
float mutation_rate = 0.5;
int max_execution_time = (3*60*60);//3h 
int max_iteration_number = 1000000;
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
 * 45-4j:   ./it45-operation-research ../instances/45-4/Distances.csv ../instances/45-4/Intervenants.csv ../instances/45-4/Missions.csv
 * 96-6j:   ./it45-operation-research ../instances/96-6/Distances.csv ../instances/96-6/Intervenants.csv ../instances/96-6/Missions.csv
 * 100-10j: ./it45-operation-research ../instances/100-10/Distances.csv ../instances/100-10/Intervenants.csv ../instances/100-10/Missions.csv
 */
int main(int argc, char *argv[])
{
    extract_options(argc, argv);

    n_employee = extract_rows_nb_csv(argv[argc-2]);
    n_mission = extract_rows_nb_csv(argv[argc-1]);
    n_location = n_mission + 1; //+1 for sessad

    const float* distances = extract_distance_matrix_csv(n_location, argv[argc-3]); 
    const Employee* employees = extract_employee_csv(n_employee, argv[argc-2]);
    const Mission* missions = extract_mission_csv(n_mission, argv[argc-1]);

    // /* Generate initial solution with first fit algorithm */
    // std::cout << "\nGenerate initial solution with first fit algotihm\n";
    // Chromosome initial_solution = Chromosome(&missions, &employees, &distances);
    // initial_solution.initialize();
    // std::cout << initial_solution<< std::endl;
    // std::cout << "\nDone\n";
    // std::cout << "Evaluation: " << initial_solution.evaluate() << std::endl;


    delete[] missions;
    delete[] employees;
    delete[] distances;
    return 0;
}
