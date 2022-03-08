NAME = minishell

MAIN_SRCS = $(shell ls *.c)  #exec_line.c clean_utils.c debug.c signal_dispose.c exit_shell.c
SYN_SRCS = $(shell ls syntax/*.c)
RED_SRCS = $(shell ls redirect/*.c)
PARS_SRCS = $(shell ls parser/*.c)
EXEC_SRCS = $(shell ls exec_stmnt/*.c)
EXP_SRCS = $(shell ls expansions/*.c)
ENV_SRCS = $(shell ls environment/*.c)
BLTN_SRCS = $(shell ls builtin/*.c)
SRCS = ${MAIN_SRCS} ${SYN_SRCS} ${RED_SRCS} ${PARS_SRCS} ${EXEC_SRCS} ${EXP_SRCS} ${ENV_SRCS} ${BLTN_SRCS}
OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

LIB_DIR = ../libft
LIBFT = ${LIB_DIR}/libft.a

INCLUDE = -I. -I${LIB_DIR} -I../includes
LDFLAGS = -L${LIB_DIR}
LIBRARIES = -lft -lreadline
CC = gcc

OS = $(shell uname -s)
ifeq (${OS}, Darwin)
LDFLAGS+=-L/Users/sdalton/.brew/opt/readline/lib -L/Users/sdalton/.brew/opt/readline/lib
INCLUDE+=-I/Users/sdalton/.brew/opt/readline/include -I/Users/sdalton/.brew/opt/ncurses/include
else
ifeq (${OS}, Linux)
INCLUDE+=-I/usr/share/
LDFLAGS+=-L/usr/lib/x86_64-linux-gnu/
LIBRARIES+= -ltinfo
endif
endif
CFLAGS = -Wall -Werror -Wextra ${INCLUDE} -MMD

all : ${NAME}
dbg : fclean ${NAME}
dbg : CFLAGS+=-g -fsanitize=address

${NAME} : ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${LDFLAGS} $(filter-out ${LIBFT},$^ ) -o $@ ${LIBRARIES}

${OBJS} : %.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${LIBFT} : libft ;

clean :
	rm -rf ${OBJS} ${DEPS}
	make clean -C ${LIB_DIR}

fclean : clean
	rm -rf ${NAME}
	rm -rf ${LIBFT}

re : fclean all

-include ${DEPS}

.PHONY : all re clean fclean libft

libft :
	make -C ${LIB_DIR}
