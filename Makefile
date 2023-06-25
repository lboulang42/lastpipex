# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:31:43 by lboulang          #+#    #+#              #
#    Updated: 2023/06/25 16:50:48 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
LIBFT = ./libft/libft.a

SRCS = ./srcs/mandatory/main.c\
		./srcs/mandatory/acces.c\
		./srcs/mandatory/exec.c\
		./srcs/mandatory/clean.c\

SRCS_BONUS = ./srcs/bonus/main_bonus.c\
		./srcs/bonus/acces_bonus.c\
		./srcs/bonus/exec_bonus.c\
		
OBJS = ${SRCS:.c=.o }
OBJS_BONUS = ${SRCS_BONUS:.c=.o }
CC = gcc
CFLAGS = -g3 -Wall -Werror -Wextra -I .

all: ${NAME}

$(NAME) : ${OBJS}
	make --no-print-directory  -C ./libft/
	echo "\n\t\t\t |  MAKING PIPEX MANDATORY 🔄 |"
	$(CC) ${OBJS} ${LIBFT} -o ${NAME}
	echo "\n\t\t\t |  PIPEX MANDATORY MAKED 🔄 |\n"

bonus : ${OBJS_BONUS}
	make --no-print-directory  -C ./libft/
	echo "\n\t\t\t |  MAKING PIPEX BONUS 🔄 |"
	$(CC) ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}
	echo "\n\t\t\t |  PIPEX BONUS MAKED 🔄 |\n"
	

clean : 
	@make --no-print-directory clean -C ./libft/
	rm -rf ${OBJS} 
	rm -rf ${OBJS_BONUS} 
	
fclean : clean
	@make --no-print-directory fclean -C ./libft/
	rm -rf ${LIBFT}
	rm -rf ${NAME}
	rm -rf ${NAME_BONUS}

re : fclean all