# CMakeList.txt : CMake project for TestingProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file( GLOB sourceFiles
	${CMAKE_SOURCE_DIR}/GlobalSources/*.cpp
	${CMAKE_SOURCE_DIR}/GlobalSources/*.c
)

# Add source to this project's executable.
add_executable (OETS_PRLL "oets_prll.cpp" ${sourceFiles})
add_executable (OETS_SRL "oets_srl.cpp" ${sourceFiles})

# TODO: Add tests and install targets if needed.
#target_link_libraries(TestingProject PRIVATE mpi)

message(WOLOLO\ 5678\ IS:\ ${CMAKE_SOURCE_DIR})

find_package(MPI)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

target_link_libraries(OETS_PRLL ${MPI_C_LIBRARIES})
target_link_libraries(OETS_SRL ${MPI_C_LIBRARIES})

target_include_directories(OETS_PRLL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)
target_include_directories(OETS_SRL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/GlobalIncludes)

link_directories(${CMAKE_SOURCE_DIR}/GlobalSources)

#add_library(OETS_PRLL STATIC ${sourceFiles})
#add_library(OETS_SRL STATIC ${sourceFiles})

#link_directories("GlobalSources")
