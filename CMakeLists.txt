cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(tests)
add_subdirectory(libft)

include_directories(includes)
include_directories(libft)
if (${CMAKE_SYSTEM_NAME} EQUAL "Linux" )
    include_directories(/usr/share)
else()
    include_directories($ENV{HOME}/.brew/opt/readline/include)
endif()

add_executable(minishell
        srcs/parser/cmd.c
        srcs/clean_utils.c
        includes/clean.h
        srcs/exec_line.c
        includes/minishell.h
        srcs/parser/parser.c
        includes/parser.h
        srcs/parser/redir.c
        includes/syntax.h srcs/syntax/syntax_utils.c srcs/syntax/tokens.c srcs/syntax/token_utils.c
        srcs/parser/parenthesis.c
        srcs/debug.c srcs/expansions/filename.c srcs/environment/get_hash_get_array.c srcs/environment/set_value_get_value.c
        includes/environment.h srcs/expansions/variable.c includes/expansions.h
        srcs/expansions/filename_utils.c srcs/expansions/variable_utils.c
        srcs/exec_stmnt/exec_stmnt.c srcs/exec_stmnt/exec_stmnt_utils.c
        srcs/exec_stmnt/ft_which.c includes/exec_stmnt.h
        srcs/environment/environment_utils.c srcs/exec_stmnt/get_args.c
        srcs/signal_dispose.c
        srcs/redirect/redirect.c srcs/redirect/redirect_utils.c srcs/builtin/exit_shell.c srcs/builtin/echo.c
        includes/builtin.h srcs/expansions/exp_args.c srcs/exec_stmnt/exec_builtin.c
        srcs/syntax/quoting.c srcs/redirect/try_openfiles.c srcs/error.c includes/error.h srcs/error.c includes/error.h)


target_link_directories(minishell PUBLIC libft)
target_link_libraries(minishell libft.a)
if (${CMAKE_SYSTEM_NAME} EQUAL "Linux" )
    include_directories(/usr/share)
    target_link_directories(minishell PUBLIC /usr/lib/x86_64-linux-gnu/)
else()
    target_link_directories(minishell PUBLIC $ENV{HOME}/.brew/opt/readline/lib)
endif()
target_link_libraries(minishell libreadline.a)
target_link_libraries(minishell libtinfo.a)
