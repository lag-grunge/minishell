NAME = minishell

MAIN_SRCS = exec_line.c clean_utils.c debug.c
SYN_SRCS = $(shell ls syntax/*.c)
RED_SRCS = $(shell ls redirect/*.c)
PARS_SRCS = $(shell ls parser/*.c)
EXEC_SRCS = $(shell ls exec_stmnt/*.c)
EXP_SRCS = $(shell ls expansions/*.c)
ENV_SRCS = $(shell ls environment/*.c)
SRCS = ${MAIN_SRCS} ${SYN_SRCS} ${RED_SRCS} ${PARS_SRCS} ${EXEC_SRCS} ${EXP_SRCS} ${ENV_SRCS}
OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

LIB_DIR = ../libft
LIBFT = ${LIB_DIR}/libft.a

INCLUDE = -I../includes -I${LIB_DIR} -I/usr/share/
CFLAGS = -g -Wall -Werror -Wextra ${INCLUDE} -MMD -fsanitize=address
LDFLAGS = -L${LIB_DIR} -L/usr/local/lib
LIBRARIES = -lft -lreadline
CC = gcc

all : ${NAME}

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
