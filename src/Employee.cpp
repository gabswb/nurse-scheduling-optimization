#include "Employee.hpp"

Employee::Employee() {}

Employee::Employee(int id_p, int qutoa_p, Specialties specialty_p, Skills skill_p)
{
    this->id = id_p;
    this->quota = qutoa_p * 60; // hour->minutes
    this->specialty = specialty_p;
    this->skill = skill_p;
}

std::ostream &operator<<(std::ostream &output, const Employee &e)
{
    output << "Employee " << e.id  << " : skill=" << e.skill << ", specialty=" << e.specialty << ", quota=" << e.quota;
    return output;
}
