# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/10 15:37:21 by cpieri            #+#    #+#              #
#    Updated: 2019/11/26 11:10:21 by cpieri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************************** #
#			Ouput Name of Library			#
# ***************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so

LINK_NAME	=	libft_malloc.so

# ***************************************** #
#	Path for Sources, Objects and Includes	#
# ***************************************** #

PATH_SRCS	=	srcs

PATH_OBJS	=	objs

PATH_INCS	=	includes

# ***************************************** #
#	Names of Sources, Objects and Includes	#
# ***************************************** #

NAME_SRCS	=	malloc.c				\
				realloc.c				\
				calloc.c				\
				free.c					\
				show_alloc_mem.c		\
				shared/mini_libft_0.c	\
				shared/mini_libft_1.c	\
				shared/helpers.c		\
				shared/heap_0.c			\
				shared/heap_1.c			\
				shared/block.c

NAME_OBJS	=	$(NAME_SRCS:.c=.o)

NAME_INCS	=	malloc.h

NAME_DEPS	=	$(NAME_SRCS:.c=.d)

SRCS		=	$(addprefix $(PATH_SRCS)/,$(NAME_SRCS))

OBJS		=	$(addprefix $(PATH_OBJS)/,$(NAME_OBJS))

INCS		=	$(addprefix $(PATH_INCS)/,$(NAME_INCS))

DEPS		=	$(INCS)	\
				Makefile

# ***************************************** #
#			Flags for compile		 		#
# ***************************************** #

CC				=	clang

FLAGS_INCS		=	-Iincludes

SHARED			=	-shared

FSANITIZE		=	-fsanitize=address -fno-omit-frame-pointer

override ERROR	+=	-g3

override FLAGS	+=	-Wall -Wextra -Werror $(ERROR)


# ***************************************** #
#					Color					#
# ***************************************** #

NONE	=	\033[0m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
MAGENTA	=	\033[35m
CYAN	=	\033[36m
PINK	=	\033[38;5;206m

# ***************************************** #
#					Rules					#
# ***************************************** #

.PHONY: all clean fclean re echo

all:		$(NAME)

$(NAME):	echo $(OBJS)
			@$(CC) $(SHARED) $(FLAGS) -o $(NAME) $(OBJS)
			@echo "\n$(GREEN)$(NAME) is ready !$(NONE)"
			@ln -s $(NAME) $(LINK_NAME) 2> /dev/null || true
			@echo "$(GREEN)$(NAME) is linked to $(LINK_NAME)$(NONE)"

echo:
			@echo "$(YELLOW)Start of Compilation...$(NONE)"
			@echo "$(PINK)---------------------------$(CYAN)"
			@echo -n In progress

$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c $(DEPS)
			@mkdir $(dir $@) 2> /dev/null || true
			@$(CC) $(FLAGS) $(FLAGS_INCS) -c $< -o $@
			@echo -n .

clean:
			@echo "$(YELLOW)Start of Cleaning...$(NONE)"
			@echo "$(PINK)---------------------------$(NONE)"
			@echo "$(CYAN)Deleting all objects files...$(NONE)"
			@/bin/rm -f $(OBJS)
			@/bin/rm -rf $(PATH_OBJS) 2> /dev/null || true
			@echo "$(GREEN)Objects files have been deleted !\n$(NONE)"

fclean:		clean
			@echo "$(CYAN)Deleting all binary files...$(NONE)"
			@/bin/rm -f $(LINK_NAME)
			@/bin/rm -f $(NAME)
			@echo "$(GREEN)Binary files have been deleted !\n$(NONE)"

re:			fclean all
