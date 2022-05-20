#ifndef GENE_HPP
#define GENE_HPP

#include "Mission.hpp"
#include "Employee.hpp"

class Gene
{
    Mission mission;
    Employee employee;

    void is_affected();
    void check_specialty();
};

#endif /*GENE_HPP*/