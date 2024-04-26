# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 17:03:39 by junhhong          #+#    #+#              #
#    Updated: 2024/04/26 18:15:38 by junhhong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBDIR = libft
LIBFT = libft/libft.a
NAME = push_swap
AR = ar -rcs

SRC = pushswap stack_test stack_control organizer presort small_argc stack_movement \
		utils utils2 ft_new_atoi

all : $(NAME)

SRCOBJ = $(addsuffix .o, $(SRC))

%.o : %.c pushswap.h
	$(CC) $(CFLAGS) -c $< -o $@

# -C는 make를 어디서 실행할 지 알려주는 역할
$(NAME) : $(SRCOBJ)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(SRCOBJ) ./libft/libft.a -o $(NAME)

clean:
	rm -f $(SRCOBJ)

lib :
	$(MAKE) -C $(LIBDIR)/

libclean :
	$(MAKE) -C $(LIBDIR)/ clean

libfclean :
	$(MAKE) -C $(LIBDIR)/ fclean