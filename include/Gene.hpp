#ifndef GENE_HPP
#define GENE_HPP

#include "Mission.hpp"
#include "Employee.hpp"

class Gene
{
public:
    Mission mission;
    Employee employee;
    bool is_assigned;

    Gene();
    Gene(Mission m, Employee e);
    
    bool check_specialty();

    friend std::ostream &operator<<(std::ostream &output, const Gene &g);
};

#endif /*GENE_HPP*/