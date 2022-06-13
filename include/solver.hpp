#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <chrono>
#include "Chromosome.hpp"
#include "Mission.hpp"
#include "Employee.hpp"
#include "global.hpp"
#include "utils.hpp"
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
void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::default_random_engine &generator, std::chrono::steady_clock::time_point begin_exec);

/**
 * @brief Initialize a heterogene population of chromosomes
 *
 * @param population chromosome array to initialize
 * @param missions missions array
 * @param employees employees array
 * @param distances distances matrix (in one-dimension array form)
 */
void initialize_population(Chromosome *population, const Mission missions[], const Employee employees[], const float distances[]);

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

/**
 * @brief selects a chromosome by the biased roulette method. The probability of selecting a chromosome is inversely proportional to its fitness (because fitness minimization)
 *
 * @param population in which the chromosome is selected
 * @param generator random number generator
 * @return Chromosome* the chromosome selected for a crossover
 */
Chromosome *roulette_selection(Chromosome population[], std::default_random_engine &generator);

/**
 * @brief Divide the 2 chromosomes in 1 point and create 2 different new child chromosomes as a combination of the 2 parents
 *
 * @param parent1
 * @param parent2
 * @param child1
 * @param child2
 */
void crossover_1X(Chromosome *parent1, Chromosome *parent2, Chromosome *child1, Chromosome *child2);

/**
 * @brief Divide the 2 chromosomes in N points and create 2 different new child chromosomes as a combination of the 2 parents
 * @note Here N is 4 because the employees work 5 days a week
 * @param parent1
 * @param parent2
 * @param child1
 * @param child2
 */
void crossover_NX(Chromosome *parent1, Chromosome *parent2, Chromosome *child1, Chromosome *child2);

/**
 * @brief selects a chromosome by the biased roulette method. The probability of selecting a chromosome is proportional to its fitness (because fitness minimization). Thus, the less fit chromosome is more likely to be selected
 *
 * @param population in which the chromosome is selected
 * @param generator random number generator
 */
void replacement_roulette_selection(Chromosome population[], Chromosome child1, std::default_random_engine &generator);

/**
 * @brief perform mutation on few random chromosmes
 */
void mutate(Chromosome &chromosome, std::default_random_engine &generator);

#endif /*SOLVER_HPP*/