#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Chromosome.hpp"
#include "Mission.hpp"
#include "Employee.hpp"
#include "global.hpp"
#include <chrono>

void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::chrono::steady_clock::time_point begin_exec);

void initialize_population();
void crossover();
void mutate();

 #endif /*SOLVER_HPP*/