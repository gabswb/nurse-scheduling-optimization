#ifndef GENE_HPP
#define GENE_HPP

#include <iostream>
#include "global.hpp"

enum Skills
{
    LSF,
    LPC
};

enum Specialties
{
    ELECTRICITY,
    CARPENTRY,
    MUSIC,
    MECANIC,
    GARDENING
};

typedef struct Mission 
{
public:
    int id;
    int day;
    int start_minute;
    int end_minute;
    Specialties specialty;
    Skills skill;

    Mission();
    Mission(int id, int day_p, int start_minute_p, int end_minute_p, Specialties specialty_p, Skills skill_p);

    friend std::ostream &operator<<(std::ostream &output, const Mission &m);
    
}Mission;

typedef struct Employee
{
public:
    int id;
    int quota;
    Specialties specialty;
    Skills skill;

    Employee();
    Employee(int id_p, int quota_p, Specialties specialty_p, Skills skill_p);

    friend std::ostream &operator<<(std::ostream &output, const Employee &e);
} Employee;



typedef struct
{
    int start;
    int end;
    int mission_id;
    Specialties specialty;
    Skills skill;
} Gene;

#endif /*GENE_HPP*/