# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:31:43 by lboulang          #+#    #+#              #
#    Updated: 2023/05/12 16:32:42 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
LIBFT = ./libft/libft.a

SRCS = ./srcs/mandatory/main.c\
		./srcs/mandatory/acces.c\
		./srcs/mandatory/exec.c\

SRCS_BONUS = ./srcs/bonus/main_bonus.c\
		./srcs/bonus/acces_bonus.c\
		./srcs/bonus/exec_bonus.c\
		
OBJS = ${SRCS:.c=.o }
OBJS_BONUS = ${SRCS_BONUS:.c=.o }
CC = gcc
CFLAGS = -g3 -Wall -Werror -Wextra -I .

all: ${NAME}

$(NAME) : ${OBJS}
	make -C ./libft/
	$(CC) ${OBJS} ${LIBFT} -o ${NAME}

bonus : ${OBJS_BONUS}
	make -C ./libft/
	$(CC) ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}

clean : 
	make clean -C ./libft/
	rm -rf ${OBJS} 
	rm -rf ${OBJS_BONUS} 
	
fclean : clean
	make fclean -C ./libft/
	rm -rf ${LIBFT}
	rm -rf ${NAME}
	rm -rf ${BONUS}

re : fclean all