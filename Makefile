# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:31:43 by lboulang          #+#    #+#              #
#    Updated: 2023/06/25 20:31:42 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
LIBFT = ./libft/libft.a

SRCS = ./srcs/mandatory/main.c ./srcs/mandatory/acces.c ./srcs/mandatory/exec.c ./srcs/mandatory/clean.c

SRCS_BONUS = ./srcs/bonus/main_bonus.c\
		./srcs/bonus/acces_bonus.c\
		./srcs/bonus/exec_bonus.c\
		
OBJS = ${SRCS:.c=.o }
OBJS_BONUS = ${SRCS_BONUS:.c=.o }
CC = @ gcc
CFLAGS = -g3 -Wall -Werror -Wextra -I .

all: ${NAME}

$(NAME) : ${OBJS}
	@make --no-print-directory  -C ./libft/
	@echo -n "\n🟦📘🟦📘🟦📘🟦📘🟦📘🟦📘| 🔌 MAKING PIPEX MANDATORY  🔌 |🟦📘🟦📘🟦📘🟦📘🟦📘🟦📘\n"
	@echo -n "...................."
	@sleep 0.2
	@echo -n "...................."
	@sleep 0.2
	@echo -n "...................."
	@sleep 0.2
	@echo -n "...................."
	@$(CC) ${OBJS} ${LIBFT} -o ${NAME}
	@echo "\n🟩✅🟩✅🟩✅🟩✅🟩✅🟩✅ | 🔌 PIPEX MANDATORY MAKED 🔌 |🟩✅🟩✅🟩✅🟩✅🟩✅🟩✅\n"

bonus : ${OBJS_BONUS}
	@make --no-print-directory  -C ./libft/
	@echo "\n\t\t\t |  MAKING PIPEX BONUS 🔄 |"
	@$(CC) ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}
	@echo "\n\t\t\t |  PIPEX BONUS MAKED 🔄 |\n"
	

clean : 
	@make --no-print-directory clean -C ./libft/
	@echo "\n\t\t\t | 📚  CLEANING PIPEX 🚮 📚  |\t\t"
	@rm -rf ${OBJS} 
	@rm -rf ${OBJS_BONUS} 
	@echo "\n\t\t\t | 📚 PIPEX CLEANED 🚮 📚  |\t\t"
	
fclean : clean
	@echo "\n\t\t\t | 📚  FCLEANING LIBFT 🚮 📚  |\t\t"
	@rm -rf ${LIBFT}
	@echo "\n\t\t\t | 📚  LIBFT FCLEANED 🚯 📚  |\n"
	@echo "\n\t\t\t | 📚  FCLEANING PIPEX 🚮 📚  |\t\t"
	@rm -rf ${NAME}
	@rm -rf ${NAME_BONUS}
	@echo "\n\t\t\t | 📚  PIPEX FCLEANED 🚮 📚  |\t\t"

re : fclean all