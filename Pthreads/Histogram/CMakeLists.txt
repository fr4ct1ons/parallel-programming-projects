cmake_minimum_required (VERSION 2.8)

file( GLOB sourceFiles
	${CMAKE_SOURCE_DIR}/GlobalSources/*.cpp
	${CMAKE_SOURCE_DIR}/GlobalSources/*.c
)

# Add source to this project's executable.
add_executable (Histogram_PRLL "main_prll.cpp"  ${sourceFiles})
add_executable (Histogram_SRL "main_srl.cpp"  ${sourceFiles})

message(DIR\ 1234\ IS:\ ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/GlobalIncludes)

target_link_libraries(Histogram_PRLL pthread)
target_link_libraries(Histogram_PRLL rt)
#target_include_directories(MatMult_PRLL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)

#SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

target_include_directories(Histogram_PRLL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)
target_include_directories(Histogram_PRLL PUBLIC include)
target_include_directories(Histogram_SRL PUBLIC ${CMAKE_SOURCE_DIR}/GlobalIncludes)

#link_directories(${CMAKE_SOURCE_DIR}/GlobalSources)