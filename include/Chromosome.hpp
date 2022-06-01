#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include "Gene.hpp"
#include "global.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>

class Chromosome
{
public:
    float fitness;
    Gene *genes;

    /**
     */
    std::vector<Time_window> employee_timetables[n_employee][N_WEEK_DAY];

    /**
     * @brief distances[i][j] = distance between mission i and mission j
     * @remark index 0 = SESSAD
     *
     */
    int distances[];

    Chromosome();
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
    Chromosome init(Mission missions[], Employee employees[], float distances[]);

    /**
     * @brief print a given timetable
     *
     * @param timetable_p
     */
    void display_timetable(int timetable_p[N_WEEK_DAY][N_WORKING_HOURS]);

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