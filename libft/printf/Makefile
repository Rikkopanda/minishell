SRCS =	ft_printf.c	\
		ft_print_unsigned.c	\
		ft_putnbr_base.c \
		ft_printf_utils.c \
		ft_print_hex.c \
		ft_print_ptr.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

#MAIN = testmain.c

FLAGS = -Wall -Werror -Wextra -Wno-format

LIBFTNAME = ../libft.a

RUN = run

.PHONY: all clean fclean re bonus

all: $(NAME)

#san: $(MAIN) $(NAME)
#	cc $(MAIN) $(NAME) -g -fsanitize=address -o $(RUN)

#run: $(MAIN) $(NAME)
#	cc $(MAIN) $(FLAGS) $(NAME) -o $(RUN)

$(NAME): $(LIBFT) $(OBJS)
	make -C libft/
	ar rcT  $(NAME) $(OBJS) $(LIBFTNAME)

$(OBJS): %.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME) $(RUN)
		make fclean -C libft/

re:		fclean all