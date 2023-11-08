cmake_minimum_required(VERSION 3.16.0)

set(EXTERNAL_INCLUDED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_QUIET off) 

FetchContent_Declare(
  googletest  
  GIT_REPOSITORY https://github.com/google/googletest.git
  SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src/gtest"
  BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/build/gtest"
  GIT_TAG v1.14.0
)

FetchContent_GetProperties(googletest)

if (NOT googletest_POPULATED)
  message("Downloading gtest library...")
  FetchContent_MakeAvailable(googletest)
endif()

FetchContent_Declare(fmt
  GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
  SOURCE_DIR      "${CMAKE_CURRENT_LIST_DIR}/src/fmt"
  BINARY_DIR      "${CMAKE_CURRENT_LIST_DIR}/build/fmt"
  GIT_TAG 10.1.1
)

FetchContent_GetProperties(fmt)

if (NOT fmt_POPULATED)
  message("Downloading fmt library...")
  FetchContent_MakeAvailable(fmt)
endif()

FetchContent_Declare(stb
  GIT_REPOSITORY  https://github.com/nothings/stb.git
  SOURCE_DIR      "${CMAKE_CURRENT_LIST_DIR}/src/stb"
  BINARY_DIR      "${CMAKE_CURRENT_LIST_DIR}/build/stb"
  GIT_TAG beebb24b945efdea3b9bba23affb8eb3ba8982e7
)

FetchContent_GetProperties(stb)

if (NOT stb_POPULATED)
  message("Downloading stb library...")
  FetchContent_MakeAvailable(stb)
endif()
