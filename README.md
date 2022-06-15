# Operation research: nurse scheduling problem
Optimization of Problems of Assignment, Planning and Routing tours of the employees with a Genetic Algorithm.
## Features
- The genetic algorithm minimize the following fitness for a solution s:

  $\large f_{employees} = \frac{\zeta \cdot \sigma_{WH}(s)+ \gamma \cdot \sigma_{OH}(s) + \kappa \cdot \sigma_D(s)}{3}$

  - $\sigma_{WH}(s)$ = standard derviation of wasted hours
  - $\sigma_{OH}(s)$ = standard derivation of employee overtime
  - $\sigma_{D}(s)$ = standard derviation of distance travelled by employees
  - $\gamma, \zeta, \kappa$ correlation factors

- Create employee timetables with missions respecting the following constraints:
  - every mission has to be affected
  - mission and employee have the same skill
  - every employee has a least one hour lunch break
  - employees have a maximum daily and weekly hour work 
  - employees have a maximum daily and weekly overtime hour work 
  - a employee have enough time to travel from a mission to the next one

- Support instance 3 csv files:
  - `Distances.csv`: distances matrix between missions
  - `Intervenants.csv`: Employees(id,Skill,Specialty,Quota)
  - `Missions.csv`: Missions(id,day,starting_period,ending_period,Skill,Specialty)


## Build 
Only tested on linux

### Requirements
- [Cmake](https://cmake.org/) version 3.10 or higher

### Build and run with bash script
```bash
bash build.sh
bash run.sh [options] <distance_file> <employee_file> <mission_file>
```
Exemple of usage of ```run.sh``` script (see usage section below):
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

## Usage
```bash
 Usage: ./nsp-solver [options] <distance_file> <employee_file> <mission_file>
```
```bash
 options:
  [-p arg1 arg2 arg2] ,arg1 = population size, arg2 = crossover rate, arg3 = mutation rate
  [-t arg3]           ,arg3 = max execution time
  [-i arg4]           ,arg4 = max iteration number
  [-v]                ,verbose mode
  [-h]                ,print this usage message and exit
```
