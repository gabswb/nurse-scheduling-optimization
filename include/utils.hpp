#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "Mission.hpp"
#include "Employee.hpp"

int extract_rows_nb_csv(std::string path);

Mission *extract_mission_csv(int size, std::string path);
Employee *extract_employee_csv(int size, std::string path);
float *extract_distance_matrix_csv(int size, std::string path);

template <typename T>
void print_matrix(int size_p, const T *matrix_p);

#endif /*UTILS_HPP*/