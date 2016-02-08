# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwoodwar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 16:35:07 by gwoodwar          #+#    #+#              #
#    Updated: 2016/02/08 21:56:24 by gwoodwar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	clang
FLAGS =	-Wall -Werror -Wextra -g
NAME =	ft_ls
LIB =	libft/libftprintf.a
HEAD =	ft_ls.h

SRCS =	ls_lst_dir.c \
		ls_fetch_lst.c \
		ls_clear_lst.c \
		ls_parse.c \
		ls_error.c \
		print_struct.c \
		ls_stat_file.c \
		ls_stat_size.c \
		ls_tools.c \
		ls_cmp.c \
		ls_col_disp.c \
		ls_mode_file.c \
		ls_first_sort.c \
		main.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(LIB):
	make -C libft/ fclean
	make -C libft/

$(NAME): $(LIB) $(OBJS)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIB)

%.o: %.c
	$(CC) $(FLAGS) -I $(HEAD) -o $@ -c $<

clean:
	make -C libft/ clean
	@/bin/rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	@/bin/rm -f $(NAME)

re: fclean all
