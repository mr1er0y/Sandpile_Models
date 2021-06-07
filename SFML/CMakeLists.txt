cmake_minimum_required(VERSION 3.16)
project(Sandpile_Models)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS graphics window system)

add_executable(Sandpile_Models main.cpp)

target_link_libraries(Sandpile_Models PUBLIC ${SFML_LIBRARIES})
include_directories(${SFML_INCLUDE_DIR})
