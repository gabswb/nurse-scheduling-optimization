#include "Gene.hpp"

Gene::Gene(Mission m, Employee e)
{
    this->mission = m;
    this->employee = e;
    this->is_assigned = true;
}

Gene::Gene()
{
    this->is_assigned = false;
}


bool Gene::check_specialty()
{
    return this->mission.specialty == this->employee.specialty;
}

std::ostream &operator<<(std::ostream &output, const Gene &g)
{
    output <<"\n----------------Mission "<< g.mission.id<<" Employee "<< g.employee.id<< "----------------\n"
            <<"Day "<< g.mission.day<< " from "<< g.mission.start_minute<< " to "<< g.mission.end_minute<< "\n"
            <<"Specialty: "<< g.mission.specialty<< " Asked skill "<< g.mission.skill<< "\n"
            <<"Employee spe: "<< g.employee.specialty<< " employee skill: "<< g.employee.skill<< std::endl;
    return output;
}