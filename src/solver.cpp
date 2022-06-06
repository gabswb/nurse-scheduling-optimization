#include "solver.hpp"

void genetic_algorithm(const Mission missions[], const Employee employees[], const float distances[], std::chrono::steady_clock::time_point begin_exec)
{
    int n_iteration = 0;
    std::vector<Chromosome> population;

    initialize_population();

    while(n_iteration++ < max_iteration_number && std::chrono::steady_clock::now() - begin_exec < std::chrono::seconds(max_execution_time))
    {
        //if(verbose) ...

        crossover();

        mutate();
    }



    
    if(n_iteration > max_iteration_number){
        std::cout << "Max iteration number reached" << std::endl;
        return;
    }
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin_exec).count() > max_execution_time){
        std::cout << "Max execution time reached" << std::endl;
        return;
    }
}
