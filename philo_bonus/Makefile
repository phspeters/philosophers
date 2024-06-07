# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 19:11:03 by pehenri2          #+#    #+#              #
#    Updated: 2024/06/07 18:24:47 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME				=	philo_bonus
CC					=	cc
CFLAGS				=	-Wextra -Wall -Werror -Wunreachable-code -g3 -pthread #-fsanitize=thread
HEADERS				=	-I .
FILES				= 	main_bonus.c \
						invitations_bonus.c \
						table_bonus.c \
						philosophers_bonus.c \
						dinner_bonus.c \
						waiter_bonus.c \
						host_bonus.c \
						time_bonus.c \
						rules_bonus.c
						
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
	valgrind \
		--leak-check=full \
		--trace-children=yes \
	    --track-origins=yes \
		--show-leak-kinds=all \
		./$(NAME) 5 18000 200 200 5
#       --log-file=valgrind-out.txt \

hel: all
	valgrind \
		--tool=helgrind \
		--history-level=none \
		-s \
		./$(NAME) 5 1800 200 200 5
#       --log-file=helgrind-out.txt \

drd: all
	valgrind \
		--tool=drd \
		-s \
		./$(NAME) 5 1800 200 200 5
#       --log-file=drd-out.txt \

.PHONY: all, clean, fclean, re, norm, val, hel, drd
