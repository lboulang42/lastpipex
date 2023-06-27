# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:31:43 by lboulang          #+#    #+#              #
#    Updated: 2023/06/27 14:33:20 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME
NAME = 			pipex
NAME_BONUS =	 pipex_bonus
#LIBRARIES
LIBFT = 		./libft/libft.a
#SOURCES
SRCS =			./srcs/mandatory/main.c\
				./srcs/mandatory/acces.c\
				./srcs/mandatory/exec.c\
				./srcs/mandatory/clean.c
SRCS_BONUS =	./srcs/bonus/main_bonus.c\
				./srcs/bonus/acces_bonus.c\
				./srcs/bonus/exec_bonus.c\
				./srcs/bonus/clean_bonus.c\
				./srcs/bonus/gnl_bonus.c
#OBJECTS
OBJS = ${SRCS:.c=.o }
OBJS_BONUS = ${SRCS_BONUS:.c=.o }
#COMPILER
CC = @ gcc
CFLAGS = -g3 -Wall -Werror -Wextra -I .
#VISUAL
LOADING_BAR = @echo -n "......................" ; sleep 0.05 ; echo -n "......................" ; sleep 0.05 ; echo -n "......................"; sleep 0.05; echo -n "......................"
BOLD_TEXT = \033[1m
RESET_TEXT = \033[0m

all: ${NAME}

$(NAME) : ${OBJS}
	@make --no-print-directory  -C ./libft/
	@echo -n "\n🟦📘🟦📘🟦📘🟦📘🟦📘🟦📘 | 🍀🔌 MAKING PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) 🔌🍀 | 🟦📘🟦📘🟦📘🟦📘🟦📘🟦📘\n"
	${LOADING_BAR}
	$(CC) ${OBJS} ${LIBFT} -o ${NAME}
	@echo "\n🟩✅🟩✅🟩✅🟩✅🟩✅🟩✅ | 🍀🔌 PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) MAKED 🔌🍀 | 🟩✅🟩✅🟩✅🟩✅🟩✅🟩✅\n\n"
	
bonus : ${OBJS_BONUS}
	@make --no-print-directory  -C ./libft/
	@echo -n "\n🟦📘🟦📘🟦📘🟦📘🟦📘🟦📘 | 🔥🔌 MAKING PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) 🔌🔥 | 🟦📘🟦📘🟦📘🟦📘🟦📘🟦📘\n"
	${LOADING_BAR}
	@$(CC) ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}
	@echo "\n🟩✅🟩✅🟩✅🟩✅🟩✅🟩✅ | 🔥🔌 PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) MAKED 🔌🔥 | 🟩✅🟩✅🟩✅🟩✅🟩✅🟩✅\n\n"
	

clean : 
	@make --no-print-directory clean -C ./libft/
	@echo "\n🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌 | 🍀🔌 CLEANING PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) 🔌🍀 | 🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌"
	${LOADING_BAR}
	@rm -rf ${OBJS} 
	@echo "\n🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌 | 🍀🔌 PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) CLEANED 🔌🍀 | 🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌"
	@echo "\n🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌 | 🔥🔌 CLEANING PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) 🔌🔥 | 🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌🧽🔌"
	$(LOADING_BAR)
	@rm -rf ${OBJS_BONUS} 
	@echo "\n🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌 | 🔥🔌 PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) CLEANED 🔌🔥 | 🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌🚮🔌\n\n"
	
fclean : clean
	@echo "🧼📚🧼📚🧼📚🧼📚🧼📚🧼📚🧼📚 | 🧼📚  FCLEANING $(BOLD_TEXT)LIBFT$(RESET_TEXT) 📚🧼 |🧼📚🧼📚🧼📚🧼📚🧼📚🧼📚🧼📚"
	${LOADING_BAR}
	@rm -rf ${LIBFT}
	@echo "\n🚱📚🚱📚🚱📚🚱📚🚱📚🚱📚🚱📚 | 🚱📚 $(BOLD_TEXT)LIBFT$(RESET_TEXT) FCLEANED 📚🚱 |🚱📚🚱📚🚱📚🚱📚🚱📚🚱📚🚱📚\n\n"
	
	@echo "🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌 | 🍀🔌 FCLEANING PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) 🔌🍀 |🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌"
	$(LOADING_BAR)
	@rm -rf ${NAME}
	@echo "\n🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌 | 🍀🔌 PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) FCLEANED 🔌🍀 |🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌\n"
	@echo "🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌 | 🔥🔌 FCLEANING PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) 🔌🔥 |🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌🧼🔌"
	$(LOADING_BAR)
	@rm -rf ${NAME_BONUS}
	@echo "\n🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌 | 🔥🔌 PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) FCLEANED 🔌🔥 |🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌🚱🔌\n"

re : fclean all