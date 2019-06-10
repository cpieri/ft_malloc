# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpieri <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/10 15:37:21 by cpieri            #+#    #+#              #
#    Updated: 2019/06/10 16:37:47 by cpieri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************************** #
#			Ouput Name of Library			#
# ***************************************** #

ifeq ($(HOSTTYPE))
	HOSTTYPE := $(shell uname -m)_$(shell uname -s) 
endif

NAME		=	libft_malloc_$(HOSTTYPE).so

LINK_NAME	=	libft_malloc.so

# ***************************************** #
#	Path for Sources, Objects and Includes	#
# ***************************************** #

PATH_SRCS	=	./srcs/

PATH_OBJS	=	./objs/

PATH_INCS	=	./includes/

PATH_DEPS	=	./deps/

# ***************************************** #
#	Names of Sources, Objects and Includes	#
# ***************************************** #

NAME_SRCS	=	malloc.c	\
				realloc.c	\
				free.c		\
				show_alloc_mem.c

NAME_OBJS	=	$(NAME_SRCS:.c=.o)

NAME_INCS	=	malloc.h

# ***************************************** #
#			Flags for compile		 		#
# ***************************************** #

CC				=	clang

FSANITIZE		=	-fsanitize=address -fno-omit-frame-pointer

override ERROR	+=	-g3

override FLAGS	+=	-Wall -Wextra -Werror


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

# ***************************************** #
#					Rules					#
# ***************************************** #

.PHONY all clean fclean re echo

all:		$(NAME)

$(NAME):	$(OBJ)

$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c
			@mkdir $(dir $@) 2> /dev/null || true
			@$(CC) $(FLAGS) -c $< -o $@
			@echo -n .

clean:
			@echo "$(YELLOW)Start of Cleaning...$(NONE)"
			@echo "$(CYAN)Removing all objects files...$(NONE)"
			@/bin/rm -f $(OBJS)
			@/bin/rm -rf $(PATH_OBJS) 2> /dev/null || true
			@echo "$(GREEN)Objects is removed !$(NONE)"

fclean:		clean
			@echo "$(CYAN)Removing all binairy files....$(NONE)"
			@/bin/rm -f $(LINK_NAME)
			@/bin/rm -f $(NAME)
			@echo "$(GREEN)Binairy files is removed !$(NONE)"

re:			fclean all
