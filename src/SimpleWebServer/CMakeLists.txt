cmake_minimum_required(VERSION 3.16.0)
project(SimpleWebServer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

set(EXTERNAL_PROJECTS "${CMAKE_CURRENT_SOURCE_DIR}/../../External")
include(${EXTERNAL_PROJECTS}/External.cmake)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)