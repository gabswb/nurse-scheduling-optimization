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