# Operation research: the timetable problem
Optimization of Problems of Assignment, Planning and Routing tours of the Employees. This project was developped for school purpuse.
## Features
- Create employee timetables with missions respecting the following constraints:
  - every mission has to be affected
  - mission and employee have the same skill
  - every employee has a least one hour lunch break
  - employees have a maximum daily and weekly hour work 
  - employees have a maximum daily and weekly overtime hour work 
  - a employee have enough time to travel from a mission to the next one
- Optimize the timetables with genetic algorithm following those goals:
  - less overtime hour work
  - less distances between missions
  - less unsatisfied specialty 
- Support instance 3 csv files:
  - `Distances.csv`: distances matrix between missions
  - `Intervenants.csv`: Employees(id,Skill,Specialty,Quota)
  - `Missions.csv`: Missions(id,day,starting_period,ending_period,Skill,Specialty)

## Requirements
- [Cmake](https://cmake.org/)

## Build (Linux only)
```bash
mkdir build
cd build
cmake ..
make
```

## Usage
### Run
```bash
cd build
./it45-operation-research [options] <distance_file> <employee_file> <mission_file>
```
### Options
- Genetic algorithm options:
    ```bash
  ./it45-operation-research -p arg1 arg2 arg2 <distance_file> <employee_file> <mission_file>
    ```
    >`arg1` = population size, `arg2` = crossover rate, `arg3` = mutation rate

- iteration option:
    ```bash
  ./it45-operation-research -i arg4 <distance_file> <employee_file> <mission_file>
    ```
    >`arg4` = iteration number
- utililies options:
    ```bash
  ./it45-operation-research -v -h <distance_file> <employee_file> <mission_file>
    ```
    >-v = verbose mode <br>
    >-h = help message