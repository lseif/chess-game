# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

#create chess library
add_library(chess_lib ${SOURCES})

# I../includes
target_include_directories(chess_lib PRIVATE ${CMAKE_SOURCE_DIR}/includes)

# Set compile options for different configurations
target_compile_options(chess PRIVATE
    $<$<CONFIG:Debug>:-g -Wall>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
)