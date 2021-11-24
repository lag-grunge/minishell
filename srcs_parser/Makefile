NAME = parser

SRCS = tokens.c

LIBFT = libft/libft.a

INCLUDE = -I. -I./libft
CFLAGS = -Wall -Werror -Wextra ${INCLUDE}
LDFLAGS = -L./libft
LIBRARIES = -lft

${NAME} : ${LIBFT}
	${CC} ${CFLAGS} ${LDFLAGS} tokens.c -o $@ ${LIBRARIES}

${LIBFT} : libft ;

.PHONY : all re clean fclean libft

libft : 
	make -C libft/
