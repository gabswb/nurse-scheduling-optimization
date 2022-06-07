#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <chrono>
#include "Chromosome.hpp"
#include "Mission.hpp"
#include "Employee.hpp"
#include "global.hpp"

/**
 * @brief Optimize the timetables of the employees using genetic algorithm
 * @param missions array of missions
 * @param employees array of employees
 * @param distances distance matrix
 */
void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::chrono::steady_clock::time_point begin_exec);

/**
 * @brief Initialize the population with random chromosomes
 */
void initialize_population();

/**
 * @brief perform crossover between two chromosomes* 
 */
void crossover();

/**
 * @brief perform mutation on few random chromosmes
 */
void mutate();

 #endif /*SOLVER_HPP*/