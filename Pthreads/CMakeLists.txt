cmake_minimum_required (VERSION 3.8)

project ("OpenMPI")

# Include sub-projects.
add_subdirectory ("MatrixMultiplication")

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)
