NAME=libexp.a

SRCS = $(shell ls *.c)
OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

CFLAGS = -Wall -Werror -Wextra -MMD
LIB_DIR = ../../libft
INCLUDES = -I../../includes -I${LIB_DIR}


all : ${NAME}
dbg : all
dbg : DEBUG=1

${NAME} : ${OBJS}
	ar rcs $@ $^

${OBJS} : %.o : %.c
	gcc ${CFLAGS} ${INCLUDES} -c $< -o $@

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

-include ${DEPS}

.PHONY : all re fclean clean
