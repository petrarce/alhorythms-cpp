cmake_minimum_required(VERSION 3.10)

project(EulerProjectSolutions)

find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED)
find_package( absl REQUIRED)

add_subdirectory(../libcore/ libcore)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "CXX standard")
file(GLOB FILES_LIST
	LIST_DIRECTORIES false
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	*.cpp)
foreach(FILE IN LISTS FILES_LIST)
	string(REPLACE ".cpp" "" FILE_NAME ${FILE})
	add_executable(${FILE_NAME} ${FILE})
	target_link_libraries(${FILE_NAME}
            PRIVATE
                Eigen3::Eigen
                pthread
                tbb

                libcore::math
                inf::int

                absl::algorithm
                absl::base
                absl::debugging
                absl::flat_hash_map
                absl::flags
                absl::memory
                absl::meta
                absl::numeric
                absl::random_random
                absl::strings
                absl::synchronization
                absl::time
                absl::utility
        )
endforeach()
