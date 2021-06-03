# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 18:19:38 by lnoaille          #+#    #+#              #
#    Updated: 2021/06/03 17:05:30 by lnoaille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

SRCS =	check_args.c	check.c	chrono.c init.c main.c memory.c put_action.c survive.c utils.c \
		utils2.c		check_2.c

DEP = philosophers.h

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

all : 		${NAME}

${NAME}:	${OBJS}
			gcc  ${CFLAGS} -o ${NAME} ${SRCS}

clean :
			${RM} ${OBJS} ${BONUS}

fclean :	clean
			${RM} ${NAME}

re :		fclean all