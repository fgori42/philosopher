# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgori <fgori@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 14:38:53 by fgori             #+#    #+#              #
#    Updated: 2024/05/17 10:36:09 by fgori            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

file = utils.c\
		philosopher.c\
		lst_utils.c\
		ft_atoi.c\
		error.c\
		create.c\
		check_utils.c
cc = cc

Cflag =  -Wall -Wextra -Werror -pthread

NAME = philo

object = $(file:.c=.o)

all: $(NAME)

$(NAME): $(object)
	$(cc) $(Cflag) $(object) -g -o $(NAME) 

%.o : %.c
	$(cc) $(Cflag) -c $< -o $@
clean:
	rm -f $(object)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re bonus