cmake_minimum_required(VERSION 3.10)
project(SocialNetworkAnalyzer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(server main.cpp Graph.cpp)

target_link_libraries(server PRIVATE httplib::httplib nlohmann_json::nlohmann_json)

if(WIN32)
    target_link_libraries(server PRIVATE ws2_32)
endif()
