#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Chromosome.hpp"
#include "Mission.hpp"
#include "Employee.hpp"
#include "global.hpp"
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
 */
void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::chrono::steady_clock::time_point begin_exec);

/**
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
void display_population(Chromosome *population);

/**
 * @brief compute and display population fitness
 * 
 * @param population 
 * @param average_population_fitness 
 * @return float 
 */
void display_fitness(Chromosome *population, float &average_population_fitness);


void crossover();
void mutate();

#endif /*SOLVER_HPP*/