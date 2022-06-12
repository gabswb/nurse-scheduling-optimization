#include "solver.hpp"

void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::default_random_engine& generator, std::chrono::steady_clock::time_point begin_exec)
{
    bool modified = false;
    int n_iteration = 0;
    float fitness_average = 0;
    Chromosome *population = new Chromosome[population_size];
    std::uniform_real_distribution<float> uniform_dist(0, 1);

    initialize_population(population, missions, employees, distances);
    //display_population(population);
    display_fitness(population, fitness_average);

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
            printf("modified\n");
        }
        display_fitness(population, fitness_average);

    }




    if (n_iteration > max_iteration_number)
    {
        std::cout << "Max iteration number reached" << std::endl;
        delete[] population;
        return;
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin_exec).count() > max_execution_time)
    {
        std::cout << "Max execution time reached" << std::endl;
        delete[] population;
        return;
    }
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
        fitness_sum += 1/population[i].evaluate();
        //std::cout << "fitness = " << 1/population[i].evaluate() << std::endl;
    }
    for(int i = 0; i < population_size; ++i){
        proba_array[i] = proba_sum + (1/population[i].fitness) / fitness_sum;
        proba_sum += (1/population[i].fitness) / fitness_sum;
        //std::cout << "proba = " << (1/population[i].fitness) / fitness_sum << std::endl;
        //std::cout << "proba_array" << i << " = " << proba_array[i] << std::endl;
    }
    //std::cout << "proba_sum = " << proba_sum << std::endl;

    size_t index = 0;
    float random = uniform_dist(generator);
    //std::cout << "random = " << random << std::endl;
    while(proba_array[index] < random) index++;

    //std::cout << "index selection = " << index << std::endl;
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
        fitness_sum += population[i].evaluate();
       // std::cout << "fitness = " << 1/population[i].evaluate() << std::endl;
    }
    for(int i = 0; i < population_size; ++i){
        proba_array[i] = proba_sum + population[i].fitness / fitness_sum;
        proba_sum += population[i].fitness / fitness_sum;
        //std::cout << "proba = " << (1/population[i].fitness) / fitness_sum << std::endl;
       // std::cout << "proba_array" << i << " = " << proba_array[i] << std::endl;
    }
    //std::cout << "proba_sum = " << proba_sum << std::endl;

    size_t index = 0;
    float random = uniform_dist(generator);
    //std::cout << "random = " << random << std::endl;
    while(proba_array[index] < random) index++;

    //std::cout << "index replacement = " << index << std::endl;
    population[index] = child;
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
        average_population_fitness += population[i].evaluate();
        std::cout << "Fitness " << i << ": " << population[i].evaluate() << "  validation: " << population[i].is_valid() << std::endl;
    }
    average_population_fitness /= population_size;
    std::cout << "Average population evaluation: " << average_population_fitness << std::endl;
}