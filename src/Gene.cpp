void Gene::is_affected()
{
    return this.mission != nullptr && this.employee != nullptr;
}

void Gene::check_specialty()
{
    return this.mission.specialty == this.employee.specialty;
}
