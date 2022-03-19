NAME = libft.a

SRCS = $(shell ls *.c)

OBJS = $(SRCS:.c=.o)

INCLUDE = -I./

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

$(NAME) :	${OBJS}
	ar rcs ${NAME} $?

%.o	: 	%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re	: fclean all

.PHONY: all clean fclean re
