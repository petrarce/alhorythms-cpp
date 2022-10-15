cmake_minimum_required(VERSION 3.10)

project(EulerProjectSolutions)

find_package(Boost)
find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "CXX standard")
add_executable(problem25 problem25.cpp)
add_executable(problem26 problem26.cpp)
add_executable(problem27 problem27.cpp)
add_executable(problem28 problem28.cpp)
add_executable(problem23 problem23.cpp)
add_executable(problem24 problem24.cpp)
add_executable(problem2525 problem2525.cpp)
add_executable(extender-euler extended-euler.cpp)
add_executable(sor-algorythms sort_algs.cpp)
add_executable(gus-jordan guas_jordan_algorythms.cpp)
#target_link_libraries(gus-jordan Eigen3)
