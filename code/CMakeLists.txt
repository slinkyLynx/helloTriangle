cmake_minimum_required(VERSION 3.28)

project(helloTriangle VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -O2")

add_subdirectory(src)
add_subdirectory(test)
