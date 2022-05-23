#include "Chromosome.hpp"
#include "global.hpp"

Chromosome::Chromosome()
{
        this->size = 0;
        this->fitness = 0;
        this->n_employees = 0;
}

Chromosome::Chromosome(std::vector<Gene> genes_p, int n_employees_p)
{
        this->size = genes.size();
        this->fitness = 0;
        this->n_employees = n_employees_p;
        this->genes = genes_p;
}

std::vector<Gene> Chromosome::init(std::vector<Mission> missions, std::vector<Employee> employees)
{
        std::vector<Gene> genes;
        std::vector<Gene>::iterator itGe;
        std::vector<Employee>::iterator itEm;
        std::vector<Mission>::iterator itMi;
        int mission_hours, i, lunch_break_count, working_hours;
        int affectation_failed = 0;
        bool is_timetable_compatible, affectation_founded;

        bool employee_timetables[employees.size()][N_WEEK_DAY][N_WORKING_HOURS_SLOT] = {false};
        int weekly_working_hours[employees.size()] = {0};
        mission_hours = 0;

        for (itMi = missions.begin(); itMi < missions.end(); itMi++)
        {
                affectation_founded = false;
                for (itEm = employees.begin(); itEm < employees.end(); itEm++)
                {
                        /* Check if specialty compatible */
                        if (itEm->specialty == itMi->specialty)
                        {
                                lunch_break_count = 0;
                                is_timetable_compatible = true;
                                working_hours = 0;

                                /* Check weekly working hours */
                                if (weekly_working_hours[itEm->id] > FULL_TIME_WOKRING_HOURS_WEEK + WEEKLY_OVERTIME - (itMi->end_hour - itMi->start_hour))
                                        is_timetable_compatible = false;

                                /* Check timetable constraints */
                                if (is_timetable_compatible)
                                        for (i = itMi->start_hour; i < itMi->end_hour; i++)
                                        {
                                                /* Availability */
                                                if (employee_timetables[itEm->id][itMi->day][i])
                                                        is_timetable_compatible = false;

                                                /* Make sure that the employee has a least 1 hour lunch break */
                                                if (i == LUNCH_BREAK_1 || i == LUNCH_BREAK_2)
                                                        lunch_break_count++;
                                                if (lunch_break_count > 1)
                                                {
                                                        is_timetable_compatible = false;
                                                        i = itMi->end_hour;
                                                }
                                        }

                                /* Check daily working hours */
                                if (is_timetable_compatible)
                                        for (i = 0; i < N_WORKING_HOURS_SLOT; i++)
                                        {
                                                if (employee_timetables[itEm->id][itMi->day][i])
                                                        working_hours++;
                                                if (working_hours > FULL_TIME_WOKRING_HOURS_DAY + DAILY_OVERTIME - (itMi->end_hour - itMi->start_hour))
                                                {
                                                        /* With this mission, the employee would work more than FULL_TIME_WOKRING_HOURS_DAY this day => incompatible */
                                                        is_timetable_compatible = false;
                                                        i = N_WORKING_HOURS_SLOT;
                                                }
                                        }

                                if (is_timetable_compatible)
                                {
                                        /* Affectation */
                                        itGe = genes.insert(itGe, Gene(*itMi, *itEm));
                                        affectation_founded = true;

                                        /* Fill the timetable */
                                        for (i = itMi->start_hour; i < itMi->end_hour; i++)
                                        {
                                                employee_timetables[itEm->id][itMi->day][i] = true;
                                        }

                                        /* Increment weekly working hours count */
                                        weekly_working_hours[itEm->id] += itMi->end_hour - itMi->start_hour;

                                        /* "Break" for-loop */
                                        itEm = employees.end();
                                }
                        }
                }
                if (!affectation_founded)
                {
                        printf("\n\t*****Affectation impossible*****");
                        affectation_failed++;
                }
                else
                        itGe->display();
                mission_hours += itMi->end_hour - itMi->start_hour;
        }

        working_hours = 0;
        for (i = 0; i < employees.size(); i++)
        {
                printf("\n\n\tEmloyee %d", i);
                display_timetable(employee_timetables[i]);
                std::cout << "\nWeekly working hours : " << weekly_working_hours[i];
                working_hours += weekly_working_hours[i];
        }
        
        std::cout << "\ntotal mission hours: " << mission_hours;
        std::cout << "\ntotal working hours: " << working_hours;
        std::cout << "\nAffectation failed: " << affectation_failed;

        return genes;
}

bool Chromosome::is_valid()
{
        int i = 0,
            j = 0;
        /**
         * @brief Defines whenever an employee is working or not
         * Each week has N_WEEK_DAY days
         * Each day has N_WORKING_HOURS_SLOT working hours (from 8 am to 7 pm for instance)
         *
         */
        bool employee_timetables[n_employees][N_WEEK_DAY][N_WORKING_HOURS_SLOT];

        for (Gene gene : this->genes)
        {
                /* Check that each mission is affected (and is realized by only emlpoyee) and has the right speciality */
                if (!gene.is_affected() && !gene.check_specialty())
                        return false;

                /* Fill the employe timetables */
                for (i = gene.mission.start_hour; i < gene.mission.end_hour; i++)
                {
                        if (employee_timetables[gene.employee.id][gene.mission.day][i])
                                /* Not valid if the employee is already working during these working hours */
                                return false;
                        else
                                employee_timetables[gene.employee.id][gene.mission.day][i] = true;
                }
        }

        /* Check timetable constraints */
        for (i = 0; i < n_employees; i++)
        {
                for (j = 0; j < N_WEEK_DAY; j++)
                {
                        /* Check that employees have at least one hour lunch break every day (btw 12am and 2 pm) */
                        if (employee_timetables[i][j][LUNCH_BREAK_1] && employee_timetables[i][j][LUNCH_BREAK_2])
                                /* Not valid, the employee is working during the full lunch break */
                                return false;
                }
        }

        return true;
}

void Chromosome::display()
{
}

void Chromosome::display_timetable(bool timetable_p[N_WEEK_DAY][N_WORKING_HOURS_SLOT])
{
        printf("\n    Mon Tue Wed Thu Fri Sat");
        for (int k = 0; k < N_WORKING_HOURS_SLOT; k++)
        {

                if (k == LUNCH_BREAK_1 || k == LUNCH_BREAK_2)
                        printf("\nL%d: ", k);
                else if (k < 10)
                        printf("\n%d:  ", k);
                else
                        printf("\n%d: ", k);
                for (int j = 0; j < N_WEEK_DAY; j++)
                        printf("%d   ", timetable_p[j][k]);
        }
}