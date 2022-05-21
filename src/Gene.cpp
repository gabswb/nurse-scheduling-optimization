#include "Gene.hpp"

Gene::Gene()
{
    this->isAffected = false;
}

Gene::Gene(Mission m, Employee e)
{
    this->mission = m;
    this->employee = e;
    this->isAffected = true;
}

bool Gene::is_affected()
{
    return this->isAffected;
}

bool Gene::check_specialty()
{
    return this->mission.specialty == this->employee.specialty;
}