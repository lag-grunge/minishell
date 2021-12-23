cmake_minimum_required(VERSION 3.21)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(srcs_parser)
include_directories(srcs_parser/libft)

add_executable(minishell
        srcs_parser/cmd.c
        srcs_parser/clean.c
        srcs_parser/clean.h
        srcs_parser/exec_line.c
        srcs_parser/minishell.h
        srcs_parser/parser.c
        srcs_parser/parser.h
        srcs_parser/redir.c
        srcs_parser/syntax.h
        srcs_parser/syntax_utils.c
        srcs_parser/tokens.c srcs_parser/token_utils.c srcs_parser/subshell.c srcs_parser/debug.c)

target_link_directories(minishell PUBLIC srcs_parser/libft)
target_link_libraries(minishell libft.a)
