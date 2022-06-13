#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <list>
#include "Mission.hpp"
#include "Employee.hpp"

/**
 * @brief Extract the options given in the commande line arguments
 * @param argc number of commande line arguments
 * @param argv array of command line arguments
 */
void extract_options(int argc, char* argv[]);

/**
 * @brief Extract the number of rows in a csv file
 * @param path of the csv file
 * @return int number of rows
 */
int extract_rows_nb_csv(std::string path);

/**
 * @brief Extract the missions from a csv file
 * @param size number of missions
 * @param path of the csv file
 * @return Mission* array of missions
 */
Mission *extract_mission_csv(int size, std::string path);

/**
 * @brief Extract the employees from a csv file
 * @param size number of employees
 * @param path of the csv file
 * @return Employee* array of employee
 */
Employee *extract_employee_csv(int size, std::string path);

/**
 * @brief Extract the distances from a csv file
 * @param size number of distances
 * @param path of the csv file
 * @return float* array of distances
 */
float *extract_distance_matrix_csv(int size, std::string path);

template <typename T>
void print_matrix(int size_p, const T *matrix_p);

bool time_window_compare(Time_window &a,Time_window &b);

const std::string usage_msg = "\n\n"
"Usage: %s [options] <required_distance_file> <resquired_employee_file> <resquired_mission_file>\n\n"

"   options : \n"
"       [-p arg1 arg2 arg2] ,arg1 = population size, arg2 = crossover rate, arg3 = mutation rate\n"
"       [-t arg3]           ,arg3 = max execution time\n"
"       [-i arg4]           ,arg4 = max iteration number\n"
"       [-v]                ,verbose mode\n"
"       [-h]                ,print this usage message and exit\n";

#endif /*UTILS_HPP*/