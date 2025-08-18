cmake_minimum_required(VERSION 3.10)    # Phiên bản CMake tối thiểu
project(ProjectDemo C)                  # Tên project, ngôn ngữ C

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

file(GLOB_RECURSE SRC_FILES "src/*.c")

include_directories(
    inc/
    inc/states
)

add_executable(muzik_playor main.c ${SRC_FILES})  # Tạo file thực thi từ source