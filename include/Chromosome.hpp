#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include "Gene.hpp"
#include "global.hpp"
#include <vector>
#include <unistd.h>

class Chromosome
{
    public:
    int size;
    std::vector<Gene> genes;
    float fitness;
    int n_employees;

    bool is_valid();
    void evaluate();
    void mutate();
    void is_mission_affected();

};

#endif /*CHROMOSOME_HPP*/