cmake_minimum_required(VERSION 2.8)	 

set(SOURCE_EXE main.cpp)		

set(SOURCE_LIB fazzynumber.cpp)			

add_library(fazzynumber STATIC ${SOURCE_LIB})	

add_executable(main ${SOURCE_EXE})	

target_link_libraries(main fazzynumber)
