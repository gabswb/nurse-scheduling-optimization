#include "solver.hpp"

Chromosome genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::default_random_engine &generator, std::chrono::steady_clock::time_point begin_exec)
{
    bool modified = false;
    int n_iteration = 0;
    float fitness_average = 0;
    Chromosome *population = new Chromosome[population_size];
    std::uniform_real_distribution<float> uniform_dist(0, 1);

    initialize_population(population, missions, employees, distances, generator);
    // display_population(population);
    display_fitness(population, fitness_average);

    // for(int i=0; i<population_size; i++)
    //     mutate_test(&population[0],employees, generator);

    // mutate(&population[0], employees, generator);

    while (n_iteration++ < max_iteration_number && std::chrono::steady_clock::now() - begin_exec < std::chrono::seconds(max_execution_time))
    {
        Chromosome child1(missions, employees, distances), child2(missions, employees, distances);
        Chromosome *parent1, *parent2;

        parent1 = roulette_selection(population, generator);
        parent2 = roulette_selection(population, generator);

        if (uniform_dist(generator) < crossover_rate)
        {
            crossover_1X(parent1, parent2, &child1, &child2);
            modified = true;
        }
        else
        {
            child1 = *parent1;
            child2 = *parent2;
        }

        if (uniform_dist(generator) < mutation_rate)
        {
            mutate(&child1, generator);
            // mutate_gab(&child1, employees, generator);
            modified = true;
        }
        if (uniform_dist(generator) < mutation_rate)
        {
            mutate(&child2, generator);
            // mutate_gab(&child2, employees, generator);
            modified = true;
        }

        if (modified)
        {
            replacement_roulette_selection(population, child1, generator);
            replacement_roulette_selection(population, child2, generator);
        }
        display_fitness(population, fitness_average);
    }

    std::sort(population, population + population_size, employees_fitness_comparator);

    size_t new_pop_size = population_size * 0.2;
    Chromosome filtred_population[new_pop_size]; // 20% of the best chromosomes
    for (size_t i = 0; i < new_pop_size; ++i)
    {
        filtred_population[i] = population[i];
    }
    std::sort(filtred_population, filtred_population + new_pop_size, clients_fitness_comparator);
    std::sort(filtred_population, filtred_population + new_pop_size, sessad_fitness_comparator);
    Chromosome result = filtred_population[0];

    if (n_iteration > max_iteration_number)
        std::cout << "Max iteration number reached" << std::endl;
    else
        std::cout << "Max execution time reached" << std::endl;

    delete[] population;
    return result;
    return population[0];
}

void initialize_population(Chromosome *population, const Mission missions_p[], const Employee employees_p[], const float distances_p[], std::default_random_engine& generator)
{
    population[0] = Chromosome(missions_p, employees_p, distances_p);
    population[0].initialize();

    for (int i = 1; i < population_size; ++i)
    {
        Mission missions[n_mission];
        Employee employees[n_employee];
        std::copy(missions_p, missions_p + n_mission, missions);
        std::copy(employees_p, employees_p + n_employee, employees);
        std::shuffle(missions, missions + n_mission, generator);
        std::shuffle(employees, employees + n_employee, generator);
        Chromosome chr = Chromosome(missions, employees, distances_p);
        population[i] = chr;
        population[i].initialize();
    }
}

Chromosome *roulette_selection(Chromosome population[], std::default_random_engine &generator)
{
    float proba_sum = 0;
    float fitness_sum = 0;
    float proba_array[population_size] = {0};
    std::uniform_real_distribution<float> uniform_dist(0, 1);

    for (int i = 0; i < population_size; ++i)
    {
        fitness_sum += 1 / population[i].evaluate_employees();
    }
    for (int i = 0; i < population_size; ++i)
    {
        proba_array[i] = proba_sum + (1 / population[i].fitness) / fitness_sum;
        proba_sum += (1 / population[i].fitness) / fitness_sum;
    }

    size_t index = 0;
    float random = uniform_dist(generator);
    while (proba_array[index] < random)
        index++;

    return &population[index];
}

