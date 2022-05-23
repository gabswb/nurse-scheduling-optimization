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
    std::vector<Mission> missions;

    Employee();
    Employee(int id_p, Specialties specialty_p, Skills skill_p);
    Employee(int id_p, Specialties specialty_p, Skills skill_p, std::vector<Mission> missions_p);
};

#endif /*EMPLOYEE_HPP*/