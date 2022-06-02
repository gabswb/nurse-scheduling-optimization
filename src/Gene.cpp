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
    printf("\nDay %d from %d to %d", this->mission.day, this->mission.start_minute, this->mission.end_minute);
    printf("\nSpecialty: %d Asked skill %d", this->mission.specialty, this->mission.skill);
    printf("\nEmployee spe: %d employee skill: %d", this->employee.specialty, this->employee.skill);
}