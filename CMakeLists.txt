# only for cmake --version >= 3.1
cmake_minimum_required(VERSION 3.16.3)

# project name
project(chessgame)

# creates the variable EXEC and sets it to chess
set(EXEC chess)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)

enable_testing()

# I../includes
include_directories(includes)

#create main executable
add_executable(chess Main.cpp)
target_link_libraries(chess PRIVATE chess_lib)

#export compile commands for clangd 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# Set default build type
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type")

add_subdirectory(src)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Test")
    add_subdirectory(tests)
endif()

# Configure flags based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
elseif(CMAKE_BUILD_TYPE STREQUAL "Test")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O0 -DTEST_MODE")
endif()