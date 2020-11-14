cmake_minimum_required(VERSION 3.16)

project(metro C)
add_executable(metro projects/server/src/main.c projects/server/src/Socket.c projects/server/src/Database/Database.c projects/server/src/Database/travelcard.c)
target_link_libraries(metro sqlite3)
target_include_directories(metro PUBLIC projects/server/include)