cmake_minimum_required(VERSION 3.10)
project(Client)
add_executable(client client.cpp)
TARGET_LINK_LIBRARIES( client pthread )