void crossover_1X(Chromosome *parent1, Chromosome *parent2, Chromosome *child1, Chromosome *child2)
{
    for (int i = 0; i < n_employee; ++i)
    {
        child1->employee_timetables[i * N_WEEK_DAY + MONDAY] = parent1->employee_timetables[i * N_WEEK_DAY + MONDAY];
        child1->employee_timetables[i * N_WEEK_DAY + TUESDAY] = parent1->employee_timetables[i * N_WEEK_DAY + TUESDAY];
        child1->employee_timetables[i * N_WEEK_DAY + WEDNESDAY] = parent1->employee_timetables[i * N_WEEK_DAY + WEDNESDAY];
        child1->employee_timetables[i * N_WEEK_DAY + THURSDAY] = parent2->employee_timetables[i * N_WEEK_DAY + THURSDAY];
        child1->employee_timetables[i * N_WEEK_DAY + FRIDAY] = parent2->employee_timetables[i * N_WEEK_DAY + FRIDAY];

        child2->employee_timetables[i * N_WEEK_DAY + MONDAY] = parent2->employee_timetables[i * N_WEEK_DAY + MONDAY];
        child2->employee_timetables[i * N_WEEK_DAY + TUESDAY] = parent2->employee_timetables[i * N_WEEK_DAY + TUESDAY];
        child2->employee_timetables[i * N_WEEK_DAY + WEDNESDAY] = parent2->employee_timetables[i * N_WEEK_DAY + WEDNESDAY];
        child2->employee_timetables[i * N_WEEK_DAY + THURSDAY] = parent1->employee_timetables[i * N_WEEK_DAY + THURSDAY];
        child2->employee_timetables[i * N_WEEK_DAY + FRIDAY] = parent1->employee_timetables[i * N_WEEK_DAY + FRIDAY];
    }
}

void crossover_NX(Chromosome *parent1, Chromosome *parent2, Chromosome *child1, Chromosome *child2)
{
    for (int i = 0; i < n_employee; ++i)
    {
        child1->employee_timetables[i * N_WEEK_DAY + MONDAY] = parent1->employee_timetables[i * N_WEEK_DAY + MONDAY];
        child1->employee_timetables[i * N_WEEK_DAY + TUESDAY] = parent2->employee_timetables[i * N_WEEK_DAY + TUESDAY];
        child1->employee_timetables[i * N_WEEK_DAY + WEDNESDAY] = parent1->employee_timetables[i * N_WEEK_DAY + WEDNESDAY];
        child1->employee_timetables[i * N_WEEK_DAY + THURSDAY] = parent2->employee_timetables[i * N_WEEK_DAY + THURSDAY];
        child1->employee_timetables[i * N_WEEK_DAY + FRIDAY] = parent1->employee_timetables[i * N_WEEK_DAY + FRIDAY];

        child2->employee_timetables[i * N_WEEK_DAY + MONDAY] = parent2->employee_timetables[i * N_WEEK_DAY + MONDAY];
        child2->employee_timetables[i * N_WEEK_DAY + TUESDAY] = parent1->employee_timetables[i * N_WEEK_DAY + TUESDAY];
        child2->employee_timetables[i * N_WEEK_DAY + WEDNESDAY] = parent2->employee_timetables[i * N_WEEK_DAY + WEDNESDAY];
        child2->employee_timetables[i * N_WEEK_DAY + THURSDAY] = parent1->employee_timetables[i * N_WEEK_DAY + THURSDAY];
        child2->employee_timetables[i * N_WEEK_DAY + FRIDAY] = parent2->employee_timetables[i * N_WEEK_DAY + FRIDAY];
    }
}

void replacement_roulette_selection(Chromosome *population, Chromosome child, std::default_random_engine &generator)
{
    float proba_sum = 0;
    float fitness_sum = 0;
    float proba_array[population_size] = {0};
    std::uniform_real_distribution<float> uniform_dist(0, 1);

    for (int i = 0; i < population_size; ++i)
    {
        fitness_sum += population[i].evaluate_employees();
    }
    for (int i = 0; i < population_size; ++i)
    {
        proba_array[i] = proba_sum + population[i].fitness / fitness_sum;
        proba_sum += population[i].fitness / fitness_sum;
    }

    size_t index = 0;
    float random = uniform_dist(generator);
    while (proba_array[index] < random)
        index++;

    population[index] = child;
}

