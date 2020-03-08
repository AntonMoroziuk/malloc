# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/29 14:28:47 by amoroziu          #+#    #+#              #
#    Updated: 2020/01/25 15:03:31 by amoroziu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LNK_NAME = libft_malloc.so

# srcs, path and obj

SRC_N			=	free.c \
					malloc.c \
					realloc.c \
					utils.c \
					show_alloc_mem.c

SRC_P 			= ./src/
OBJ 			= $(addprefix $(OBJ_P),$(SRC_N:.c=.o))
OBJ_P			= ./obj/
INC 			= $(addprefix -I, $(INC_P))
INC_P			= ./includes/
HEADER			= $(addprefix $(INC_P), malloc.h utils.h)

# compiler

CC 				= gcc
CC_FLAGS 		= -g -Wall -Wextra -Werror

# libft

LIB_P			= ./libft/
ADD_LIB			= $(addprefix $(LIB_P),libft.a)
INC_LIB			= -I ./libft
LNK_LIB			= -L ./libft -l ftprintf

all: obj $(ADD_LIB) $(NAME)

obj:
	@mkdir -p $(OBJ_P)

$(OBJ_P)%.o:$(SRC_P)%.c $(HEADER)
	@$(CC) $(CC_FLAGS) $(INC_LIB) -I $(INC_P) -o $@ -c $<

$(ADD_LIB):
	@make -C $(LIB_P)

$(NAME): $(OBJ)
	@$(CC) -shared $(LNK_LIB) $(OBJ) -o $(NAME)
	@rm -rf $(LNK_NAME)
	@ln -s $(NAME) $(LNK_NAME)

clean:
	@rm -rf $(OBJ_P)
	@make -C $(LIB_P) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB_P) fclean
	@rm -rf $(LNK_NAME)

re: fclean all

.PHONY: all clean fclean re
