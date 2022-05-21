cmake_minimum_required(VERSION 3.0.0)
project(it45-operation-research VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB 
    project_SRC
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(
    main 
    ${project_SRC}
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
