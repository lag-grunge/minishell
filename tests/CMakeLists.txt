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
add_definitions(-DTEST_G)
#if ($OS EQUAL "Linux" )
#    add_subdirectory(/home/dfyz/CLionProjects/minishell/libft /home/dfyz/CLionProjects/minishell/libft)
#else()
#add_subdirectory($ENV{HOME}/CLionProjects/minishell/libft $ENV{HOME}/CLionProjects/minishell/libft)
#endif()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../includes ../libft)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run test_quote_removal.cpp tests2.cpp tests_var_exp.cpp ../srcs/syntax/token_utils.c ../srcs/syntax/syntax_utils.c
                ../srcs/syntax/quoting.c ../srcs/expansions/filename_utils.c ../srcs/expansions/variable_utils.c
                ../srcs/environment/set_value_get_value.c ../srcs/environment/environment_utils.c ../srcs/environment/get_hash_get_array.c
                ../srcs/syntax/tokens.c ../srcs/clean_utils.c get_tokens_tests.cpp ../srcs/error.c)
target_link_directories(Google_Tests_run PUBLIC ../libft)
target_link_directories(Google_Tests_run PUBLIC ./lib/ )
target_link_libraries(Google_Tests_run libft.a)
target_link_libraries(Google_Tests_run gtest_main)
