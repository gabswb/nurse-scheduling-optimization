#include "Chromosome.hpp"

Chromosome::Chromosome() : fitness(0)
{
    this->employee_timetables = new std::vector<Time_window>[n_employee * N_WEEK_DAY];
}


Chromosome::Chromosome(const Chromosome &chr) 
{
    this->genes = new Gene[n_mission];
    this->fitness = chr.fitness;
    this->genes = chr.genes;
    this->missions = chr.missions;
    this->employees = chr.employees;
    this->distances = chr.distances;
    this->alpha = chr.alpha;
    this->beta = chr.beta;
    this->gamma = chr.gamma;
    this->zeta = chr.zeta;
    this->kappa = chr.kappa;
    this->employee_timetables = new std::vector<Time_window>[n_employee * N_WEEK_DAY];
    for(int i = 0 ; i < n_employee * N_WEEK_DAY; ++i)
        this->employee_timetables[i] = chr.employee_timetables[i];
}

Chromosome& Chromosome::operator=(const Chromosome &chr)
{
    this->genes = new Gene[n_mission];
    this->fitness = chr.fitness;
    this->genes = chr.genes;
    this->missions = chr.missions;
    this->employees = chr.employees;
    this->distances = chr.distances;
    this->alpha = chr.alpha;
    this->beta = chr.beta;
    this->gamma = chr.gamma;
    this->zeta = chr.zeta;
    this->kappa = chr.kappa;
    this->employee_timetables = new std::vector<Time_window>[n_employee * N_WEEK_DAY];
    for(int i = 0 ; i < n_employee * N_WEEK_DAY; ++i)
        this->employee_timetables[i] = chr.employee_timetables[i];
    return *this;
}

Chromosome::Chromosome(const Mission missions_p[], const Employee employees_p[], const float distances_p[])
{
    this->fitness = 0;
    this->genes = new Gene[n_mission];
    this->employee_timetables = new std::vector<Time_window>[n_employee * N_WEEK_DAY];
    this->missions = missions_p;
    this->employees = employees_p;
    this->distances = distances_p;

    /* Allocate memory */

    for (int i = 0; i < n_employee * N_WEEK_DAY; ++i)
    {
        employee_timetables[i].reserve(n_mission / (N_WEEK_DAY * n_employee)); // reserve memory assuming that missions are uniformly distributed by employee and day
    }

    /* Compute fitness correlation coefficient */

    alpha = 100 / n_mission;
    beta = 100 / (FULL_TIME_WOKRING_MINUTES_WEEK/60 + WEEKLY_OVERTIME/60);
    zeta = 0;
    for (int i = 0; i < n_employee; ++i){
        zeta += employees[i].quota/60;
    }
    zeta = 100 / (zeta / n_employee);
    gamma = 100 / (WEEKLY_OVERTIME/60);
    for (int i = 0; i < n_location; ++i){
        kappa += distances_p[0 * n_location + i] + distances_p[i * n_location + 0];
    }
    kappa = 100 / (kappa / n_employee);
}

