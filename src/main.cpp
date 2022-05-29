
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "global.hpp"
#include "Gene.hpp"
#include "Employee.hpp"
#include "Chromosome.hpp"
#include "Mission.hpp"
#include "instance.hpp"

void print_matrix(int d[NB_MISSION + 1][NB_MISSION + 1]);
int generate_int_range(int min, int max);

int main(int argc, char **argv)
{
       Skills skills[5] = {ELECTRICITY, CARPENTRY, MUSIC, MECANIC, GARDENING};
       Specialties specialties[2] = {LSF, LPC};
       Employee employees[NB_EMPLOYEE];
       Mission missions[NB_MISSION];
       int distances[NB_MISSION + 1][NB_MISSION + 1];
       int tmp, i, j;

       srand(static_cast<int>(time(0)));

       /* Generate random employees and missions */

       for (i = 0; i < NB_EMPLOYEE; i++)
       {
              employees[i] = Employee(i, specialties[generate_int_range(0, 1)], skills[generate_int_range(0, 4)]);
       }

       for (i = 0; i < NB_MISSION; i++)
       {
              if (generate_int_range(0, 1))
                     tmp = generate_int_range(0, 2);
              else
                     tmp = generate_int_range(5, 8);
              missions[i] = Mission(i, generate_int_range(1, 100), generate_int_range(1, 100), generate_int_range(0, 5), tmp, tmp + generate_int_range(1, 3), specialties[generate_int_range(0, 1)], skills[generate_int_range(0, 4)]);
       }

       /* Compute distances btw missions and SESSAD */
       int sessad_coord_y = generate_int_range(1, 100);
       int sessad_coord_x = generate_int_range(1, 100);
       distances[0][0] = -1;

       for (i = 0; i < NB_MISSION; i++)
              distances[0][i + 1] = sqrt(pow(sessad_coord_y - missions[i].coord_y, 2) + pow(sessad_coord_x - missions[i].coord_x, 2));

       for (i = 0; i < NB_MISSION; i++)
              distances[i + 1][0] = sqrt(pow(missions[i].coord_y - sessad_coord_y, 2) + pow(missions[i].coord_x - sessad_coord_x, 2));

       /* Compute distances btw mission places */
       for (i = 0; i < NB_MISSION; i++)
              for (j = 0; j < NB_MISSION; j++)
                     if (i == j)
                            distances[i + 1][j + 1] = -1;
                     else
                            distances[i + 1][j + 1] = sqrt(pow(missions[i].coord_y - missions[j].coord_y, 2) + pow(missions[i].coord_x - missions[j].coord_x, 2));

       // print_matrix(distances);

       /* Generate initial solution with first fit algorithm */
       std::cout << "\nGenerate initial solution with first fit algotihm\n";
       Chromosome initial_solution = Chromosome();
       initial_solution.init(missions, employees, distances);
       initial_solution.display();

       std::cout << "\nDone\n";
       return 0;
}

int generate_int_range(int min, int max)
{
       return min + (std::rand() % (max - min + 1));
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
