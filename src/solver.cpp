#include "solver.hpp"

void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::chrono::steady_clock::time_point begin_exec)
{
    int n_iteration = 0;
    Chromosome *population = new Chromosome[population_size];
    float average_population_fitness = 0;

    initialize_population(population, missions, employees, distances);
    display_population(population);
    display_fitness(population, average_population_fitness);

    // while (n_iteration++ < max_iteration_number && std::chrono::steady_clock::now() - begin_exec < std::chrono::seconds(max_execution_time))
    // {
    //     // if(verbose) ...

    //     // crossover();

    //     // mutate();
    // }

    if (n_iteration > max_iteration_number)
    {
        std::cout << "Max iteration number reached" << std::endl;
        return;
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin_exec).count() > max_execution_time)
    {
        std::cout << "Max execution time reached" << std::endl;
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