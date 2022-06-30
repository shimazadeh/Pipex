NAME = pipex

LIBFT = ./Libft/libft.a

SRCS = Pipex_Bonus.c Libft_Utils_lst.c get_next_line_utils.c get_next_line.c

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f *.o
	$(MAKE) clean -C ./Libft

fclean: clean
	rm -rf $(NAME)

re: fclean all
