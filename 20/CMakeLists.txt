cmake_minimum_required(VERSION 3.16.0)
project(CPP_20 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} 
PUBLIC -fno-omit-frame-pointer -fsanitize=address,undefined,integer,nullability
PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_link_options(${PROJECT_NAME} 
PUBLIC -fno-omit-frame-pointer -fsanitize=address,undefined,integer,nullability)

target_link_libraries(${PROJECT_NAME} fmt::fmt)

add_compile_options(-fno-omit-frame-pointer)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


