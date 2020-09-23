# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenMPI")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#add_library(
	#mpi SHARED IMPORTED
	#GlobalIncludes/MPI/mpi.h
	#mpi.cpp
	#../GlobalSources/MPI/x86/msmpi.lib
	#)


#set_target_properties(mpi PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/GlobalSources/MPI/x86/msmpi.lib)

# Include sub-projects.
add_subdirectory ("TestingProject")