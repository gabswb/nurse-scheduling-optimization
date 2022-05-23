
#include <stdio.h>
#include <iostream>
#include "global.hpp"
#include "Gene.hpp"
#include "Employee.hpp"
#include "Chromosome.hpp"
#include "Mission.hpp"

int generate_int_range(int min, int max);
void display_timetable(bool timetable_p[N_WEEK_DAY][N_WORKING_HOURS_SLOT]);

int main(int argc, char **argv)
{
       Skills skills[5] = {ELECTRICITY, CARPENTRY, MUSIC, MECANIC, GARDENING};
       Specialties specialties[2] = {SIGN_LANGUAGE, LPC};
       std::vector<Employee> employees;
       std::vector<Mission> missions;
       std::vector<Employee>::iterator itEm;
       std::vector<Mission>::iterator itMi;
       int tmp, i;

       srand(static_cast<int>(time(0)));

       /* Generate random employees and missions */
       int nb_employees = 25;
       int nb_mission = 80;
       itEm = employees.begin();
       itMi = missions.begin();

       for (i = 0; i < nb_employees; i++)
       {
              itEm = employees.insert(itEm, Employee(i, specialties[generate_int_range(0, 1)], skills[generate_int_range(0, 4)]));
       }

       for (i = 0; i < nb_mission; i++)
       {
              if (generate_int_range(0, 1))
                     tmp = generate_int_range(0, 2);
              else
                     tmp = generate_int_range(5, 8);
              itMi = missions.insert(itMi, Mission(i, generate_int_range(1, 100), generate_int_range(1, 100), generate_int_range(0, 5), tmp, tmp + generate_int_range(1, 3), specialties[generate_int_range(0, 1)], skills[generate_int_range(0, 4)]));
       }

       /* Generate initial solution with first fit algorithm */
       Chromosome initial_solution = Chromosome();
       std::cout << "\nGenerate initial solution with first fit algotihm\n";
       initial_solution.init(missions, employees);

       std::cout << "\nDone\n";
       return 0;
}

int generate_int_range(int min, int max)
{
       return min + (std::rand() % (max - min + 1));
}
