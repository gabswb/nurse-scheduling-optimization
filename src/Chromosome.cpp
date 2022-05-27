#include "Chromosome.hpp"
#include "global.hpp"

Chromosome::Chromosome()
{
        this->fitness = 0;
        /* Initialize every timetables to -1, which means free */
        for (int i = 0; i < NB_EMPLOYEE; i++)
                for (int j = 0; j < N_WEEK_DAY; j++)
                        for (int k = 0; k < N_WORKING_HOURS; k++)
                                this->employee_timetables[i][j][k] = -1;
}

Chromosome Chromosome::init(Mission missions[NB_MISSION], Employee employees[NB_EMPLOYEE], int distances[NB_MISSION + 1][NB_MISSION + 1])
{
        int mission_hours, i, lunch_break_count, working_hours;
        int affectation_failed = 0;
        bool is_timetable_compatible, affectation_founded;

        int weekly_working_hours[NB_EMPLOYEE] = {0};
        mission_hours = 0;

        for (int j = 0; j < NB_MISSION; j++)
        {
                affectation_founded = false;
                for (int k = 0; k < NB_EMPLOYEE; k++)
                {
                        /* Check if specialties are compatibles */
                        if (employees[k].specialty == missions[j].specialty)
                        {
                                lunch_break_count = 0;
                                is_timetable_compatible = true;
                                working_hours = 0;

                                /* Check weekly working hours */
                                if (weekly_working_hours[employees[k].id] > FULL_TIME_WOKRING_HOURS_WEEK + WEEKLY_OVERTIME - (missions[j].end_hour - missions[j].start_hour))
                                        is_timetable_compatible = false;

                                /* Check timetable constraints */
                                if (is_timetable_compatible)
                                        for (i = missions[j].start_hour; i < missions[j].end_hour; i++)
                                        {
                                                /* Check availability */
                                                if (this->employee_timetables[employees[k].id][missions[j].day][i] >= 0)
                                                        is_timetable_compatible = false;

                                                /* Make sure that the employee has a least 1 hour lunch break */
                                                if (i == LUNCH_BREAK_1 || i == LUNCH_BREAK_2)
                                                        lunch_break_count++;
                                                if (lunch_break_count > 1)
                                                {
                                                        is_timetable_compatible = false;
                                                        i = missions[j].end_hour;
                                                }
                                        }

                                /* If the mission takes place during a lunch break, make sure that the other is free to have at least 1 jour lunch break */
                                if (is_timetable_compatible &&
                                    lunch_break_count > 0 &&
                                    (this->employee_timetables[employees[k].id][missions[j].day][LUNCH_BREAK_1] >= 0 ||
                                     this->employee_timetables[employees[k].id][missions[j].day][LUNCH_BREAK_2] >= 0))
                                        is_timetable_compatible = false;

                                /* Check daily working hours */
                                if (is_timetable_compatible)
                                        for (i = 0; i < N_WORKING_HOURS; i++)
                                        {
                                                if (this->employee_timetables[employees[k].id][missions[j].day][i] >= 0)
                                                        working_hours++;
                                                if (working_hours > FULL_TIME_WOKRING_HOURS_DAY + DAILY_OVERTIME - (missions[j].end_hour - missions[j].start_hour))
                                                {
                                                        /* With this mission, the employee would work more than FULL_TIME_WOKRING_HOURS_DAY this day => incompatible */
                                                        is_timetable_compatible = false;
                                                        i = N_WORKING_HOURS;
                                                }
                                        }

                                if (is_timetable_compatible)
                                {
                                        /* Gene affectation */
                                        this->genes[j] = Gene(missions[j], employees[k]);
                                        affectation_founded = true;

                                        /* Fill the timetable */
                                        for (i = missions[j].start_hour; i < missions[j].end_hour; i++)
                                        {
                                                this->employee_timetables[employees[k].id][missions[j].day][i] = missions[j].id;
                                        }

                                        /* Increment weekly working hours count */
                                        weekly_working_hours[employees[k].id] += missions[j].end_hour - missions[j].start_hour;

                                        /* "Break" for-loop */
                                        k = NB_EMPLOYEE;
                                }
                        }
                }
                if (!affectation_founded)
                {
                        printf("\n\t*****Affectation impossible*****");
                        affectation_failed++;
                }
                mission_hours += missions[j].end_hour - missions[j].start_hour;
        }
        std::cout << "\nAffectation failed: " << affectation_failed;

        return *this;
}

bool Chromosome::is_valid()
{
        int i = 0,
            j = 0;
        // TODO a finir
        // for (Gene gene : this->genes)
        // {
        //         /* Check that each mission is affected (and is realized by only emlpoyee) and has the right speciality */
        //         if (!gene.is_affected() && !gene.check_specialty())
        //                 return false;

        //         /* Fill the employe timetables */
        //         for (i = gene.mission.start_hour; i < gene.mission.end_hour; i++)
        //         {
        //                 if (this->employee_timetables[gene.employee.id][gene.mission.day][i])
        //                         /* Not valid if the employee is already working during these working hours */
        //                         return false;
        //                 else
        //                         this->employee_timetables[gene.employee.id][gene.mission.day][i] = true;
        //         }
        // }

        /* Check timetable constraints */
        for (i = 0; i < NB_EMPLOYEE; i++)
        {
                for (j = 0; j < N_WEEK_DAY; j++)
                {
                        /* Check that employees have at least one hour lunch break every day (btw 12am and 2 pm) */
                        if (this->employee_timetables[i][j][LUNCH_BREAK_1] >= 0 && this->employee_timetables[i][j][LUNCH_BREAK_2] >= 0)
                                /* Not valid, the employee is working during the full lunch break */
                                return false;
                }
        }

        return true;
}

void Chromosome::display()
{
        int i;
        for (i = 0; i < NB_MISSION; i++)
                this->genes[i].display();

        for (i = 0; i < NB_EMPLOYEE; i++)
        {
                printf("\n\n\tEmloyee %d", i);
                display_timetable(this->employee_timetables[i]);
                // std::cout << "\nWeekly working hours : " << weekly_working_hours[i];
                // working_hours += weekly_working_hours[i];
        }

        // std::cout << "\ntotal working hours: " << working_hours;
}

void Chromosome::display_timetable(int timetable_p[N_WEEK_DAY][N_WORKING_HOURS])
{
        printf("\n    Mon Tue Wed Thu Fri Sat");
        for (int k = 0; k < N_WORKING_HOURS; k++)
        {

                if (k == LUNCH_BREAK_1 || k == LUNCH_BREAK_2)
                        printf("\nL%d: ", k);
                else if (k < 10)
                        printf("\n%d:  ", k);
                else
                        printf("\n%d: ", k);
                for (int j = 0; j < N_WEEK_DAY; j++)
                        if (timetable_p[j][k] < 0)
                                printf("-    ");
                        else if (timetable_p[j][k] < 10)
                                printf("%d    ", timetable_p[j][k]);
                        else if (timetable_p[j][k] < 100)
                                printf("%d   ", timetable_p[j][k]);
                        else
                                printf("%d  ", timetable_p[j][k]);
        }
}