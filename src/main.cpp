
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "global.hpp"
#include "Gene.hpp"
#include "Employee.hpp"
#include "Chromosome.hpp"
#include "Mission.hpp"
#include "utils.hpp"

#include "instance.hpp"
#include <stdio.h>


void print_matrix(int d[NB_MISSION + 1][NB_MISSION + 1]);
/*
Usage:  <distance_file> <employee_file> <mission_file>
*/
int main(int argc, char *argv[])
{

       size_t n_employee = extract_rows_nb_csv(argv[2]);
       size_t n_mission = extract_rows_nb_csv(argv[3]);

       float* distances = extract_distance_matrix_csv(n_mission+1, argv[1]);//+1 for sessad
       Employee* employees = extract_employee_csv(n_employee, argv[2]);
       Mission* missions = extract_mission_csv(n_mission, argv[3]);

       
       delete[] missions;
       delete[] employees;
       delete[] distances;

       // /* Generate initial solution with first fit algorithm */
       // std::cout << "\nGenerate initial solution with first fit algotihm\n";
       // Chromosome initial_solution = Chromosome();
       // initial_solution.init(missions, employees, distances);
       // initial_solution.display();

       // std::cout << "\nDone\n";
       // return 0;
}


/**
 * print a matrix
 */
void print_matrix(int d[NB_MISSION + 1][NB_MISSION + 1])
{
       int i, j;
       for (i = 0; i < NB_MISSION + 1; i++)
       {
              printf("%d:", i);
              for (j = 0; j < NB_MISSION + 1; j++)
              {
                     printf("%d ", d[i][j]);
              }
              printf("\n");
       }
}
