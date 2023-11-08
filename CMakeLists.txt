cmake_minimum_required(VERSION 3.16.0)

if (APPLE)
  set (CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")
endif()

add_subdirectory(src)
add_subdirectory(20)