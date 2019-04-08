cmake_minimum_required(VERSION 3.12)
project(ope_core)

set(CMAKE_CXX_STANDARD 14)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(NLopt)
find_package(GSL)

include_directories(inc ${NLOPT_INCLUDE_DIRS} ${GSL_INCLUDE_DIR})

aux_source_directory(src CORE_SRCS)

add_library(ope_core SHARED ${CORE_SRCS})
add_executable(spherical_main spherical_main.cpp)
add_executable(cartesian_main cartesian_main.cpp)

target_link_libraries(ope_core ${GSL_LIBRARIES} ${NLOPT_LIBRARIES})
target_link_libraries(spherical_main ope_core ${NLOPT_LIBRARIES})
target_link_libraries(cartesian_main ope_core ${NLOPT_LIBRARIES})

add_subdirectory(cpython)
