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

class Chromosome
{
public:
    float fitness;
    Gene *genes;

    /**
     * @brief equivalent to employee_timetables[n_employee][N_WEEK]
     * 
     */
    std::list<Time_window> *employee_timetables;

    /**
     * @brief distances[i][j] = distance between mission i and mission j
     * @remark index 0 = SESSAD
     *
     */
    int *distances;

    Chromosome();
    ~Chromosome();

    /**
     * @brief Check if the chromosome respect all constraints
     *
     * @return true is valid
     * @return false isn't valid
     */
    bool is_valid();

    void initial_solution(Mission missions[], Employee employees[], float distances[]);

    /**
     * @brief generate the initial solution with first fit algorithm
     *
     * @param missions mission set
     * @param employees employee set
     * @return Chromosome the chromosome initialized
     */
    void init(Mission missions[], Employee employees[], float distances[]);

    /**
     * @brief print a employee timetable
     *
     * @param employee
     */
    void display_timetable(int employee);

    /**
     * @brief Display the whole chromosome: every affectations and timetables
     *
     */
    void display();

    void evaluate();
    void mutate();
    void is_mission_affected();

};

#endif /*CHROMOSOME_HPP*/