void mutate_gab(Chromosome *chromosome, const Employee employees[], std::default_random_engine &generator)
{
    int day;
    int hour;
    int n_attempts = 0;
    int employee_index2;
    int employee_index1;
    std::uniform_int_distribution<int> uniform_dist_emp(0, n_employee - 1);
    std::uniform_int_distribution<int> uniform_dist_day(0, N_WEEK_DAY - 1);
    std::uniform_int_distribution<int> uniform_dist_hour(START_HOUR, END_HOUR - 4);

    do
    {
        day = uniform_dist_day(generator);
        hour = uniform_dist_hour(generator);
        employee_index2 = uniform_dist_emp(generator);
        employee_index1 = uniform_dist_emp(generator);
        while (employees[employee_index1].skill == employees[employee_index2].skill)
            employee_index2 = uniform_dist_emp(generator);

        auto emp1_ttb_day = chromosome->employee_timetables[employee_index1 * N_WEEK_DAY + day];
        auto emp2_ttb_day = chromosome->employee_timetables[employee_index2 * N_WEEK_DAY + day];

        std::vector<Gene> temp_ttb_1 = emp1_ttb_day;
        std::vector<Gene> temp_ttb_2 = emp2_ttb_day;

        int index_1 = 0;
        int index_2 = 0;

        while (index_1 < (int(temp_ttb_1.size()) - 1) && temp_ttb_1[index_1].start / 60 < hour)
            ++index_1;
        while (index_2 < (int(temp_ttb_2.size()) - 1) && temp_ttb_2[index_2].start / 60 < hour)
            ++index_2;

        emp1_ttb_day.erase(emp1_ttb_day.begin() + index_1, emp1_ttb_day.end());
        emp2_ttb_day.erase(emp2_ttb_day.begin() + index_2, emp2_ttb_day.end());

        for(size_t i=index_2; i < temp_ttb_2.size(); ++i)
            emp1_ttb_day.push_back(temp_ttb_2[i]);

        for(size_t i=index_1; i < temp_ttb_1.size(); ++i)
            emp2_ttb_day.push_back(temp_ttb_1[i]);


        if(chromosome->is_valid()){
            chromosome->employee_timetables[employee_index1*N_WEEK_DAY + day] = emp1_ttb_day;
            chromosome->employee_timetables[employee_index2*N_WEEK_DAY + day] = emp2_ttb_day;
            //std::cout << "Mutation successful\n" << std::endl;
        } 
        //else std::cout << "Mutation unsuccessful\n" << std::endl;
        ++n_attempts;
    } while (!chromosome->is_valid() && n_attempts < MAX_MUTATION_ATTEMPT);
}

