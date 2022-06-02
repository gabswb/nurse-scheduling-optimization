#include "Chromosome.hpp"
#include "global.hpp"

Chromosome::Chromosome()
{
    this->fitness = 0;
    this->employee_timetables = new std::list<Time_window> *[n_employee];
    for (int i = 0; i < n_employee; ++i){
        this->employee_timetables[i] = new std::list<Time_window>[N_WEEK_DAY];
        for(int j = 0 ; j < N_WEEK_DAY; ++j)
            this->employee_timetables[i][j] = std::list<Time_window>();
    }


    this->genes = new Gene[n_employee];
}

Chromosome Chromosome::init(Mission missions[], Employee employees[], float distances[])
{
    int mission_minutes, i, daily_working_minutes;
    int affectation_failed = 0;
    bool is_timetable_compatible, affectation_founded, availability_checked, time_window_founded;
    Time_window tm;
    std::list<Time_window>::iterator period_iterator;

    int weekly_working_minutes[n_employee] = {0};
    mission_minutes = 0;

    for (int j = 0; j < n_mission; j++)
    {
        affectation_founded = false;
        for (int k = 0; k < n_employee; k++)
        {
            printf("Debug speciality %d (employe %d)\n", j, k);
            /* Check if specialties are compatibles */
            if (employees[k].skill == missions[j].skill)
            {
                is_timetable_compatible = true;
                daily_working_minutes = 0;

                /* Check weekly working minutes */
                if (weekly_working_minutes[employees[k].id] > FULL_TIME_WOKRING_MINUTES_WEEK + WEEKLY_OVERTIME - (missions[j].end_minute - missions[j].start_minute))
                    is_timetable_compatible = false;

                /* Check timetable constraints */
                if (is_timetable_compatible)
                {
                    availability_checked = false;

                    std::cout << "debug\n";
                    for (Time_window period : this->employee_timetables[k][missions[j].day])
                    {
                        std::cout << "debug for\n";
                        std::cout << period.start << ";" << period.end << " | " << missions[j].start_minute << ";" << missions[j].end_minute << "\n";
                        /* Check availability */
                        if (
                            /* If the start mission period is during an employee mission, the mission encroaches upon an employee mission */
                            (period.start <= missions[j].start_minute &&
                             period.end > missions[j].start_minute) ||
                            /* If the end mission period is during an employee mission, the mission encroaches upon an employee mission */
                            (period.start < missions[j].end_minute &&
                             period.end >= missions[j].end_minute) ||
                            /* If the mission overtook a whole employee mission, the mission encroaches upon an employee mission*/
                            (period.start >= missions[j].start_minute &&
                             period.end <= missions[j].end_minute))
                        {
                            is_timetable_compatible = false;
                            break;
                        }

                        /* Count daily working minutes */
                        daily_working_minutes += period.end - period.end;
                    }
                    std::cout << "debug\n";
                }

                // /* Make sure that the employee has a least 1 hour lunch break */
                // if(is_timetable_compatible)
                //     if ((missions[j].start_minute >= LUNCH_BREAK_START && missions[j].start_minute <= LUNCH_BREAK_END) ||
                //         (missions[j].end_minute >= LUNCH_BREAK_START && missions[j].end_minute <= LUNCH_BREAK_END))
                //     { /* If the mission is during the lunch break time window */

                //     }
                //         lunch_break_count++;

                /* Check daily working minutes */
                if (is_timetable_compatible)
                    if (daily_working_minutes > FULL_TIME_WOKRING_MINUTES_DAY + DAILY_OVERTIME - (missions[j].end_minute - missions[j].start_minute))
                        /* With this mission, the employee would work more than the maximum allowed this day => incompatible */
                        is_timetable_compatible = false;

                std::cout << "debug\n";

                /* Check travel time (only if the employee has alreay a mission scheduled this day) */
                if (is_timetable_compatible && daily_working_minutes > 0)
                {
                }

                if (is_timetable_compatible)
                {
                    /* Gene affectation */
                    this->genes[j] = Gene(missions[j], employees[k]);
                    affectation_founded = true;

                    /* Fill the timetable */
                    time_window_founded = false;
                    std::cout << "debug aff start " << j << "->" << k << " \n";

                    if (daily_working_minutes > 0)
                    { /* If this isn't the first mission this day, we include the mission at the right window */
                        for (period_iterator = this->employee_timetables[k][missions[j].day].begin(); period_iterator != this->employee_timetables[k][missions[j].day].end(); ++period_iterator)
                        {
                            std::cout << "debug for iterator\n";
                            if ((*period_iterator).start > missions[j].start_minute)
                            {
                                Time_window tm;
                                tm.start = missions[j].start_minute;
                                tm.end = missions[j].end_minute;
                                tm.mission_id = missions[j].id;
                                this->employee_timetables[k][missions[j].day].insert(period_iterator, tm);
                                time_window_founded = true;
                                std::cout << "timewindow founded\n";

                                break;
                            }
                        }
                    }

                    if (!time_window_founded)
                    { /* this is the first mission this day or the latest of the day, we simply add it at the end*/
                        // std::cout << "not timewindow founded start\n";
                        tm.start = missions[j].start_minute;
                        tm.end = missions[j].end_minute;
                        tm.mission_id = missions[j].id;
                        // std::cout << "test" << missions[j].day << " " << this->employee_timetables[k][missions[j].day].capacity() << "\n";
                        // std::cout << "tm" << tm.start << " " << tm.end << " " << tm.mission_id << "\n";

                        // std::cout << this->employee_timetables[k][missions[j].day].front().mission_id;
                        this->employee_timetables[k][missions[j].day].push_back(tm);
                        // std::cout << "not timewindow founded end\n";
                    }
                    std::cout << "debug aff end\n";

                    /* Increment weekly working minutes count */
                    weekly_working_minutes[employees[k].id] += missions[j].end_minute - missions[j].start_minute;

                    /* "Break" for-loop */
                    this->display_timetable(this->employee_timetables[k]);
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
    // int i = 0,
    //     j = 0;
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

    // /* Check timetable constraints */
    // for (i = 0; i < n_employee; i++)
    // {
    //     for (j = 0; j < N_WEEK_DAY; j++)
    //     {
    //         /* Check that employees have at least one minute lunch break every day (btw 12am and 2 pm) */
    //         if (this->employee_timetables[i][j][LUNCH_BREAK_1] >= 0 && this->employee_timetables[i][j][LUNCH_BREAK_2] >= 0)
    //             /* Not valid, the employee is working during the full lunch break */
    //             return false;
    //     }
    // }

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
    }
}

void Chromosome::display_timetable(std::list<Time_window> *timetable_p)
{
    int i;
    printf("\n    ");
    for (int k = START_HOUR; k < END_HOUR; ++k)
    {
        if (k < 10)
            printf("%d  |  ", k);
        else
            printf("%d |  ", k);
    }
    printf("\n");
    for (int j = MONDAY; j < N_WEEK_DAY + MONDAY; ++j)
    {
        printf("\n%d   ", j);
        // printf("debug\n");
        i = START_HOUR * 60;
        for (Time_window mission_time_window : timetable_p[j-MONDAY])
        {
            printf("debug\n");
            for (; i < mission_time_window.start; i += 10)
                printf(" ");
            printf("%d", mission_time_window.mission_id);
            if (mission_time_window.mission_id < 10)
                i += 10;
            else if (mission_time_window.mission_id < 100)
                i += 20;
            else
                i += 30;

            for (; i < mission_time_window.end; i += 10)
            {
                printf("-");
            }
        }
    }
    std::cout << "\n";
}

Chromosome::~Chromosome()
{
    for (int i = 0; i < n_employee; i++)
        delete[] this->employee_timetables[i];
    delete[] this->employee_timetables;
    std::cout << "\nFree memory";
}