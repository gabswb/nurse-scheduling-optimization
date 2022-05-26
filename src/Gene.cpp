#include "Gene.hpp"

Gene::Gene(Mission m, Employee e)
{
    this->mission = m;
    this->employee = e;
    this->isAffected = true;
}

Gene::Gene()
{
    this->isAffected = false;
}

bool Gene::is_affected()
{
    return this->isAffected;
}

bool Gene::check_specialty()
{
    return this->mission.specialty == this->employee.specialty;
}

void Gene::display()
{
    printf("\n----------------Mission %d -> Employee %d----------------", this->mission.id, this->employee.id);
    printf("\nLocation: (%d, %d)", this->mission.coord_x, this->mission.coord_y);
    printf("\nDay %d from %d to %d", this->mission.day, this->mission.start_hour, this->mission.end_hour);
    printf("\nSpecialty: %d Asked skill %d", this->mission.specialty, this->mission.asked_skill);
    printf("\nEmployee spe: %d employee skill: %d", this->employee.specialty, this->employee.skill);
}