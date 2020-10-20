

cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (TestingProject_PRLL "main_prll.cpp")
add_executable (TestingProject_SRL "main_srl.cpp")

# TODO: Add tests and install targets if needed.
#target_link_libraries(TestingProject PRIVATE mpi)

message(DIR\ 1234\ IS:\ ${CMAKE_SOURCE_DIR})

find_package(MPI)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

target_link_libraries(TestingProject_PRLL ${MPI_C_LIBRARIES})
target_link_libraries(TestingProject_SRL ${MPI_C_LIBRARIES})

target_include_directories(TestingProject_PRLL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)
target_include_directories(TestingProject_SRL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)

link_directories(${CMAKE_SOURCE_DIR}/GlobalSources)


#link_directories("GlobalSources")
