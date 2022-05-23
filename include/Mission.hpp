#ifndef MISSION_HPP
#define MISSION_HPP

#include "global.hpp"

class Mission
{
    public:
    int id;
    int coord_x;
    int coord_y;
    int day;
    int start_hour;
    int end_hour;
    Specialties specialty;
    Skills asked_skill;
    Skills assigned_skill;

    Mission();
    Mission(int id, int coord_x_p, int coord_y_p, int day_p, int start_hour_p, int end_hour_p, Specialties specialty_p, Skills skill_p, Skills assigned_skill_p);
    Mission(int id, int coord_x_p, int coord_y_p, int day_p, int start_hour_p, int end_hour_p, Specialties specialty_p, Skills skill_p);
};

#endif /*MISSION_HPP*/