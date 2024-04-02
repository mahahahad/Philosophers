NAME = philo
C_FLAGS = -Wall -Werror -Wextra -pthread -g3
SRCS = monitor.c args.c args_utils.c init.c init_philos.c utils.c utils_2.c utils_3.c time.c end.c philo.c
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

BGREEN = \033[1;32m
RESET = \033[0m\033[K

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(C_FLAGS) $(OBJS) -o $(NAME)
	@printf "$(BGREEN)Compiled $(NAME)!$(RESET)\n"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) -c $< -o $@

debug: fclean
	@cc $(C_FLAGS) -fsanitize=thread -g3 $(SRCS) -o $(NAME)
	@printf "$(BGREEN)Compiled $(NAME)!$(RESET)\n"

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
