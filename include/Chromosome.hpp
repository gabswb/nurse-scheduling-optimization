#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include "Gene.hpp"
#include <vector>
#include <unistd.h>

class Chromosome
{
    size_t size;
    std::vector<Gene> genes;
    float fitness;
    size_t n_employees;

    bool is_valid();
    void evaluate();
    void mutate();
    void is_mission_affected();

};

#endif /*CHROMOSOME_HPP*/