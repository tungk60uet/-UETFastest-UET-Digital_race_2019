cmake_minimum_required(VERSION 2.8)

project(cds2019)

find_package( OpenCV REQUIRED )
find_package( Threads REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories( ${CMAKE_SOURCE_DIR}/include)

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64") 
	include_directories(${CMAKE_SOURCE_DIR}/include/x86_64)
	set(ADDITIONAL_EXECUTABLE src/IOInterface.cpp)
else()
	message(${CMAKE_SYSTEM_PROCESSOR})
endif()

add_executable(${PROJECT_NAME} 
	src/main.cpp 
	${ADDITIONAL_EXECUTABLE}
)
target_link_libraries(${PROJECT_NAME} 
	${OpenCV_LIBS} 
	${CMAKE_THREAD_LIBS_INIT}
)
