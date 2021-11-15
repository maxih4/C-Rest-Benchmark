cmake_minimum_required(VERSION 3.7)
project(cpprestsdk)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(cpprestsdk ${SOURCE_FILES})

find_library(CPPREST_LIB cpprest)
find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
find_package(OpenSSL 1.0.0 REQUIRED)

target_link_libraries(cpprestsdk
        ${CPPREST_LIB}
        Boost::boost
        Boost::random
        Boost::system
        Boost::thread
        Boost::filesystem
        Boost::chrono
        Boost::atomic
        Boost::date_time
        Boost::regex
        OpenSSL::SSL)