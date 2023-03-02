cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(flipimage VERSION 1.0)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(flipimage ${PROJECT_SOURCE_DIR}/src/main.cpp)
configure_file(${PROJECT_SOURCE_DIR}/include/flipimageConfig.h.in flipimageConfig.h)
# we add the files in the include directory to be included
# while compiling all the source code
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# we add the sub-directories that we want CMake to scan
add_subdirectory(include)
add_subdirectory(src)
configure_file(${PROJECT_SOURCE_DIR}/include/flipimageConfig.h.in flipimageConfig.h)
target_link_libraries(flipimage ${OpenCV_LIBS})
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(flipimage PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include")


