#include "Employee.hpp"

Employee::Employee(){}

Employee::Employee(int id_p, Specialties specialty_p, Skills skill_p)
{
    this->id = id_p;
    this->specialty = specialty_p;
    this->skill = skill_p;
}

Employee::Employee(int id_p, Specialties specialty_p, Skills skill_p, std::vector<Mission> missions_p)
{
    this->id = id_p;
    this->specialty = specialty_p;
    this->skill = skill_p;
    this->missions = missions_p;
}
