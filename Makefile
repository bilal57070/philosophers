SRCS = main.c utils.c first.c do.c \

OBJS = ${SRCS:.c=.o}
NAME = philo
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

all: ${NAME}

${NAME}: ${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re 