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



## Build (Linux only)
### Requirements
- [Cmake](https://cmake.org/)

### Build and run with bash script
```bash
bash build.sh
bash run.sh <options>
```
Exemple of usage of ```run.sh``` script :
```bash
bash run.sh -i 100000 -p 100 0.7 0.3 ../instances/96-6/Distances.csv ../instances/96-6/Intervenants.csv ../instances/96-6/Missions.csv
```

### Build with Cmake

```bash
mkdir build
cd build
cmake ..
make
```

### Build with Make (Without Cmake)
```bash
make
```

## Usage
### Run
```bash
cd build
./it45-operation-research [options] <distance_file> <employee_file> <mission_file>
```

### Options
All of theses options are compatible together except h
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

- execution time option:
    ```bash
  ./it45-operation-research -t arg5 <distance_file> <employee_file> <mission_file>
    ```
    >`arg5` = max time of execution

- utililies options:
    ```bash
  ./it45-operation-research -v <distance_file> <employee_file> <mission_file>
    ```
    >-v = verbose mode <br>
  
  ```bash
  ./it45-operation-research -h
  ```
  >-h = help message
