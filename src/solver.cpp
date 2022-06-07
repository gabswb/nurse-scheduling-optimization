#include "solver.hpp"

void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::chrono::steady_clock::time_point begin_exec)
{
    int n_iteration = 0;
    Chromosome *population = new Chromosome[population_size];

    initialize_population(population, missions, employees, distances);
    display(population);

    // while (n_iteration++ < max_iteration_number && std::chrono::steady_clock::now() - begin_exec < std::chrono::seconds(max_execution_time))
    // {
    //     // if(verbose) ...

    //     // crossover();

    //     // mutate();
    // }

    if (n_iteration > max_iteration_number)
    {
<<<<<<< HEAD
        
    }



    
    if(n_iteration > max_iteration_number){
=======
>>>>>>> f50b456c729e5f8f824ebb9e485f0de541a44791
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
        population[i] = Chromosome(missions, employees, distances_p);
    }
}

void display(Chromosome *population)
{
    for (int i = 0; i < population_size; ++i)
    {
        std::cout << "\n\n\n******************************************Chromosome " << i << "******************************************" << std::endl;
        std::cout << population[i];
    }
    for (int i = 0; i < population_size; ++i)
        std::cout << "Evaluation  chromosome " << i << ": " << population[i].evaluate() << std::endl;
}