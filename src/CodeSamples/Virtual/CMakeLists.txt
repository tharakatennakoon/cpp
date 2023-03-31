add_executable(virtual main.cpp)

target_compile_options(virtual PUBLIC -fno-omit-frame-pointer -fsanitize=address)
target_link_options(virtual PUBLIC -fno-omit-frame-pointer -fsanitize=address)