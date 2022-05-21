#ifndef MISSION_HPP
#define MISSION_HPP

#include "global.hpp"

class Mission
{
    public:
    int coordonates[2];
    int day;
    int start;
    int end;

    Specialties specialty;
    Skills asked_skill;
    Skills assigned_skill;
};

#endif /*MISSION_HPP*/