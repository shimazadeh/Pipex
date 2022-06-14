NAME = pipex

LIBFT = ./Libft/libft.a

SRCS = main.c

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
