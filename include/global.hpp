#ifndef GLOBAL_HPP
#define GLOBAL_HPP

enum Specialties
{
    LSF,
    LPC
};

enum Skills
{
    ELECTRICITY,
    CARPENTRY,
    MUSIC,
    MECANIC,
    GARDENING
};

/* Timetable definitions */
#define N_WEEK_DAY 5 //6 ?
#define N_WORKING_HOURS 11 //?
#define LUNCH_BREAK_1 4 //?
#define LUNCH_BREAK_2 5 //?
#define FULL_TIME_WOKRING_HOURS_DAY 8*60
#define FULL_TIME_WOKRING_HOURS_WEEK 35*60 //10 ?
#define PART_TIME_WORKING_HOURS_DAY 6*60
#define PART_TIME_WORKING_HOURS_WEEK 24*60
#define TIME_RANGE_DAY 12*60 //amplitude horaire quotidienne
#define DAILY_OVERTIME 2*60
#define WEEKLY_OVERTIME 10*60
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6 //?

#endif /*GLOBAL_HPP*/