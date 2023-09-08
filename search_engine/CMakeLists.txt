cmake_minimum_required(VERSION 3.21)
project(search_engine)

set(CMAKE_CXX_STANDARD 23)
set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)
add_executable(search_engine main.cpp)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
