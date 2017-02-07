cmake_minimum_required(VERSION 2.8)
project(hokuyo-test)

add_definitions(-std=c++11)
link_directories(/usr/local/lib)

set(SOURCE src/hokuyo-test.cpp)

add_executable(hokuyo-test ${SOURCE})
target_link_libraries(hokuyo-test urg_cpp)

add_custom_target(format clang-format -i ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

install(TARGETS hokuyo-test RUNTIME DESTINATION bin)
