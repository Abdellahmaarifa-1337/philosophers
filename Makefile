CC = cc 
CFALGS = -Wall -Werror -Wextra -pthread

HELPERS = ./src/helpers
UTILS = ./src/utils

SRC = ./src/philosopher.c ${HELPERS}/ft_atoi.c ${HELPERS}/ft_isdigit.c \
		${HELPERS}/ft_strlen.c ${UTILS}/error_handler.c ${HELPERS}/ft_strdup.c

OBJ = ${SRC:.c=.o}

NAME = philo

all: ${NAME}

${NAME} : ${OBJ}
		${CC} ${OBJ} -o ${NAME}

${OBJ} : ${SRC}

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all

