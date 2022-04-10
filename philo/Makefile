CC = cc 
CFALGS = -Wall -Werror -Wextra -pthread -g -fsanitize=address

HELPERS_PATH = ./src/helpers
UTILS_PATH = ./src/utils

HELPERS = ${HELPERS_PATH}/ft_isdigit.c ${HELPERS_PATH}/ft_atoi.c

UTILS = ${UTILS_PATH}/parser.c ${UTILS_PATH}/throw_error.c ${UTILS_PATH}/routine.c \
		${UTILS_PATH}/get_time.c ${UTILS_PATH}/ft_sleep.c ${UTILS_PATH}/watcher.c

SRC = ./src/philo.c ${UTILS} ${HELPERS}

OBJ = ${SRC:.c=.o}

.c.o: 
	${CC} ${CFLAGS} -c $< -o $@

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