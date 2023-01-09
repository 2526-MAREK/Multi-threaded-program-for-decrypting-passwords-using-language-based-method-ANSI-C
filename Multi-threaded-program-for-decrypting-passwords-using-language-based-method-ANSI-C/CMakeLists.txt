cmake_minimum_required(VERSION 3.0)

project(password_deciphered)

include_directories(inc)


file(GLOB SRC src/*.c)



add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_link_libraries(password_deciphered -lssl -lcrypto -pthread)
