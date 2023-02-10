cmake_minimum_required(VERSION 3.22)
project(tcp_server_client)
set(CMAKE_C_STANDARD 11)

add_executable(echo_server echo_server.c)
add_executable(echo_client echo_client.c)