void mutate(Chromosome *chromosome, std::default_random_engine &generator)
{
    bool mutated = false, error = false;
    int employee1, employee2, day, start_minute, attempt = 0, i, count, mission_count_1, mission_count_2;
    std::uniform_int_distribution<int> random_employee(0, n_employee - 1);
    std::uniform_int_distribution<int> random_day(0, N_WEEK_DAY - 1);
    std::uniform_int_distribution<int> random_start_minute(START_HOUR * 60, (END_HOUR - 4) * 60);

    while (!mutated && attempt < MAX_MUTATION_ATTEMPT)
    {
        /* Generator random day, random start minute and select random employees with same skill */
        day = random_day(generator);
        start_minute = random_start_minute(generator);
        employee1 = random_employee(generator);
        count = 0;

        do
        {
            employee2 = random_employee(generator);
            // std::cout << " " << employee1 << "->" << employee2 << " " << chromosome->employees[employee1].skill << "->" << chromosome->employees[employee2].skill << std::endl;
            if (count > 100)
                error = true;
            ++count;

        } while ((employee1 == employee2 || chromosome->employees[employee1].skill != chromosome->employees[employee2].skill) && !error);

        if (!error)
        {
            /* Verbose */
            // std::cout << "Mutation Exchange day " << day << "form hour" << start_minute/60 <<  "\n";
            // chromosome->print_employee_timetable(employee1);
            // chromosome->print_employee_timetable(employee2);

            std::vector<Gene> employee1_timetable_day_j = chromosome->employee_timetables[employee1 * N_WEEK_DAY + day];
            std::vector<Gene> employee2_timetable_day_j = chromosome->employee_timetables[employee2 * N_WEEK_DAY + day];

            /* Swap missions starting after start_minute */
            std::vector<Gene> employee1_missions, employee2_missions;

            for (i = 0; i < employee1_timetable_day_j.size(); ++i)
            {
                if (employee1_timetable_day_j[i].start >= start_minute)
                {
                    employee1_missions.push_back(employee1_timetable_day_j[i]);
                    employee1_timetable_day_j.erase(employee1_timetable_day_j.begin() + i);
                }
            }

            for (i = 0; i < employee2_timetable_day_j.size(); ++i)
            {
                if (employee2_timetable_day_j[i].start >= start_minute)
                {
                    employee2_missions.push_back(employee2_timetable_day_j[i]);
                    employee2_timetable_day_j.erase(employee2_timetable_day_j.begin() + i);
                }
            }

            mission_count_1 = 0;
            mission_count_2 = 0;

            for (auto tw : employee2_missions)
            {
                employee1_timetable_day_j.push_back(tw);
                ++mission_count_1;
            }

            for (auto tw : employee1_missions)
            {
                employee2_timetable_day_j.push_back(tw);
                ++mission_count_2;
            }

            std::sort(employee1_timetable_day_j.begin(), employee1_timetable_day_j.end(), time_window_compare);
            std::sort(employee2_timetable_day_j.begin(), employee2_timetable_day_j.end(), time_window_compare);

            /* Test if solution is valid (store old solution and affect new solution) */
            auto old_employee1_timetable_day_j = chromosome->employee_timetables[employee1 * N_WEEK_DAY + day];
            auto old_employee2_timetable_day_j = chromosome->employee_timetables[employee2 * N_WEEK_DAY + day];
            chromosome->employee_timetables[employee1 * N_WEEK_DAY + day] = employee1_timetable_day_j;
            chromosome->employee_timetables[employee2 * N_WEEK_DAY + day] = employee2_timetable_day_j;

            if (chromosome->is_valid())
            {
                /* We keep the solution and allocate the memory space needed */
                mutated = true;
                chromosome->employee_timetables[employee1 * N_WEEK_DAY + day].reserve(mission_count_1);
                chromosome->employee_timetables[employee2 * N_WEEK_DAY + day].reserve(mission_count_2);
                // std::cout << "debug: valid\n";
            }
            else
            {
                /* If not valid, we restore the old solution */
                chromosome->employee_timetables[employee1 * N_WEEK_DAY + day] = old_employee1_timetable_day_j;
                chromosome->employee_timetables[employee2 * N_WEEK_DAY + day] = old_employee2_timetable_day_j;
                std::cout << "debug: mutation not valid\n";
            }
            /* Verbose */
            // std::cout << "after\n";
            // chromosome.print_employee_timetable(employee1);
            // chromosome.print_employee_timetable(employee2);
        }
        else
            std::cout << "error: attempt:" << attempt << "\n";

        ++attempt;
    }

    if (attempt == MAX_MUTATION_ATTEMPT)
        std::cout << "*********Mutation failed !*********\n";
}

void display_population(Chromosome *population)
{
    for (int i = 0; i < population_size; ++i)
    {
        std::cout << "\n\n\n******************************************Chromosome " << i << "******************************************" << std::endl;
        std::cout << population[i];
    }
}

void display_fitness(Chromosome *population, float &average_population_fitness)
{
    for (int i = 0; i < population_size; ++i)
    {
        average_population_fitness += population[i].evaluate_employees();
        // std::cout << "Fitness " << i << ": " << population[i].evaluate_employees() << "  validation: " << population[i].is_valid() << std::endl;
    }
    average_population_fitness /= population_size;
    std::cout << "Average population evaluation: " << average_population_fitness << std::endl;
}