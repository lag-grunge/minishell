project(Google_Tests_run)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(libft)
include_directories(includes)

add_executable(Google_Tests_run quote_removal.cpp)

# linking Google_Tests_run with expansions which will be tested
target_link_directories(Google_Tests_run PUBLIC srcs/expansions/)
target_link_directories(Google_Tests_run PUBLIC srcs/syntax/)
target_link_directories(Google_Tests_run PUBLIC libft)
target_link_libraries(Google_Tests_run libexp.a)
target_link_libraries(Google_Tests_run libsyn.a)
target_link_libraries(Google_Tests_run libft.a)
target_link_libraries(Google_Tests_run gtest gtest_main)
