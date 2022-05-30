#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <vector>
#include <iostream>
#include "global.hpp"
#include "Mission.hpp"

class Employee
{
    public:
    int id;
    int quota;
    Specialties specialty;
    Skills skill;
    int timetable[N_WEEK_DAY][]

    Employee();
    Employee(int id_p, int quota_p, Specialties specialty_p, Skills skill_p);
    Employee(int id_p, Specialties specialty_p, Skills skill_p, std::vector<Mission> missions_p);

    friend std::ostream& operator<<(std::ostream &output, const Employee& e);

};

#endif /*EMPLOYEE_HPP*/