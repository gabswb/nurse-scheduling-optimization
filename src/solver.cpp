#include "solver.hpp"

Chromosome genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::default_random_engine& generator, std::chrono::steady_clock::time_point begin_exec)
{
    bool modified = false;
    int n_iteration = 0;
    float fitness_average = 0;
    Chromosome *population = new Chromosome[population_size];
    std::uniform_real_distribution<float> uniform_dist(0, 1);

    initialize_population(population, missions, employees, distances);
    //display_population(population);
    display_fitness(population, fitness_average);

    for(int i=0; i<population_size; ++i){
        std::cout << "fitness: " << population[i].evaluate_employees() << std::endl;
        std::cout << "fitness client = " <<population[i].evaluate_clients() << std::endl;
        std::cout << "fitness sessad = " <<population[i].evaluate_sessad() << std::endl;
    }

    //mutate(&population[0], employees, generator);

    while (n_iteration++ < max_iteration_number && std::chrono::steady_clock::now() - begin_exec < std::chrono::seconds(max_execution_time))
    {
        Chromosome child1(missions, employees, distances), child2(missions, employees, distances);
        Chromosome *parent1, *parent2;

        parent1 = roulette_selection(population, generator);
        parent2 = roulette_selection(population, generator);

        if(uniform_dist(generator) < crossover_rate){
            crossover_1X(parent1, parent2, &child1, &child2);
            modified = true;
        }
        else{
            child1 = *parent1;
            child2 = *parent2;
        }

        // if(uniform_dist(generator) < mutation_rate){
        //     mutate(&child1);
        //     modified = true;
        // }
        // if(uniform_dist(generator) < mutation_rate){
        //     mutate(&child2);
        //     modified = true;
        // }

        if(modified){ 
            replacement_roulette_selection(population, child1, generator);
            replacement_roulette_selection(population, child2, generator);  
        }
        //display_fitness(population, fitness_average);
    }

    std::sort(population, population+population_size, employees_fitness_comparator);

    size_t new_pop_size = population_size*0.2;
    Chromosome filtred_population[new_pop_size];//20% of the best chromosomes
    for(size_t i=0; i<new_pop_size; ++i){
        filtred_population[i] = population[i];
    }
    std::sort(filtred_population, filtred_population+new_pop_size, clients_fitness_comparator);
    std::sort(filtred_population, filtred_population+new_pop_size, sessad_fitness_comparator);
    Chromosome result = filtred_population[0];

    if (n_iteration > max_iteration_number) std::cout << "Max iteration number reached" << std::endl;
    else std::cout << "Max execution time reached" << std::endl;

    delete[] population;
    return result;
    return population[0];
}



void initialize_population(Chromosome *population, const Mission missions_p[], const Employee employees_p[], const float distances_p[])
{
    population[0] = Chromosome(missions_p, employees_p, distances_p);

    for (int i = 1; i < population_size; ++i)
    {
        Mission missions[n_mission];
        Employee employees[n_employee];
        std::copy(missions_p, missions_p + n_mission, missions);
        std::copy(employees_p, employees_p + n_employee, employees);
        std::shuffle(missions, missions + n_mission, std::default_random_engine(i));
        std::shuffle(employees, employees + n_employee, std::default_random_engine(i));
        Chromosome chr = Chromosome(missions, employees, distances_p);
        population[i] = chr;
    }
}

Chromosome* roulette_selection(Chromosome population[], std::default_random_engine& generator)
{
    float proba_sum = 0;
    float fitness_sum = 0;
    float proba_array[population_size] = {0};
    std::uniform_real_distribution<float> uniform_dist(0, 1);

    for(int i = 0; i < population_size; ++i){
        fitness_sum += 1/population[i].evaluate_employees();
    }
    for(int i = 0; i < population_size; ++i){
        proba_array[i] = proba_sum + (1/population[i].fitness) / fitness_sum;
        proba_sum += (1/population[i].fitness) / fitness_sum;
    }

    size_t index = 0;
    float random = uniform_dist(generator);
    while(proba_array[index] < random) index++;

    return &population[index];
}


