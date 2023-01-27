cmake_minimum_required(VERSION 3.20)
project(tpk4128-2023)


add_library(add SHARED add.c)

add_executable(hello hello.c)
target_link_libraries(hello PRIVATE add)



