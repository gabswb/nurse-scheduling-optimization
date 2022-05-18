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

    bool is_valid();
    void evaluate();
    void mutate();


};

#endif /*CHROMOSOME_HPP*/