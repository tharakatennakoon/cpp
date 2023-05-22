project(concurrency)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} 
PUBLIC -fno-omit-frame-pointer -fsanitize=address,undefined,integer,nullability
PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_link_options(${PROJECT_NAME} 
PUBLIC -fno-omit-frame-pointer -fsanitize=address,undefined,integer,nullability)

target_link_libraries(${PROJECT_NAME} fmt::fmt)

add_compile_options(-fno-omit-frame-pointer)