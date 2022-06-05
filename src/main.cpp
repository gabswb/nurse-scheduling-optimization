
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

int n_employee = 0;
int n_mission = 0;
int n_location = 0;

/*
 * Usage:   <distance_file> <employee_file> <mission_file>
 * 45-4j:   ./it45-operation-research ../instances/45-4/Distances.csv ../instances/45-4/Intervenants.csv ../instances/45-4/Missions.csv
 * 96-6j:   ./it45-operation-research ../instances/96-6/Distances.csv ../instances/96-6/Intervenants.csv ../instances/96-6/Missions.csv
 * 100-10j: ./it45-operation-research ../instances/100-10/Distances.csv ../instances/100-10/Intervenants.csv ../instances/100-10/Missions.csv
 */
int main(int argc, char *argv[])
{

    n_employee = extract_rows_nb_csv(argv[2]);
    n_mission = extract_rows_nb_csv(argv[3]);
    n_location = n_mission + 1; //+1 for sessad

    float* distances = extract_distance_matrix_csv(n_location, argv[1]); 
    Employee* employees = extract_employee_csv(n_employee, argv[2]);
    Mission* missions = extract_mission_csv(n_mission, argv[3]);

    /* Generate initial solution with first fit algorithm */
    std::cout << "\nGenerate initial solution with first fit algotihm\n";
    Chromosome initial_solution = Chromosome(employees, distances);
    initial_solution.initialize(missions, employees, distances);
    std::cout << initial_solution<< std::endl;
    std::cout << "\nDone\n";

    delete[] missions;
    delete[] employees;
    delete[] distances;
    return 0;
}
