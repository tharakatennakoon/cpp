project(transferqueue)

add_executable(${PROJECT_NAME} TransferQueue.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} fmt::fmt)