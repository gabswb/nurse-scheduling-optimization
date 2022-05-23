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
    int size;
    std::vector<Gene> genes;
    float fitness;
    int n_employees;
    
    Chromosome();
    Chromosome(std::vector<Gene> genes_p, int n_employees_p);
    bool is_valid();
    void evaluate();
    void mutate();
    void is_mission_affected();
    void display_timetable(bool timetable_p[N_WEEK_DAY][N_WORKING_HOURS_SLOT]);
    void display();
    std::vector<Gene> init(std::vector<Mission> missions, std::vector<Employee> employees);
};

#endif /*CHROMOSOME_HPP*/