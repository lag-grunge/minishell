cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(tests)

include_directories(includes)
include_directories(libft)
#include_directories(/Users/sdalton/.brew/opt/readline/include)
include_directories(/usr/share)

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
        srcs/expansions/quote_removal.c srcs/expansions/filename_utils.c srcs/expansions/variable_utils.c
        srcs/exec_stmnt/exec_stmnt.c srcs/exec_stmnt/exec_stmnt_utils.c
        srcs/exec_stmnt/ft_which.c includes/exec_stmnt.h
        srcs/environment/environment_utils.c srcs/exec_stmnt/get_args.c
        srcs/signal_dispose.c includes/signal_dispose.h
        srcs/redirect/redirect.c srcs/redirect/redirect_utils.c srcs/exit_shell.c includes/exit_shell.h srcs/expansions/exp_args.c)


target_link_directories(minishell PUBLIC libft)
target_link_libraries(minishell libft.a)
#target_link_directories(minishell PUBLIC /Users/sdalton/.brew/opt/readline/lib)
target_link_directories(minishell PUBLIC /usr/lib/x86_64-linux-gnu/)
target_link_libraries(minishell libreadline.a)
target_link_libraries(minishell libtinfo.a)
