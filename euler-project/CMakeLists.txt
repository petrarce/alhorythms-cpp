cmake_minimum_required(VERSION 3.10)

project(EulerProjectSolutions)

find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "CXX standard")
file(GLOB FILES_LIST
	LIST_DIRECTORIES false
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	*.cpp)
foreach(FILE IN LISTS FILES_LIST)
	string(REPLACE ".cpp" "" FILE_NAME ${FILE})
	add_executable(${FILE_NAME} ${FILE})
	target_link_libraries(${FILE_NAME}
		Eigen3::Eigen pthread tbb)
endforeach()
