cmake_minimum_required(VERSION 3.16.0)
project(OpenGLSample VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(EXTERNAL_PROJECTS "${CMAKE_CURRENT_SOURCE_DIR}/../../External")
include(${EXTERNAL_PROJECTS}/External.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glm)
include_directories(${EXTERNAL_PROJECTS}/src)

find_package(glfw3 3.3 REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED )

add_executable(${PROJECT_NAME} 
    main.cpp 
    BasicTriangle.cpp 
    ModelTransform.cpp 
    UniformBuffers.cpp 
    UniformBuffersMultiBind.cpp
    ./glad/src/glad.c)

target_link_libraries(${PROJECT_NAME} glfw GLU GL ${CMAKE_DL_LIBS})

file(COPY shader res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
