# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 17:03:39 by junhhong          #+#    #+#              #
#    Updated: 2024/02/27 12:49:11 by junhhong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBDIR = libft
LIBFT = libft/libft.a
NAME = pushswap.a
AR = ar -rcs

SRC = pushswap asort stack_test stack_control

SRCOBJ = $(addsuffix .o, $(SRC))

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(SRCOBJ)
	$(AR) $(NAME) $(SRCOBJ) 

clean:
	rm -f $(SRCOBJ)

lib :
	$(MAKE) -C $(LIBDIR)/

libclean :
	$(MAKE) -C $(LIBDIR)/ clean

libfclean :
	$(MAKE) -C $(LIBDIR)/ fclean