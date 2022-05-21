#include "Chromosome.hpp"
#include "global.hpp"

bool Chromosome::is_valid()
{
    int i = 0,
        j = 0;
    /**
     * @brief Defines whenever an employee is working or not
     * Each week has N_WEEk_DAY days
     * Each day has N_WORKING_HOURS_SLOT working hours (from 8 am to 7 pm for instance)
     *  
     */
    bool employeTimetable[n_employees][N_WEEk_DAY][N_WORKING_HOURS_SLOT];
    
    for(Gene gene : this->genes)
    {
        /* Check that each mission is affected (and is realized by only emlpoyee) and has the right speciality */
        if(!gene.is_affected() && !gene.check_specialty())
            return false;

        /* Fill the employe timetables */
        for(i = gene.mission.start ; i < gene.mission.end; i ++ )
        {
            if(employeTimetable[gene.employee.id][gene.mission.day][i])
                /* Not valid if the employee is already working during these working hours */
                return false;
            else
                employeTimetable[gene.employee.id][gene.mission.day][i] = true;
        }
    }

    /* Check timetable constraints */
    for(i = 0; i < n_employees ; i++ )
    {
        for(j = 0 ; j < N_WEEk_DAY ; j++)
        {
            /* Check that employees have at least one hour lunch break every day (btw 12am and 2 pm) */
            if(employeTimetable[i][j][LUNCH_BREAK_1] && employeTimetable[i][j][LUNCH_BREAK_2])
                /* Not valid, the employee is working during the full lunch break */
                return false;
        }
    }

    return true;
}