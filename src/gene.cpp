#include "gene.hpp"

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


Mission::Mission() {}

Mission::Mission(int id_p, int day_p, int start_minute_p, int end_minute_p, Specialties specialty_p, Skills skill_p)
{
    this->id = id_p;
    this->day = day_p;
    this->start_minute = start_minute_p;
    this->end_minute = end_minute_p;
    this->specialty = specialty_p;
    this->skill = skill_p;
}

std::ostream &operator<<(std::ostream &output, const Mission &m)
{
    output << "Mission(" << m.id << ", " << m.day << ", " << m.start_minute << ", " << m.end_minute << ", " << m.specialty << ", " << m.skill << ")" << std::endl;
    return output;
}