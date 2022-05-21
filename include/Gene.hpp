#ifndef GENE_HPP
#define GENE_HPP

#include "Mission.hpp"
#include "Employee.hpp"

class Gene
{
    Mission mission;
    Employee employee;
    bool isAffected;

    Gene();
    Gene(Mission m, Employee e);

    public:
    bool is_affected();
    bool check_specialty();
};

#endif /*GENE_HPP*/