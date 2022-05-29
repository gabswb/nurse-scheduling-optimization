#include "Mission.hpp"

Mission::Mission(){}

Mission::Mission(int id_p, int coord_x_p, int coord_y_p, int day_p, int start_hour_p, int end_hour_p, Specialties specialty_p, Skills skill_p, Skills assigned_skill_p)
{
    this->id = id_p;
    this->coord_x = coord_x_p;
    this->coord_y = coord_y_p;
    this->day = day_p;
    this->start_hour = start_hour_p;
    this->end_hour = end_hour_p;
    this->specialty = specialty_p;
    this->asked_skill = skill_p;
    this->assigned_skill = assigned_skill_p;
}

Mission::Mission(int id_p, int coord_x_p, int coord_y_p, int day_p, int start_hour_p, int end_hour_p, Specialties specialty_p, Skills skill_p)
{
    this->id = id_p;
    this->coord_x = coord_x_p;
    this->coord_y = coord_y_p;
    this->day = day_p;
    this->start_hour = start_hour_p;
    this->end_hour = end_hour_p;
    this->specialty = specialty_p;
    this->asked_skill = skill_p;
}

Mission::Mission(int id_p, int day_p, int start_hour_p, int end_hour_p, Specialties specialty_p, Skills asked_skill_p)
{
    this->id = id_p;
    this->day = day_p;
    this->start_hour = start_hour_p;
    this->end_hour = end_hour_p;
    this->specialty = specialty_p;
    this->asked_skill = asked_skill_p;
}

// Mission& Mission::operator=(const Mission& m)
// {
//     this->id = m.id;
//     this->day = m.day;
//     this->start_hour = m.start_hour;
//     return *this;
// }

std::ostream& operator<<(std::ostream &output, const Mission& m)
{
    output << "Mission("<< m.id<<", "<< m.day <<", "<< m.start_hour<<", "<< m.end_hour << ", "<< m.specialty<<", "<< m.asked_skill<< ")"<<std::endl;
    return output;
}