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
    Gene genes[NB_MISSION];
    float fitness;
    bool employee_timetables[NB_EMPLOYEE][N_WEEK_DAY][N_WORKING_HOURS_SLOT] = {false};

    Chromosome();
    /**
     * @brief Check if chromosome is valid
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
    Chromosome init(Mission missions[NB_MISSION], Employee employees[NB_EMPLOYEE]);

    /**
     * @brief print a given timetable
     *
     * @param timetable_p
     */
    void display_timetable(bool timetable_p[N_WEEK_DAY][N_WORKING_HOURS_SLOT]);

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