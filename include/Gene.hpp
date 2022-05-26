#ifndef GENE_HPP
#define GENE_HPP

#include "Mission.hpp"
#include "Employee.hpp"

class Gene
{
public:
    Mission mission;
    Employee employee;
    bool isAffected;

    Gene();
    Gene(Mission m, Employee e);

    bool is_affected();
    bool check_specialty();
    void display();
};

#endif /*GENE_HPP*/