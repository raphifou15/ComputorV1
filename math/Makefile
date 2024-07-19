# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/02 22:44:53 by rkhelif           #+#    #+#              #
#    Updated: 2020/05/15 20:03:44 by rkhelif          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = math.a
SRC = add.c \
	sub.c \
	mul.c \
	div.c \
	squareRoot.c \
	stringIsNumber.c

OBJ = $(SRC:.c=.o)
FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

.c.o:
	$(CC) $(FLAG) -c $< -o $(<:.c=.o)

so: 
	$(CC)  -shared -o math.so $(OBJ)

clean: 
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	rm -rf math.so

re: fclean all

