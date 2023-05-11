NAME=philo
CC=gcc
FLAGS=-Wall -Wextra -Werror
SRCS=$(filter-out $(wildcard *_bonus.c), $(wildcard *.c))
OBJS=$(patsubst %.c,%.o,$(SRCS))
SRCS_BONUS:=$(wildcard *.c)
OBJS_BONUS:=$(patsubst %.c,%.o,$(SRCS_BONUS))


${NAME} : ${OBJS}
	$(CC) -pthread $(OBJS) -o $(NAME)

.c.o :
	$(CC) ${FLAGS} -c $< -o ${<:.c=.o}

all : ${NAME}

clean :
	rm -rf ${OBJS_BONUS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

copy :
	rsync -av -progress ./ "/nfs/homes/bburguie/Documents/tronc commun/philosophers/mon_repo/philo" --exclude .git