void crossover_1X(Chromosome* parent1, Chromosome* parent2, Chromosome* child1, Chromosome* child2)
{
    for(int i=0; i < n_employee; ++i){
        child1->employee_timetables[i*N_WEEK_DAY + MONDAY]    = parent1->employee_timetables[i*N_WEEK_DAY + MONDAY];
        child1->employee_timetables[i*N_WEEK_DAY + TUESDAY]   = parent1->employee_timetables[i*N_WEEK_DAY + TUESDAY];
        child1->employee_timetables[i*N_WEEK_DAY + WEDNESDAY] = parent1->employee_timetables[i*N_WEEK_DAY + WEDNESDAY];
        child1->employee_timetables[i*N_WEEK_DAY + THURSDAY]  = parent2->employee_timetables[i*N_WEEK_DAY + THURSDAY];
        child1->employee_timetables[i*N_WEEK_DAY + FRIDAY]    = parent2->employee_timetables[i*N_WEEK_DAY + FRIDAY];

        child2->employee_timetables[i*N_WEEK_DAY + MONDAY]    = parent2->employee_timetables[i*N_WEEK_DAY + MONDAY];
        child2->employee_timetables[i*N_WEEK_DAY + TUESDAY]   = parent2->employee_timetables[i*N_WEEK_DAY + TUESDAY];
        child2->employee_timetables[i*N_WEEK_DAY + WEDNESDAY] = parent2->employee_timetables[i*N_WEEK_DAY + WEDNESDAY];
        child2->employee_timetables[i*N_WEEK_DAY + THURSDAY]  = parent1->employee_timetables[i*N_WEEK_DAY + THURSDAY];
        child2->employee_timetables[i*N_WEEK_DAY + FRIDAY]    = parent1->employee_timetables[i*N_WEEK_DAY + FRIDAY];        
    }
}

void crossover_NX(Chromosome* parent1, Chromosome* parent2, Chromosome* child1, Chromosome* child2)
{
    for(int i=0; i < n_employee; ++i){
        child1->employee_timetables[i*N_WEEK_DAY + MONDAY]    = parent1->employee_timetables[i*N_WEEK_DAY + MONDAY];
        child1->employee_timetables[i*N_WEEK_DAY + TUESDAY]   = parent2->employee_timetables[i*N_WEEK_DAY + TUESDAY];
        child1->employee_timetables[i*N_WEEK_DAY + WEDNESDAY] = parent1->employee_timetables[i*N_WEEK_DAY + WEDNESDAY];
        child1->employee_timetables[i*N_WEEK_DAY + THURSDAY]  = parent2->employee_timetables[i*N_WEEK_DAY + THURSDAY];
        child1->employee_timetables[i*N_WEEK_DAY + FRIDAY]    = parent1->employee_timetables[i*N_WEEK_DAY + FRIDAY];

        child2->employee_timetables[i*N_WEEK_DAY + MONDAY]    = parent2->employee_timetables[i*N_WEEK_DAY + MONDAY];
        child2->employee_timetables[i*N_WEEK_DAY + TUESDAY]   = parent1->employee_timetables[i*N_WEEK_DAY + TUESDAY];
        child2->employee_timetables[i*N_WEEK_DAY + WEDNESDAY] = parent2->employee_timetables[i*N_WEEK_DAY + WEDNESDAY];
        child2->employee_timetables[i*N_WEEK_DAY + THURSDAY]  = parent1->employee_timetables[i*N_WEEK_DAY + THURSDAY];
        child2->employee_timetables[i*N_WEEK_DAY + FRIDAY]    = parent2->employee_timetables[i*N_WEEK_DAY + FRIDAY];        
    }
}

void replacement_roulette_selection(Chromosome* population, Chromosome child, std::default_random_engine& generator)
{
    float proba_sum = 0;
    float fitness_sum = 0;
    float proba_array[population_size] = {0};
    std::uniform_real_distribution<float> uniform_dist(0, 1);

    for(int i = 0; i < population_size; ++i){
        fitness_sum += population[i].evaluate_employees();
    }
    for(int i = 0; i < population_size; ++i){
        proba_array[i] = proba_sum + population[i].fitness / fitness_sum;
        proba_sum += population[i].fitness / fitness_sum;
    }

    size_t index = 0;
    float random = uniform_dist(generator);
    while(proba_array[index] < random) index++;

    population[index] = child;
}


