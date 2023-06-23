# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:31:43 by lboulang          #+#    #+#              #
#    Updated: 2023/05/12 16:30:50 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi_itoa.c\
ft_calloc.c\
ft_isalnum.c\
ft_isascii.c\
ft_len.c\
ft_lst1.c\
ft_lst2.c\
ft_mem.c\
ft_put_fd.c\
ft_put.c\
ft_split.c\
ft_str_operation.c\
ft_strchr.c\
ft_strl.c\
ft_strn.c\
ft_strtrim.c\
ft_free_tab.c\
./ft_printf/ft_printf.c\
./ft_printf/printf_text.c\
./ft_printf/printf_nbr.c\

OBJ = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g3 -Wall -Werror -Wextra -I.
NAME = libft.a

$(NAME):$(OBJ)
	ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)