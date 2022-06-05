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

    const Mission* missions;//reference to missions array of main
    const Employee* employees;//reference to employees array of main
    const float* distances;//reference to distances matrix of main
    
    /*correlation coefficient for fitness*/
    float alpha, beta, gamma, zeta, kappa;

    Chromosome(const Mission* missions[], const Employee* employees[], const float* distances[]);
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
     * @brief compute the fitness of the chromosome
     */
    float evaluate();

    /**
     * @brief apply mutation on the chromosome
     */
    void mutate();


};

#endif /*CHROMOSOME_HPP*/