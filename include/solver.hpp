#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <chrono>
#include "Chromosome.hpp"
#include "Mission.hpp"
#include "Employee.hpp"
#include "global.hpp"
<<<<<<< HEAD

/**
 * @brief Optimize the timetables of the employees using genetic algorithm
 * @param missions array of missions
 * @param employees array of employees
 * @param distances distance matrix
=======
#include <vector>
#include <bits/stdc++.h>
#include <chrono>
#include <iterator>
#include <random>

/**
 * @brief Solve the timetable problem with the given missions, employees and distances
 * 
 * @param missions missions array
 * @param employees employees array
 * @param distances distances matrix (in one-dimension array form)
 * @param begin_exec launch time
>>>>>>> f50b456c729e5f8f824ebb9e485f0de541a44791
 */
void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::chrono::steady_clock::time_point begin_exec);

/**
<<<<<<< HEAD
 * @brief Initialize the population with random chromosomes
 */
void initialize_population();

/**
 * @brief perform crossover between two chromosomes* 
 */
=======
 * @brief Initialize a heterogene population of chromosomes
 * 
 * @param population chromosome array to initialize
 * @param missions missions array
 * @param employees employees array
 * @param distances distances matrix (in one-dimension array form)
 */
void initialize_population(Chromosome* population, const Mission missions[], const Employee employees[], const float distances[]);

/**
 * @brief Display a given population
 * 
 * @param population chromosome array to display
 */
void display(Chromosome* population);

>>>>>>> f50b456c729e5f8f824ebb9e485f0de541a44791
void crossover();

/**
 * @brief perform mutation on few random chromosmes
 */
void mutate();

#endif /*SOLVER_HPP*/