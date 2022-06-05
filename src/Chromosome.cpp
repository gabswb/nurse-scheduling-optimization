#include "Chromosome.hpp"

Chromosome::Chromosome(Employee employees[], float distances[])
{
    this->fitness = 0;
    this->genes = new Gene[n_mission];
    this->employee_timetables = new std::vector<Time_window> [n_employee*N_WEEK_DAY];
    for(int i=0; i<n_employee*N_WEEK_DAY;++i){
        employee_timetables[i].reserve(n_mission/(N_WEEK_DAY*n_employee));//reserve de la mémoire en supposant que les missions seront réparties uniformément par employé et par jour
    }

    alpha = 100/n_mission;
    beta = 100/ (N_WORKING_HOURS+WEEKLY_OVERTIME)  ;
    for(int i=0; i<n_employee; ++i){
        gamma+=employees[i].quota;
    }
    gamma = 100/gamma;
    zeta = 100/WEEKLY_OVERTIME;
    for(int i=0; i<n_location;++i){
        kappa += distances[0*n_location + 1] + distances[i*n_location + 0];
    }
    kappa = 100/(kappa/n_employee); 
}

bool time_window_compare(const Time_window &a, const Time_window &b)
{
    return a.start < b.start;
};

void Chromosome::initialize(Mission missions[], Employee employees[], float distances[])
{
    int mission_minutes, daily_working_minutes;
    int affectation_failed = 0;
    bool is_timetable_compatible, affectation_founded, availability_checked, time_window_founded;
    std::vector<Time_window>::iterator period_iterator;

    int weekly_working_minutes[n_employee] = {0};
    mission_minutes = 0;
    std::cout << this->employee_timetables[4].size() << std::endl;

    for (int j = 0; j < n_mission; j++)
    {
        affectation_founded = false;
        for (int k = 0; k < n_employee; k++)
        {
            auto& current_vector = employee_timetables[(k)*N_WEEK_DAY + missions[j].day];
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


                    for(Time_window tw : current_vector){
                        if(missions[j].start_minute < tw.start){//mission start before tw
                            float distance = distances[(missions[j].id+1)*n_location + tw.mission_id+1];//get distance mission-->tw
                            
                            if(missions[j].end_minute + distance/TRAVEL_SPEED >= tw.start){
                                is_timetable_compatible = false;
                                break;
                            }
                        }
                        else{//tw start before mission
                            float distance = distances[(tw.mission_id+1)*n_location + missions[j].id+1];//get distance tw-->mission

                            if((missions[j].start_minute + distance/TRAVEL_SPEED) <= tw.end){
                                is_timetable_compatible = false;
                                break;
                            }
                        }
                    }
                }

                /* Make sure that the employee has a least 1 hour lunch break */
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


                /* Check travel time (only if the employee has alreay a mission scheduled this day) */
                if (is_timetable_compatible && daily_working_minutes > 0)
                {
                }

                if (is_timetable_compatible){
                    /* Gene affectation */
                    this->genes[j] = Gene(missions[j], employees[k]);
                    affectation_founded = true;

                    /* Fill the timetable */
                    time_window_founded = false;

                    /* Affectation */
                    Time_window tm;
                    tm.start = missions[j].start_minute;
                    tm.end = missions[j].end_minute;
                    tm.mission_id = missions[j].id;
                    current_vector.push_back(tm);

                    if (daily_working_minutes > 0) /* If this isn't the first mission this day, we sort the list */
                        std::sort(current_vector.begin(), current_vector.end(), time_window_compare);

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

float Chromosome::evaluate(float distances[], Employee employees[])
{
    float fitness=0, delta_time, employee_worktime, temp_distance;
    float stdev_wasted_hours=0, stdev_overtime=0, stdev_distances=0;//standard derivations
    float sum_wasted_hours=0, sum_overtime=0, sum_distances=0;//sums
    float sum2_wasted_hours=0, sum2_overtime=0, sum2_distances=0;//quadratic sums

    //compute in one pass the sum and the quadratic sum of wasted hours, overtime and distances 
    for(int i=0; i<n_employee; ++i){
        employee_worktime=0;
        for(int j=0; j<N_WEEK_DAY; ++j){

            auto &vec = employee_timetables[i*n_employee + j];//reference on current vector for more readability
            for(size_t k=0; k<vec.size(); ++k)
            {
                temp_distance = distances[vec[k+1].mission_id*n_location + vec[k+2].mission_id];//distance form i to i+1

                delta_time =  vec[k+1].start - temp_distance/TRAVEL_SPEED - vec[k].start; //start time of i+1 - travel time from i-->i+1 - end time of i
                sum_wasted_hours += delta_time;
                sum2_wasted_hours += pow(delta_time,2);

                employee_worktime += vec[k].end - vec[k].start;

                sum_distances += temp_distance;
                sum2_distances += pow(temp_distance,2);

            }
        }
        sum_overtime += employee_worktime - employees[i].quota;
        sum2_overtime += pow(employee_worktime - employees[i].quota, 2);
    }

    //compute the standart derivation = E(X²)-E(X)², X the wasted hours, overtime and distances
    stdev_wasted_hours = sqrt(sum2_wasted_hours/n_employee - pow(sum_wasted_hours/n_employee,2));
    stdev_overtime = sqrt(sum2_overtime/n_employee - pow(sum_overtime/n_employee,2));
    stdev_distances = sqrt(sum2_distances/n_employee - pow(sum_distances/n_employee,2));

    fitness = (zeta*stdev_wasted_hours + gamma*stdev_overtime + kappa*stdev_distances)/3;
    return fitness;
}





std::ostream &operator<<(std::ostream &output, Chromosome &c)
{
    for (int i=0; i < n_mission; ++i)
        output<< c.genes[i];

    for (int i=0; i < n_employee; ++i)
        c.print_employee_timetable(i);
    
    return output;
}

void Chromosome::print_employee_timetable(int employee)
{
    int i;
    printf("\n------------------Emloyee %d------------------", employee);
    printf("\n    ");
    for (int k = START_HOUR; k < END_HOUR; ++k)
    {
        if (k < 10)
            std::cout << k << "  |  ";
        else
            std::cout << k << " |  ";
    }
    std::cout << "\n";
    for (int j = MONDAY; j < N_WEEK_DAY + MONDAY; ++j)
    {
        std::cout << "\n" << j << "   ";
        i = START_HOUR * 60;
        for (Time_window mission_time_window : this->employee_timetables[employee*N_WEEK_DAY + j])
        {
            // printf("debug\n");
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
    std::cout << std::endl;
}

Chromosome::~Chromosome()
{
    delete[] this->employee_timetables;
}