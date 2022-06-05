#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Mission.hpp"
#include "Employee.hpp"

void genetic_algorithm(const Mission* missions[], const Employee* employees[], const float* distances[]);

void initialize_population();
void crossover();
void mutate();

 #endif /*SOLVER_HPP*/