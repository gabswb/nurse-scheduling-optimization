
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
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
 * Usage:  <distance_file> <employee_file> <mission_file>
 */
int main(int argc, char *argv[])
{

    n_employee = extract_rows_nb_csv("instances/45-4/Intervenants.csv");
    n_mission = extract_rows_nb_csv("instances/45-4/Missions.csv");
    n_location = n_mission;

    float *distances = extract_distance_matrix_csv(n_mission + 1, "instances/45-4/Distances.csv"); //+1 for sessad
    Employee *employees = extract_employee_csv(n_employee, "instances/45-4/Intervenants.csv");
    Mission *missions = extract_mission_csv(n_mission, "instances/45-4/Missions.csv");

    for(int i = 0 ; i < n_employee ; ++i)
        std::cout << employees[i];
    for(int i = 0 ; i < n_mission ; ++i)
        std::cout << missions[i];


    /* Generate initial solution with first fit algorithm */
    std::cout << "\nGenerate initial solution with first fit algotihm\n";
    Chromosome initial_solution = Chromosome();
    initial_solution.init(missions, employees, distances);
    // initial_solution.display();

    std::cout << "\nDone\n";

    delete[] missions;
    delete[] employees;
    delete[] distances;
    return 0;
}
