cmake_minimum_required(VERSION 3.0.0)
project(nsp-solver VERSION 0.1.0)

include(CTest)
enable_testing()


set(SOURCES
	src/gene.cpp
    src/Chromosome.cpp
    src/solver.cpp
    src/utils.cpp
)

set(HEADERS
    include/global.hpp
    include/gene.hpp
    include/Chromosome.hpp
    include/utils.hpp
    include/solver.hpp
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto")

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(nsp-solver src/main.cpp ${SOURCES} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
