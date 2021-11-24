NAME = parser

SRCS = tokens.c
OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

LIBFT = libft/libft.a

INCLUDE = -I. -I./libft
CFLAGS = -g -Wall -Werror -Wextra ${INCLUDE} -MMD
LDFLAGS = -L./libft
LIBRARIES = -lft
CC = gcc

all : ${NAME}

${NAME} : ${LIBFT}
	${CC} ${CFLAGS} ${LDFLAGS} tokens.c -o $@ ${LIBRARIES}

${OBJS} : %.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${LIBFT} : libft ;

clean : 
	rm -rf ${OBJS} ${DEPS}
	make clean -C libft/

fclean : clean
	rm -rf ${NAME}
	rm -rf ${LIBFT}

re : fclean all

-include ${DEPS}

.PHONY : all re clean fclean libft

libft : 
	make -C libft/
