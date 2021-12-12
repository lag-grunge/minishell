NAME = parser

SRCS = tokens.c parser.c parser_utils.c syntax.c syntax_utils.c syntax_write.c
OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

LIBFT = libft/libft.a

INCLUDE = -I. -I./libft
CFLAGS = -g -Wall -Werror -Wextra ${INCLUDE} -MMD
LDFLAGS = -L./libft
LIBRARIES = -lft
CC = gcc

all : ${NAME}

${NAME} : ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${LDFLAGS} $(filter-out ${LIBFT},$^ ) -o $@ ${LIBRARIES}

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
