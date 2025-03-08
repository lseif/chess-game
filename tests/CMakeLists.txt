add_executable(tests Tests.cpp)

#include(CTest)
include(Catch)

target_link_libraries(tests PUBLIC chess_lib Catch2::Catch2WithMain)


catch_discover_tests(tests)
