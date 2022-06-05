#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include "Gene.hpp"
#include "global.hpp"
#include <vector>
// #include <list>
#include <unistd.h>
#include <iterator>
#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

class Chromosome
{
public:
    float fitness;
    Gene* genes;//array of Gene
    std::vector<Time_window>* employee_timetables;//matrix of n_employee*N_WEEK_DAY, access to each element with employee_timetables[i*n_employee + j], i the ith employee and j the jth day

    /*correlation coefficient for fitness*/
    float alpha, beta, gamma, zeta, kappa;

    Chromosome(Employee employees[], float distances[]);
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
    void initialize(Mission missions[], Employee employees[], float distances[]);

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
     * @brief compute the fitness of the chromosome
     */
    float evaluate(float distances[], Employee employees[]);

    /**
     * @brief apply mutation on the chromosome
     */
    void mutate();


};

#endif /*CHROMOSOME_HPP*/