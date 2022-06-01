#ifndef MISSION_HPP
#define MISSION_HPP

#include <iostream>
#include "global.hpp"

class Mission
{
public:
    int id;
    int day;
    int start_minute;
    int end_minute;
    Specialties specialty;
    Skills skill;

    Mission();
    Mission(int id, int day_p, int start_minute_p, int end_minute_p, Specialties specialty_p, Skills skill_p);

    // Mission& operator=(const Mission& m);

    friend std::ostream &operator<<(std::ostream &output, const Mission &m);
};

#endif /*MISSION_HPP*/