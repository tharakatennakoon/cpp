cmake_minimum_required(VERSION 3.0.0)
project(cpp_20 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} 
PUBLIC -fno-omit-frame-pointer -fsanitize=address,undefined,integer,nullability
PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_link_options(${PROJECT_NAME} 
PUBLIC -fno-omit-frame-pointer -fsanitize=address,undefined,integer,nullability)


