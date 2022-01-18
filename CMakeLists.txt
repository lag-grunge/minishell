cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(libft)

add_executable(minishell
        srcs/parser/cmd.c
        srcs/clean_utils.c
        includes/clean.h
        srcs/exec_line.c
        includes/minishell.h
        srcs/parser/parser.c
        includes/parser.h
        srcs/parser/redir.c
        includes/syntax.h
        srcs/syntax/syntax_utils.c
        srcs/syntax/tokens.c srcs/syntax/token_utils.c srcs/parser/subshell.c srcs/debug.c srcs/expansions/filename.c srcs/environment.c includes/environment.h srcs/expansions/variable.c includes/expansions.h srcs/expansions/quote_removal.c)

target_link_directories(minishell PUBLIC libft)
target_link_libraries(minishell libft.a)
