include(FetchContent)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

add_subdirectory(LeetCode)
add_subdirectory(CodeSamples)
add_subdirectory(TransferQueue)