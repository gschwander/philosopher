NAME	:=	philo

SRC		:=	main.c		\
			philosopher.c 	\
			atoi.c		\
			check_mutex.c 	\
			initialisation.c	\
			get_current_time.c	\
			ft_usleep.c \
			routine_philo.c \
			monitor.c 	\
			eating_utils.c	\
			clean_data.c
SRC_DIR	:=	src
BUILD	:=	.build
SRC 	:=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
DEPS 	:=	$(OBJ:.o=.d)

CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -pthread -Iinclude -g

all: create_dirs $(NAME)

create_dirs: $(BUILD)

$(BUILD):
	@if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -L/usr/local/lib -I/usr/local/include $(OBJ) -o $(NAME)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;32%sm\tCompiled: $<\033[0m\n";

clean:
	@if [ -d $(BUILD) ]; then $(RM) -rf $(BUILD) && echo "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m"; fi

fclean: clean
	@if [ -f $(NAME) ]; then $(RM) -rf $(NAME) && echo "\033[1;31m\tDeleted: $(NAME)\033[0m"; fi

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
