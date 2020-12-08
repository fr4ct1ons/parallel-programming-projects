cmake_minimum_required (VERSION 2.8)

project ("OpenMP")
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

file( GLOB sourceFiles
	${CMAKE_SOURCE_DIR}/GlobalSources/*.cpp
	${CMAKE_SOURCE_DIR}/GlobalSources/*.c
)

# Add source to this project's executable.
add_executable (Mosaic_PRLL "main_prll.cpp"  ${sourceFiles})
add_executable (Mosaic_SRL "main_srl.cpp"  ${sourceFiles})


include_directories(${CMAKE_SOURCE_DIR}/GlobalIncludes)


target_include_directories(Mosaic_PRLL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)
#target_include_directories(Mosaic_PRLL PUBLIC include)
target_include_directories(Mosaic_SRL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)

find_package(OpenMP)

if(OPENMP_FOUND)
message(DIR\ 1234\ IS:\ ${CMAKE_SOURCE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

#link_directories(${CMAKE_SOURCE_DIR}/GlobalSources)