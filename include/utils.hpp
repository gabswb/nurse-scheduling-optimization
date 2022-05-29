#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <vector>
#include <string>
#include "Mission.hpp"
#include "Employee.hpp"

size_t extract_rows_nb_csv(std::string path);

Mission* extract_mission_csv(size_t size, std::string path);
Employee* extract_employee_csv(size_t size, std::string path);
float* extract_distance_matrix_csv(size_t size, std::string path);


#endif /*UTILS_HPP*/