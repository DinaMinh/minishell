NAME := minishell

SRC := main.c ft_parsing.c ft_lexer.c ft_lexer_utils.c ft_token_utils.c \
	ft_exit.c ft_cmd.c ft_pipe.c ft_infile.c ft_outfile.c \


SRC_BUILT_IN := env_utils.c ft_env.c  ft_export.c  ft_pwd.c  ft_unset.c

SRC_DIR := ./srcs/
BUILT_IN_DIR := ./srcs/built_in/
OBJ_DIR := ./objects/
BIN_DIR := ./bin/

ALL_SRCS := $(addprefix $(SRC_DIR), $(SRC))
ALL_BUILT_IN := $(addprefix $(BUILT_IN_DIR), $(SRC_BUILT_IN))


LIBFT := libft/libft.a
LIBFT_DIR := libft/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(SRC_BUILT_IN:.c=.o))

vpath %.c $(SRC_DIR):$(BUILT_IN_DIR)

INCLUDES := includes/

LIBFT_INCLUDES := libft/includes/

CC := cc

CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES) -I$(LIBFT_INCLUDES) -lreadline

DEBUG_FLAGS := -g

MAKEFLAGS += --no-print-directory

CREATE_OBJ_DIR := mkdir -p $(OBJ_DIR)

CREATE_BIN_DIR := mkdir -p $(BIN_DIR)

all: $(LIBFT) $(BIN_DIR)$(NAME)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	@echo "[COMPILING] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR): 
	@echo "[CREATING OBJECT DIRECTORY]"
	@$(CREATE_OBJ_DIR)

$(BIN_DIR): 
	@echo "[CREATING OBJECT DIRECTORY]"
	@$(CREATE_BIN_DIR)

$(BIN_DIR)$(NAME): $(OBJ) | $(BIN_DIR)
	@echo "[COMPILING] $@ binary"
	@$(CC) $(CFLAGS) $(OBJ) -o $(BIN_DIR)$(NAME) -Llibft -lft
	@echo "-------------------------------------------------"
	@echo "|	 Finished compiling $(NAME) ✅ 		|"
	@echo "-------------------------------------------------"

debug: $(LIBFT) | $(BIN_DIR)
	@echo "[COMPILING DEBUG] $^"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I$(INCLUDES) -o $(BIN_DIR)$(NAME) $(ALL_SRCS) $(ALL_BUILT_IN) -Llibft -lft

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
	@rm -rf $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "-------------------------------------------------"
	@echo "|	   Removed $(NAME) binary ✅	 	|"
	@echo "-------------------------------------------------"

re:
	$(MAKE) -C ./ fclean
	$(MAKE) -C ./ all

.PHONY: all clean fclean re
