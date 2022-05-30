#include "Chromosome.hpp"
#include "global.hpp"

Chromosome::Chromosome()
{
        this->fitness = 0;
        /* Initialize every timetables to -1, which means free */
        for (int i = 0; i < n_employee; i++)
                for (int j = 0; j < N_WEEK_DAY; j++)
                        for (int k = 0; k < N_WORKING_HOURS; k++)
                                this->employee_timetables[i][j][k] = -1;
}




void Chromosome::initial_solution(Mission missions[], Employee employees[], float distances[])
{
        this->genes = new Gene[n_mission];
        int weekly_working_minutes[n_employee] = {0};
        int mission_minutes, i, lunch_break_count, working_minutes;
        int affectation_failed = 0;
        bool is_timetable_compatible, affectation_founded;

        for(int i = 0 ; i < n_mission ; ++i)
        {
                for(int j = 0 ; j < n_employee ; ++j)
                {
                        if(missions[i].specialty == employees[i].specialty)
                        {
                                is_timetable_compatible = true;
                                working_minutes = 0;

                                /* Check weekly working minutes */
                                if (weekly_working_minutes[employees[j].id] > FULL_TIME_WOKRING_MINUTES_WEEK + WEEKLY_OVERTIME - (missions[i].end_minute - missions[j].start_minute))
                                        is_timetable_compatible = false;
                                
                                /* Check timetable constraints */
                                if (is_timetable_compatible)
                                for (i = missions[j].start_minute; i < missions[j].end_minute; i++)
                                {
                                        /* Check availability */
                                        if (this->employee_timetables[employees[k].id][missions[j].day][i] >= 0)
                                                is_timetable_compatible = false;

                                        /* Make sure that the employee has a least 1 minute lunch break */
                                        if (i == LUNCH_BREAK_1 || i == LUNCH_BREAK_2)
                                                lunch_break_count++;
                                        if (lunch_break_count > 1)
                                        {
                                                is_timetable_compatible = false;
                                                i = missions[j].end_minute;
                                        }
                                }

                        }
                }
                
                this->genes[i] = Gene()
        }
}





























Chromosome Chromosome::init(Mission missions[], Employee employees[], float distances[])
{
        int mission_minutes, i, lunch_break_count, working_minutes;
        int affectation_failed = 0;
        bool is_timetable_compatible, affectation_founded;

        int weekly_working_minutes[n_employee] = {0};
        mission_minutes = 0;

        for (int j = 0; j < n_mission; j++)
        {
                affectation_founded = false;
                for (int k = 0; k < n_employee; k++)
                {
                        /* Check if specialties are compatibles */
                        if (employees[k].specialty == missions[j].specialty)
                        {
                                lunch_break_count = 0;
                                is_timetable_compatible = true;
                                working_minutes = 0;

                                /* Check weekly working minutes */
                                if (weekly_working_minutes[employees[k].id] > FULL_TIME_WOKRING_HOURS_WEEK + WEEKLY_OVERTIME - (missions[j].end_minute - missions[j].start_minute))
                                        is_timetable_compatible = false;

                                /* Check timetable constraints */
                                if (is_timetable_compatible)
                                        for (i = missions[j].start_minute; i < missions[j].end_minute; i++)
                                        {
                                                /* Check availability */
                                                if (this->employee_timetables[employees[k].id][missions[j].day][i] >= 0)
                                                        is_timetable_compatible = false;

                                                /* Make sure that the employee has a least 1 minute lunch break */
                                                if (i == LUNCH_BREAK_1 || i == LUNCH_BREAK_2)
                                                        lunch_break_count++;
                                                if (lunch_break_count > 1)
                                                {
                                                        is_timetable_compatible = false;
                                                        i = missions[j].end_minute;
                                                }
                                        }

                                /* If the mission takes place during a lunch break, make sure that the other is free to have at least 1 jour lunch break */
                                if (is_timetable_compatible &&
                                    lunch_break_count > 0 &&
                                    (this->employee_timetables[employees[k].id][missions[j].day][LUNCH_BREAK_1] >= 0 ||
                                     this->employee_timetables[employees[k].id][missions[j].day][LUNCH_BREAK_2] >= 0))
                                        is_timetable_compatible = false;

                                /* Check daily working minutes */
                                if (is_timetable_compatible)
                                        for (i = 0; i < N_WORKING_HOURS; i++)
                                        {
                                                if (this->employee_timetables[employees[k].id][missions[j].day][i] >= 0)
                                                        working_minutes++;
                                                if (working_minutes > FULL_TIME_WOKRING_HOURS_DAY + DAILY_OVERTIME - (missions[j].end_minute - missions[j].start_minute))
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
                                        for (i = missions[j].start_minute; i < missions[j].end_minute; i++)
                                        {
                                                this->employee_timetables[employees[k].id][missions[j].day][i] = missions[j].id;
                                        }

                                        /* Increment weekly working minutes count */
                                        weekly_working_minutes[employees[k].id] += missions[j].end_minute - missions[j].start_minute;

                                        /* "Break" for-loop */
                                        k = n_employee;
                                }
                        }
                }
                if (!affectation_founded)
                {
                        printf("\n\t*****Affectation impossible*****");
                        affectation_failed++;
                }
                mission_minutes += missions[j].end_minute - missions[j].start_minute;
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
        //         for (i = gene.mission.start_minute; i < gene.mission.end_minute; i++)
        //         {
        //                 if (this->employee_timetables[gene.employee.id][gene.mission.day][i])
        //                         /* Not valid if the employee is already working during these working minutes */
        //                         return false;
        //                 else
        //                         this->employee_timetables[gene.employee.id][gene.mission.day][i] = true;
        //         }
        // }

        /* Check timetable constraints */
        for (i = 0; i < n_employee; i++)
        {
                for (j = 0; j < N_WEEK_DAY; j++)
                {
                        /* Check that employees have at least one minute lunch break every day (btw 12am and 2 pm) */
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
        for (i = 0; i < n_mission; i++)
                this->genes[i].display();

        for (i = 0; i < n_employee; i++)
        {
                printf("\n\n\tEmloyee %d", i);
                display_timetable(this->employee_timetables[i]);
                // std::cout << "\nWeekly working minutes : " << weekly_working_minutes[i];
                // working_minutes += weekly_working_minutes[i];
        }

        // std::cout << "\ntotal working minutes: " << working_minutes;
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