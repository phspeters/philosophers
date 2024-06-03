# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 19:11:03 by pehenri2          #+#    #+#              #
#    Updated: 2024/06/03 15:47:24 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME				=	philo_bonus
CC					=	cc
CFLAGS				=	-Wextra -Wall -Werror -Wunreachable-code -g3 -fsanitize=thread -pthread
HEADERS				=	-I .
FILES				= 	main.c \
						invitations.c \
						table.c \
						philosophers.c \
						dinner.c \
						host.c \
						time.c \
						rules.c
						
OBJS				= 	$(FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR				= 	obj

.DEFAULT_GOAL = $(NAME)

all: $(NAME) 

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<\n)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Deleted object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "Deleted executable files and static libraries"

re: fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader

val: all
	valgrind --leak-check=full \
		--trace-children=yes \
		--show-leak-kinds=all \
		./$(NAME) 5 800 200 200
#		--track-fds=yes \
#       --track-origins=yes \
#       --log-file=valgrind-out.txt \

.PHONY: all, clean, fclean, re, norm, val