void mutate_test(Chromosome* chromosome, const Employee employees[], std::default_random_engine& generator)
{
    int day;
    int hour;
    int employee_index2; 
    int employee_index1;
    std::uniform_int_distribution<int> uniform_dist_emp(0, n_employee-1);
    std::uniform_int_distribution<int> uniform_dist_day(0, N_WEEK_DAY-1);
    std::uniform_int_distribution<int> uniform_dist_hour(START_HOUR, END_HOUR-4);

    do{    
        day = uniform_dist_day(generator);
        hour = uniform_dist_hour(generator);
        employee_index2 = uniform_dist_emp(generator);
        employee_index1 = uniform_dist_emp(generator);
        while(employees[employee_index1].skill == employees[employee_index2].skill) employee_index2 = uniform_dist_emp(generator);

        std::vector<Time_window> temp_ttb_1 = chromosome->employee_timetables[employee_index1*N_WEEK_DAY + day];
        std::vector<Time_window> temp_ttb_2 = chromosome->employee_timetables[employee_index2*N_WEEK_DAY + day];

        std::cout << "Info\n" << "emp : "<< employee_index1 << ","<< employee_index2 << ", day : "<< day << ", hour : "<< hour << "\n" << std::endl;

        chromosome->print_employee_timetable(employee_index1);
        chromosome->print_employee_timetable(employee_index2);    

        int index_1 = 0;
        int index_2 = 0;

        while(index_1 < temp_ttb_1.size() && temp_ttb_1[index_1].start/60 < hour) {
            std::cout << "size " << temp_ttb_1.size() << ", start " << temp_ttb_1[index_1].start/60 << std::endl;
            ++index_1;
        }
        while(index_2 < temp_ttb_2.size() && temp_ttb_2[index_2].start/60 < hour){
            std::cout << "size " << temp_ttb_2.size() << ", start " << temp_ttb_2[index_2].start/60 << std::endl;
            ++index_2;
        } 

        std::cout << "index_1 : "<< index_1 << ", index_2 : "<< index_2 << "\n" << std::endl;

        chromosome->employee_timetables[employee_index1*N_WEEK_DAY + day].erase(chromosome->employee_timetables[employee_index1*N_WEEK_DAY + day].begin() + index_1, chromosome->employee_timetables[employee_index1*N_WEEK_DAY + day].end());
        chromosome->employee_timetables[employee_index2*N_WEEK_DAY + day].erase(chromosome->employee_timetables[employee_index2*N_WEEK_DAY + day].begin() + index_2, chromosome->employee_timetables[employee_index2*N_WEEK_DAY + day].end());

        std::cout << "erase"<< std::endl;

        chromosome->print_employee_timetable(employee_index1);
        chromosome->print_employee_timetable(employee_index2);

        for(int i=index_2; i < temp_ttb_1.size(); ++i){
            chromosome->employee_timetables[employee_index1*N_WEEK_DAY + day].push_back(temp_ttb_2[i]);
        }
        for(int i=index_1; i < temp_ttb_2.size(); ++i){
            chromosome->employee_timetables[employee_index2*N_WEEK_DAY + day].push_back(temp_ttb_1[i]);
        }

        //std::cout 

        chromosome->print_employee_timetable(employee_index1);
        chromosome->print_employee_timetable(employee_index2);

        std::cout << "is valid" << std::endl;
        
        std::cout << "size 1 " << chromosome->employee_timetables[employee_index1*N_WEEK_DAY + day].size() << std::endl;
        std::cout << "size 2 " << chromosome->employee_timetables[employee_index2*N_WEEK_DAY + day].size() << std::endl;

        if(chromosome->is_valid()) std::cout << "Mutation successful\n" << std::endl;
        else std::cout << "Mutation unsuccessful\n" << std::endl;
    }
    while(!chromosome->is_valid());    
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
    for(int i = 0 ; i < population_size; ++i)
    {
        average_population_fitness += population[i].evaluate_employees();
        std::cout << "Fitness " << i << ": " << population[i].evaluate_employees() << "  validation: " << population[i].is_valid() << std::endl;
    }
    average_population_fitness /= population_size;
    std::cout << "Average population evaluation: " << average_population_fitness << std::endl;
}