#ifndef GLOBAL_HPP
#define GLOBAL_HPP

extern int n_employee;
extern int n_mission;
extern int n_location;

extern int population_size;
extern float crossover_rate;
extern float mutation_rate;
extern int max_execution_time;
extern int max_iteration_number;
extern bool verbose;

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

typedef struct
{
    int start;
    int end;
    int mission_id;
} Time_window;

/* Timetable definitions */
#define N_WEEK_DAY 5 // 6 ?
#define START_HOUR 7
#define END_HOUR 20
#define N_WORKING_HOURS (END_HOUR - START_HOUR) //?
#define LUNCH_BREAK_START 12 * 60               //?
#define LUNCH_BREAK_END 14 * 60                 //?
#define LUNCH_BREAK_TIME 1 * 60
#define FULL_TIME_WOKRING_MINUTES_DAY 8 * 60
#define FULL_TIME_WOKRING_MINUTES_WEEK 35 * 60 // 10 ?
#define PART_TIME_WORKING_MINUTES_DAY 6 * 60
#define PART_TIME_WORKING_MINUTES_WEEK 24 * 60
#define TIME_RANGE_DAY 12 * 60 // amplitude horaire quotidienne
#define DAILY_OVERTIME 2 * 60
#define WEEKLY_OVERTIME 10 * 60
#define MONDAY 0
#define TUESDAY 1
#define WEDNESDAY 2
#define THURSDAY 3
#define FRIDAY 4
#define START_MINUTE 0
#define END_MINUTE 1
#define TRAVEL_SPEED (50 * (1000 / 60))

/* Iteration definition */
#define DEFAULT_ITERATION_NUMBER 1000
#define DEFAULT_POPULATION_SIZE 5
#define DEFAULT_RUNNING_TIME 120
#define DEFAULT_CROSSOVER_RATE 0.8
#define DEFAULT_MUTATION_RATE 0.8

/* Others */
#define MAX_MUTATION_ATTEMPT 20

/* Functions */

#endif /*GLOBAL_HPP*/