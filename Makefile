NAME := minishell

SRC := main.c ft_parsing.c


SRC_DIR := ./srcs/
OBJ_DIR := ./objects/
BIN_DIR := ./bin/

ALL_SRCS := $(addprefix $(SRC_DIR), $(SRC))

LIBFT := libft/libft.a
LIBFT_DIR := libft/

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

INCLUDES := includes/

LIBFT_INCLUDES := libft/includes/

CC := cc

CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES) -I$(LIBFT_INCLUDES) -lreadline

DEBUG_FLAGS := -g

MAKEFLAGS += --no-print-directory

CREATE_OBJ_DIR := mkdir -p $(OBJ_DIR)

all: $(LIBFT) $(BIN_DIR)$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "[COMPILING] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR): 
	@echo "[CREATING OBJECT DIRECTORY]"
	@$(CREATE_OBJ_DIR)

$(BIN_DIR)$(NAME): $(OBJ)
	@echo "[DONE]"
	@echo "[COMPILING] $@ binary"
	@$(CC) $(CFLAGS) $(OBJ) -o $(BIN_DIR)$(NAME) -Llibft -lft
	@echo "-------------------------------------------------"
	@echo "|	 Finished compiling $(NAME) ✅ 		|"
	@echo "-------------------------------------------------"

debug: $(LIBFT)
	@echo "[COMPILING DEBUG] $^"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I$(INCLUDES) -o $(BIN_DIR)$(NAME) $(ALL_SRCS) -Llibft -lft

clean:
	@printf "[DELETING] Object files\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "-------------------------------------------------"
	@echo "|	   Removed all object files ✅	 	|"
	@echo "-------------------------------------------------"

fclean:
	@$(MAKE) -C ./ clean
	@printf "[Deleting] %s\n", $(NAME)
	@rm -f $(BIN_DIR)$(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "-------------------------------------------------"
	@echo "|	   Removed $(NAME) binary ✅	 	|"
	@echo "-------------------------------------------------"

re:
	$(MAKE) -C ./ fclean
	$(MAKE) -C ./ all

.PHONY: all clean fclean re
