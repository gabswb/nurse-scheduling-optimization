#include "utils.hpp"

int extract_rows_nb_csv(std::string path_p)
{
    int rows = 0;
    std::ifstream file(path_p);
    std::string line;

    while (getline(file, line))
        rows++;

    return rows;
}

Mission *extract_mission_csv(int size_p, std::string path_p)
{
    Mission *missions = new Mission[size_p];
    std::ifstream file(path_p);
    std::string s_id, s_day, s_starting_period, s_ending_period, s_specialty, s_skill;
    Specialties specialty;
    Skills skill;

    for (int i = 0; i < size_p; i++)
    {
        getline(file, s_id, ',');
        getline(file, s_day, ',');
        getline(file, s_starting_period, ',');
        getline(file, s_ending_period, ',');
        getline(file, s_skill, ',');
        getline(file, s_specialty, '\n');

        if (s_skill == "LPC")
            skill = LPC;
        else if (s_skill == "LSF")
            skill = LSF;
        else
            printf("****Parsing error (mission skill) ****\n");

        if (s_specialty.compare("Musique") == 1)
            specialty = MUSIC;
        else if (s_specialty.compare("Jardinage") == 1)
            specialty = GARDENING;
        else if (s_specialty.compare("Electricite") == 1)
            specialty = ELECTRICITY;
        else if (s_specialty.compare("Menuiserie") == 1)
            specialty = CARPENTRY;
        else if (s_specialty.compare("Mecanique") == 1)
            specialty = MECANIC;
        else
            printf("****Parsing error (mission specialty)****\n");

        missions[i] = Mission(std::stoi(s_id) - 1, std::stoi(s_day) - 1, std::stoi(s_starting_period), std::stoi(s_ending_period), specialty, skill);
    }

    return missions;
}

Employee *extract_employee_csv(int size_p, std::string path_p)
{
    Employee *employees = new Employee[size_p];
    std::ifstream file(path_p);
    std::string s_id, s_quota, s_skill, s_specialty, garbage;
    Specialties specialty;
    Skills skill;

    for (int i = 0; i < size_p; i++)
    {
        getline(file, s_id, ',');
        getline(file, s_skill, ',');
        getline(file, s_specialty, ',');
        getline(file, s_quota, '\n');

        if (s_skill == "LPC")
            skill = LPC;
        else if (s_skill == "LSF")
            skill = LSF;
        else
            printf("****Parsing error (employee skill) ****\n");

        if (s_specialty == "Musique")
            specialty = MUSIC;
        else if (s_specialty == "Jardinage")
            specialty = GARDENING;
        else if (s_specialty == "Electricite")
            specialty = ELECTRICITY;
        else if (s_specialty == "Menuiserie")
            specialty = CARPENTRY;
        else if (s_specialty == "Mecanique")
            specialty = MECANIC;
        else
            printf("****Parsing error (employee specialty)****\n");

        employees[i] = Employee(std::stoi(s_id) - 1, std::stoi(s_quota), specialty, skill);
    }

    return employees;
}
float *extract_distance_matrix_csv(int size_p, std::string path_p)
{
    float *distances = new float[(size_p + 1) * (size_p + 1)]; //+1 for sessad
    std::ifstream file(path_p);
    std::string data;

    for (int i = 0; i < size_p + 1; i++)
    {
        for (int j = 0; j < size_p; j++)
        {
            getline(file, data, ',');
            distances[i * size_p + j] = std::stof(data);
        }
    }
    return distances;
}

/**
 * print a matrix
 */
template <typename T>
void print_matrix(int size_p, const T *matrix_p)
{
    for (int i = 0; i < size_p; i++)
    {
        for (int j = 0; j < size_p; j++)
        {
            std::cout << matrix_p[i * size_p + j] << " ";
        }
        std::cout << "\n";
    }
}