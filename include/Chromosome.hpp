#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include "global.hpp"
#include "utils.hpp"
#include <vector>
#include <unistd.h>
#include <iterator>
#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

class Chromosome
{
public:
    float fitness;
    std::vector<Gene> *employee_timetables; // matrix of n_employee*N_WEEK_DAY, access to each element with employee_timetables[i*n_employee + j], i the ith employee and j the jth day
    const Mission *missions;
    const Employee *employees;
    const float *distances;

    /*correlation coefficient for fitness*/
    float alpha, beta, gamma, zeta, kappa;

    /* Constructor */
    Chromosome(const Mission missions[], const Employee employees[], const float distances[]);

    /* Coplien form */
    Chromosome();
    Chromosome(const Chromosome &chr);
    Chromosome& operator=(const Chromosome &chr);
    virtual ~Chromosome();

    /**
     * @brief Check if the chromosome respect all constraints
     * @return true is valid, false otherwise
     */
    bool is_valid();


    /**
     * @brief generate the initial solution with first fit algorithm
     * @param missions mission set
     * @param employees employee set
     * @param distances distance matrix
     */
    void initialize();

    /**
     * @brief print a employee timetable
     * @param employee
     */
    void print_employee_timetable(int employee);

    /**
     * @brief Display all the informations of the chromosome (all the employees timetable)
     */
    friend std::ostream &operator<<(std::ostream &output, Chromosome &c);

    /**
     * @brief compute the employee fitness of the chromosome
     * 
     * @return float the fitness
     */
    float evaluate_employees();

    /**
     * @brief compute the clients fitness of the chromosome
     * 
     * @return float the fitness
     */
    float evaluate_clients();

    /**
     * @brief compute the sessad fitness of the chromosome
     * 
     * @return float the fitness
     */
    float evaluate_sessad();

    /**
     * @brief apply mutation on the chromosome
     */
    void mutate();
};

/* Vector compare functions */
bool employees_fitness_comparator(Chromosome &a, Chromosome &b);
bool clients_fitness_comparator(Chromosome &a, Chromosome &b);
bool sessad_fitness_comparator(Chromosome &a, Chromosome &b);



#endif /*CHROMOSOME_HPP*/