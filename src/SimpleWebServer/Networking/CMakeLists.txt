project(networking)

file(GLOB src_cpp "./*.cpp")

add_library(${PROJECT_NAME} STATIC ${src_cpp})