NAME = philo
C_FLAGS = -Wall -Werror -Wextra
SRCS = monitor.c args.c utils.c utils_2.c utils_3.c time.c philo.c
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(C_FLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) -c $< -o $@

debug: fclean
	@cc $(C_FLAGS) -fsanitize=address -g3 $(SRCS) -o $(NAME)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
