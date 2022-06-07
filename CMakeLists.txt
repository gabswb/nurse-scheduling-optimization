cmake_minimum_required(VERSION 3.0.0)
project(it45-operation-research VERSION 0.1.0)

include(CTest)
enable_testing()


set(SOURCES
	src/Mission.cpp
	src/Employee.cpp
	src/Gene.cpp
    src/Chromosome.cpp
    src/solver.cpp
    src/utils.cpp
)

set(HEADERS
    include/global.hpp
    include/Mission.hpp
    include/Employee.hpp
    include/Gene.hpp
    include/Chromosome.hpp
    include/utils.hpp
    include/solver.hpp
)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_compile_options(-Wall -Wextra -g)

add_executable(it45-operation-research src/main.cpp ${SOURCES} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
