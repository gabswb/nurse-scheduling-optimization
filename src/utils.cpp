#include "utils.hpp"

size_t extract_rows_nb_csv(std::string path_p)
{
    size_t rows = 0;
    std::ifstream file(path_p);
    std::string line;

    while (getline(file, line)) 
        rows++;

    return rows;
}

Mission* extract_mission_csv(size_t size_p, std::string path_p)
{
    Mission* missions = new Mission[size_p];
    std::ifstream file(path_p);
    std::string s_id, s_day, s_starting_period, s_ending_period, s_specialty, s_skill;
    Specialties specialty;
    Skills skill;


    for(size_t i=0; i<size_p; i++){
        getline(file, s_id, ',');
        getline(file, s_day, ',');
        getline(file, s_starting_period, ',');
        getline(file, s_ending_period, ',');
        getline(file, s_specialty, ',');
        getline(file, s_skill, '\n');

        if(s_skill == "LPC") specialty = LPC;
        else if(s_skill == "LSF") specialty = LSF;

        if(s_specialty == "Musique") skill = MUSIC;
        else if (s_specialty == "Jardinage") skill = GARDENING;
        else if (s_specialty == "Electricite") skill = ELECTRICITY;
        else if (s_specialty == "Menuiserie") skill = CARPENTRY;
        else if (s_specialty == "Mecanique") skill = MECANIC;

        //std::cout << s_id << " " << s_day << " " << s_starting_period<< " " <<  s_ending_period<< " " << s_specialty<< " " <<  s_skill << "\n";

        missions[i] = Mission(std::stoi(s_id), std::stoi(s_day), std::stoi(s_starting_period), std::stoi(s_ending_period), specialty, skill);
    }

    return missions;
}

Employee* extract_employee_csv(size_t size_p, std::string path_p)
{
    Employee* employees = new Employee[size_p];
    std::ifstream file(path_p);
    std::string s_id, s_quota, s_skill, s_specialty, garbage;
    Specialties specialty;
    Skills skill;

    for(size_t i=0; i<size_p; i++){
        getline(file, s_id, ',');
        getline(file, s_skill, ',');
        getline(file, s_specialty, ',');
        getline(file, s_quota, '\n');
        
        // std::cout<< "s_id : "<< s_id<< " s_skill : " << s_skill <<" s_specialty : " << s_specialty<<" s_quota : "<<s_quota<<std::endl;
        // std::cout<<"end"<< std:: endl;

        if(s_skill == "LPC") specialty = LPC;
        else if(s_skill == "LSF") specialty = LSF;

        if(s_specialty == "Musique") skill = MUSIC;
        else if (s_specialty == "Jardinage") skill = GARDENING;
        else if (s_specialty == "Electricite") skill = ELECTRICITY;
        else if (s_specialty == "Menuiserie") skill = CARPENTRY;
        else if (s_specialty == "Mecanique") skill = MECANIC;

        //std::cout<< "s_id : "<< s_id<< " s_skill : " << skill <<" s_specialty : " << specialty<<" s_quota : "<<s_quota<<std::endl;

        employees[i] = Employee(std::stoi(s_id), std::stoi(s_quota), specialty, skill);
    }

    return employees;

}
float* extract_distance_matrix_csv(size_t size_p, std::string path_p)
{
    float* distances = new float[(size_p+1) * (size_p+1)];//+1 for sessad
    std::ifstream file(path_p);
    std::string data;

    for(size_t i=0; i<size_p+1; i++){
        for(size_t j=0; j< size_p; j++){
            getline(file, data, ',');
            distances[i*size_p + j] = std::stof(data);
        } 
    }

    return distances;
}
