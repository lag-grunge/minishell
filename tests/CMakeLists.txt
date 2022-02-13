#
#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        # Specify the commit you depend on and update it regularly.
#        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
## For Windows: Prevent overriding the parent project's compiler/linker settings
##set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

## Now simply link against gtest or gtest_main as needed. Eg
#add_executable(example example.cpp)
#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)
# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../includes ../libft)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run test1.cpp tests2.cpp ../srcs/syntax/token_utils.c ../srcs/syntax/syntax_utils.c
                ../srcs/expansions/quote_removal.c)
target_link_directories(Google_Tests_run PUBLIC ../libft)
target_link_directories(Google_Tests_run PUBLIC ./lib/ )
target_link_libraries(Google_Tests_run libft.a)
target_link_libraries(Google_Tests_run gtest_main)