void Chromosome::initialize()
{
    int daily_working_minutes, lunch_break_working_time, start_lunch_break, end_lunch_break;
    int affectation_failed = 0;
    float distance;
    bool is_timetable_compatible, affectation_founded;

    int weekly_working_minutes[n_employee] = {0};

    for (int j = 0; j < n_mission; j++)
    {
        affectation_founded = false;
        for (int k = 0; k < n_employee; k++)
        {
            auto &employee_timetable_day_j = employee_timetables[(employees[k].id)*N_WEEK_DAY + missions[j].day];
            /* Check if specialties are compatibles */
            if (employees[k].skill == missions[j].skill)
            {
                is_timetable_compatible = true;
                daily_working_minutes = 0;
                lunch_break_working_time = 0;

                /* Check weekly working minutes */
                if (weekly_working_minutes[employees[k].id] > FULL_TIME_WOKRING_MINUTES_WEEK + WEEKLY_OVERTIME - (missions[j].end_minute - missions[j].start_minute))
                    is_timetable_compatible = false;

                /* Check timetable constraints */
                if (is_timetable_compatible)
                {
                    for (Time_window tw : employee_timetable_day_j)
                    {
                        /* Count daily working minutes */
                        daily_working_minutes += (tw.end - tw.start);
                        
                        /* Store lunch break working time (to check later that the employee has a least 1 hour lunch break) */
                        if ((tw.start >= LUNCH_BREAK_START && tw.start <= LUNCH_BREAK_END) ||
                            (tw.end >= LUNCH_BREAK_START && tw.end <= LUNCH_BREAK_END) ||
                            (tw.start <= LUNCH_BREAK_START && tw.end >= LUNCH_BREAK_END))
                        {
                            if (tw.start > LUNCH_BREAK_START)
                                start_lunch_break = tw.start;
                            else
                                start_lunch_break = LUNCH_BREAK_START;

                            if (tw.end < LUNCH_BREAK_END)
                                end_lunch_break = tw.end;
                            else
                                end_lunch_break = LUNCH_BREAK_END;

                            lunch_break_working_time += end_lunch_break - start_lunch_break;
                        }

                        /* Test if employee is available and has enough travel time to arrive before the mission start and leave to arrive at the next mission on time */

                        if (missions[j].start_minute < tw.start)
                        {    
                            distance = distances[(missions[j].id + 1) * n_location + tw.mission_id + 1]; // get distance mission-->tw
                            if (missions[j].end_minute + distance / TRAVEL_SPEED >= tw.start) {   
                                is_timetable_compatible = false;
                                break;
                            }
                        }
                        else
                        {                                                                                // tw start before mission
                            distance = distances[(tw.mission_id + 1) * n_location + missions[j].id + 1]; // get distance tw-->mission                         
                            //if ((missions[j].start_minute + distance / TRAVEL_SPEED) <= tw.end)
                            if(tw.end + distance/TRAVEL_SPEED >= missions[j].start_minute)
                            {
                                is_timetable_compatible = false;
                                break;
                            }
                        }
                    }
                }

                /* Make sure that the employee has a least 1 hour lunch break */
                if (is_timetable_compatible)
                    if ((missions[j].start_minute >= LUNCH_BREAK_START && missions[j].start_minute <= LUNCH_BREAK_END) ||
                        (missions[j].end_minute >= LUNCH_BREAK_START && missions[j].end_minute <= LUNCH_BREAK_END) ||
                        (missions[j].start_minute <= LUNCH_BREAK_START && missions[j].end_minute >= LUNCH_BREAK_END))
                    { /* If the mission is during the lunch break time window */
                        if (missions[j].start_minute > LUNCH_BREAK_START)
                            start_lunch_break = missions[j].start_minute;
                        else
                            start_lunch_break = LUNCH_BREAK_START;

                        if (missions[j].end_minute < LUNCH_BREAK_END)
                            end_lunch_break = missions[j].end_minute;
                        else
                            end_lunch_break = LUNCH_BREAK_END;

                        lunch_break_working_time += end_lunch_break - start_lunch_break;

                        if ((LUNCH_BREAK_END - LUNCH_BREAK_START) - lunch_break_working_time < LUNCH_BREAK_TIME)
                        {
                            is_timetable_compatible = false;
                            std::cout << "mission " << j << "and employee " << k << "aren't lunch break compatible\n";
                        }
                    }

                /* Check daily working minutes */
                if (is_timetable_compatible)
                    if (daily_working_minutes > FULL_TIME_WOKRING_MINUTES_DAY + DAILY_OVERTIME - (missions[j].end_minute - missions[j].start_minute))
                        /* With this mission, the employee would work more than the maximum allowed this day => incompatible */
                        is_timetable_compatible = false;

                if (is_timetable_compatible)
                {
                    /* Gene affectation */
                    this->genes[j] = Gene(missions[j], employees[k]);
                    affectation_founded = true;

                    /* Affectation */
                    Time_window tm;
                    tm.start = missions[j].start_minute;
                    tm.end = missions[j].end_minute;
                    tm.mission_id = missions[j].id;
                    employee_timetable_day_j.push_back(tm);

                    if (daily_working_minutes > 0) /* If this isn't the first mission this day, we sort the list */
                        std::sort(employee_timetable_day_j.begin(), employee_timetable_day_j.end(), time_window_compare);

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
    }

    if(affectation_failed > 0)
        std::cout << "\nAffectation failed: " << affectation_failed << std::endl;
}

bool Chromosome::is_valid()
{
    int daily_working_minutes, lunch_break_working_time, start_lunch_break, end_lunch_break;
    int weekly_working_minutes[n_employee] = {0};
    float distance;

    /*  Employee and mission must have the same skill */
    for(int i = 0 ; i < n_mission ; ++i)
        if(this->genes[i].employee.skill != this->genes[i].mission.skill)
            return false;

    for (int k = 0 ; k < n_employee ; ++k)
    {
        for(int j = 0 ; j < N_WEEK_DAY ; ++j)
        {
            daily_working_minutes = 0;
            lunch_break_working_time = 0;
            auto &employee_timetable_day_j = employee_timetables[k*N_WEEK_DAY + j];
            for(auto tw = employee_timetable_day_j.begin(); tw != employee_timetable_day_j.end(); ++tw)
            {
                /* Count daily working minutes */
                daily_working_minutes += ((*tw).end - (*tw).start);
                
                /* Store lunch break working time (to check later that the employee has a least 1 hour lunch break) */
                if (((*tw).start >= LUNCH_BREAK_START && (*tw).start <= LUNCH_BREAK_END) ||
                    ((*tw).end >= LUNCH_BREAK_START && (*tw).end <= LUNCH_BREAK_END) ||
                    ((*tw).start <= LUNCH_BREAK_START && (*tw).end >= LUNCH_BREAK_END))
                {
                    if ((*tw).start > LUNCH_BREAK_START)
                        start_lunch_break = (*tw).start;
                    else
                        start_lunch_break = LUNCH_BREAK_START;

                    if ((*tw).end < LUNCH_BREAK_END)
                        end_lunch_break = (*tw).end;
                    else
                        end_lunch_break = LUNCH_BREAK_END; 
                    lunch_break_working_time += end_lunch_break - start_lunch_break;
                }

                /* Mission schedule must respect the time window */
                if((*tw).end > END_HOUR*60 || (*tw).start < START_HOUR*60)
                    return false;

                if(tw != employee_timetable_day_j.end() && tw != (employee_timetable_day_j.end() - 1))
                {
                    /* Employee must have a mission once a time and enough travel time btw each */                        
                    distance = distances[((*tw).mission_id + 1) * n_location + (*(tw+1)).mission_id + 1];

                    if ((*tw).end + distance / TRAVEL_SPEED > (*(tw+1)).start){
                        printf("\n");
                        //std::cout << "dist (" << (*tw).mission_id  << "," <<(*(tw+1)).mission_id << ") = " << distance << std::endl; 
                        //std::cout << "end : " << (*tw).end << " + " << distance << " / " << TRAVEL_SPEED << " = "<< (*tw).end + distance / TRAVEL_SPEED << ", start : " <<  (*(tw+1)).start << std::endl;
                        return false;
                    }
                }
            }

            /* Employe must have at least 1 hour lunch break */
            if ((LUNCH_BREAK_END - LUNCH_BREAK_START) - lunch_break_working_time < LUNCH_BREAK_TIME)
                return false;

            /* Employee schedule must respect daily working time and overtime */
            if(daily_working_minutes > FULL_TIME_WOKRING_MINUTES_DAY + DAILY_OVERTIME)
                return false;

            weekly_working_minutes[k] += daily_working_minutes;
        }
        /* Employee schedule must respect daily working time and overtime */
        if (weekly_working_minutes[k] > FULL_TIME_WOKRING_MINUTES_WEEK + WEEKLY_OVERTIME)
            return false;
    }


    return true;
}

float Chromosome::evaluate_employees()
{
    float delta_time, temp_distance;
    float stdev_wasted_hours = 0, stdev_overtime = 0, stdev_distances = 0; // standard derivations
    float sum_wasted_hours = 0, sum_overtime = 0, sum_distances = 0;       // sums
    float sum2_wasted_hours = 0, sum2_overtime = 0, sum2_distances = 0;    // quadratics sums
    float partial_sum_wasted_hours, partial_sum_distances;
    int partial_sum_employee_worktime; // we are computing standart derivation by employee by week so we need to store an intermadiate value of the sum and then compute the square in the employee for loop sums

    // compute in one pass the sum and the quadratic sum of wasted hours, overtime and distances
    // remark : the divisons by 1000 and by 60 are for conversion from metter or minute to km or hour
    for (int i = 0; i < n_employee; ++i)
    {
        partial_sum_employee_worktime = 0;
        partial_sum_wasted_hours = 0;
        partial_sum_distances = 0;
        for (int j = 0; j < N_WEEK_DAY; ++j)
        {

            auto const &vec = employee_timetables[i * N_WEEK_DAY + j]; // reference on current vector for more readability
            int k;
            partial_sum_distances += distances[(0 * n_location + vec[0].mission_id + 1)]; // distance from sessad to i first mission
            for (k = 0; k < int(vec.size()) - 1; ++k)
            {
                temp_distance = this->distances[(vec[k].mission_id + 1) * n_location + vec[k + 1].mission_id + 1]; // distance form i to i+1
                temp_distance = temp_distance / 1000;
                partial_sum_distances += temp_distance;
                

                delta_time = vec[k + 1].start - temp_distance / TRAVEL_SPEED - vec[k].start; // start time of i+1 - travel time from i-->i+1 - end time of i
                partial_sum_wasted_hours += delta_time / 60;// conversion from minute to hour

                partial_sum_employee_worktime += vec[k].end - vec[k].start;
            }
            if (vec.size() > 0){
                partial_sum_employee_worktime += vec[k].end - vec[k].start; // to get the hours of vec[vec.size()-1]
                partial_sum_distances += distances[(0 * n_location + vec[0].mission_id + 1)]; // distance from sessad to first mission
                partial_sum_distances += distances[(vec[k].mission_id + 1) * n_location + 0]; // distance from last mission to sessad
            }

        }

        if (partial_sum_employee_worktime - employees[i].quota > 0)
        {
            sum_overtime += (partial_sum_employee_worktime - employees[i].quota) / 60;
            sum2_overtime += pow((partial_sum_employee_worktime - employees[i].quota) / 60, 2);
        }
        sum2_wasted_hours += pow(partial_sum_wasted_hours, 2);
        sum_wasted_hours += partial_sum_wasted_hours;

        sum2_distances += pow(partial_sum_distances, 2);
        sum_distances += partial_sum_distances;
    }

    // compute the standart derivation = sqrt(E(X²)-E(X)²), X the wasted hours, overtime and distances
    stdev_wasted_hours = sqrt(sum2_wasted_hours / n_employee - pow(sum_wasted_hours / n_employee, 2));
    stdev_overtime = sqrt(sum2_overtime / n_employee - pow(sum_overtime / n_employee, 2));
    stdev_distances = sqrt(sum2_distances / n_employee - pow(sum_distances / n_employee, 2));

    this->fitness = (zeta * stdev_wasted_hours + gamma * stdev_overtime + kappa * stdev_distances) / 3;
    return this->fitness;
}


float Chromosome::evaluate_clients()
{
    int n_penalty = 0;
    for(int i =0; i< n_employee;  ++i){
        for(int j=0; j< N_WEEK_DAY; ++j){

            for(auto const &tw : employee_timetables[i*N_WEEK_DAY + j]){
                if(missions[tw.mission_id].specialty != employees[i].specialty) ++n_penalty;
            }
        }
    }
    return n_penalty*alpha;
}

float Chromosome::evaluate_sessad()
{
    float sum_distances = 0, max_distance=0, sum_overtime = 0, sum_wasted_hours = 0;
    float delta_time, temp_distance=0;//temporary variables
    int employee_worktime;//temporary variable

    for(int i=0; i<n_employee; ++i){
        employee_worktime=0;
        for(int j=0; j<N_WEEK_DAY; ++j){

            auto const &vec = employee_timetables[i*N_WEEK_DAY + j];
            int k;
            for(k=0; k<int(vec.size()) -1; ++k)
            {
                temp_distance = this->distances[(vec[k].mission_id + 1) * n_location + vec[k + 1].mission_id + 1]; // distance form i to i+1
                sum_distances += temp_distance / 1000;
                if(temp_distance > max_distance) max_distance = temp_distance;

                delta_time = vec[k + 1].start - temp_distance / TRAVEL_SPEED - vec[k].start; // start time of i+1 - travel time from i-->i+1 - end time of i
                sum_wasted_hours += delta_time / 60;//conversion from minutes to hours

                employee_worktime += vec[k].end - vec[k].start;
            }
            if (vec.size() > 0)
                employee_worktime += vec[k].end - vec[k].start; // to get the hours of vec[vec.size()-1]
        }
        if (employee_worktime - employees[i].quota > 0){
            sum_overtime += (employee_worktime - employees[i].quota) / 60;
        }
    }
    
    return (beta*(sum_overtime+sum_wasted_hours) + kappa*(sum_distances/n_mission) + kappa*max_distance)/3;

}


std::ostream &operator<<(std::ostream &output, Chromosome &c)
{
    // for (int i = 0; i < n_mission; ++i)
        // output << c.genes[i];

    for (int i = 0; i < n_employee; ++i)
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
        std::cout << "\n"
                  << j << "   ";
        i = START_HOUR * 60;
        for (Time_window mission_time_window : this->employee_timetables[employee * N_WEEK_DAY + j])
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
    //std::cout << "Free chromosome" << std::endl;
    delete[] this->employee_timetables;
}

bool employees_fitness_comparator(Chromosome &a, Chromosome &b)
{
    return a.evaluate_employees() < b.evaluate_employees();
};

bool clients_fitness_comparator(Chromosome &a, Chromosome &b)
{
    return a.evaluate_clients() < b.evaluate_clients();
};

bool sessad_fitness_comparator(Chromosome &a, Chromosome &b)
{
    return a.evaluate_sessad() < b.evaluate_sessad();
};