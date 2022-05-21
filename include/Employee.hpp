#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <vector>
#include "global.hpp"
#include "Mission.hpp"

class Employee
{
    public:
    int id;
    Specialties specialty;
    Skills skill;
    std::vector<Mission> mission;

};

#endif /*EMPLOYEE_HPP*/