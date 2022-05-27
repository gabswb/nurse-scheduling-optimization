#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include "Gene.hpp"
#include "global.hpp"
#include "instance.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>

class Chromosome
{
public:
    float fitness;
    Gene genes[NB_MISSION];

    /**
     * @brief employee_timetables[i][j][k] = -1 -> the employee i is free at time k of the day j
     * @brief employee_timetables[i][j][k] = other -> mission id of employee i at time k of the day j
     *
     */
    int employee_timetables[NB_EMPLOYEE][N_WEEK_DAY][N_WORKING_HOURS] = {-1};

    /**
     * @brief distances[i][j] = distance between mission i and mission j
     * @remark index 0 = SESSAD
     *
     */
    int distances[NB_MISSION + 1][NB_MISSION + 1];

    Chromosome();
    /**
     * @brief Check if the chromosome respect all constraints
     *
     * @return true is valid
     * @return false isn't valid
     */
    bool is_valid();

    /**
     * @brief generate the initial solution with first fit algorithm
     *
     * @param missions mission set
     * @param employees employee set
     * @return Chromosome the chromosome initialized
     */
    Chromosome init(Mission missions[NB_MISSION], Employee employees[NB_EMPLOYEE], int distances[NB_MISSION + 1][NB_MISSION + 1]);

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