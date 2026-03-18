NAME := minishell

SRC := main.c  \
	
SRC_BUILT_IN := ft_env_utils.c ft_env.c  ft_export.c  ft_pwd.c  ft_unset.c \
	ft_echo.c ft_exit.c ft_export_utils.c ft_cd.c

SRC_EXEC := ft_clean_exit.c ft_exec.c ft_exec_utils.c ft_exec_built_in.c \
	ft_print_error.c

SRC_PARSING := ft_parsing.c ft_cmd.c ft_fd.c

SRC_LEXER := ft_lexer.c ft_lexer_utils.c ft_token_utils.c ft_lexer_redir.c \
	ft_local_var.c ft_env_to_array.c

SRC_EXPAND := ft_expand.c ft_expand_utils.c

SRC_HEREDOC := ft_heredoc.c

SRC_SIGNALS := ft_signals.c

SRC_DIR := ./srcs/
BUILT_IN_DIR := $(SRC_DIR)built_in/
EXEC_DIR := $(SRC_DIR)exec/
PARSING_DIR := $(SRC_DIR)parsing/
EXPAND_DIR := $(SRC_DIR)expand/
LEXER_DIR := $(SRC_DIR)lexer/
HEREDOC_DIR := $(SRC_DIR)heredoc/
SIGNALS_DIR := $(SRC_DIR)signals/
OBJ_DIR := ./objects/
BIN_DIR := ./bin/

ALL_SRCS = $(addprefix $(SRC_DIR), $(SRC))
ALL_BUILT_IN := $(addprefix $(BUILT_IN_DIR), $(SRC_BUILT_IN))
ALL_EXEC := $(addprefix $(EXEC_DIR), $(SRC_EXEC))
ALL_PARSING := $(addprefix $(PARSING_DIR), $(SRC_PARSING))
ALL_LEXER := $(addprefix $(LEXER_DIR), $(SRC_LEXER))
ALL_EXPAND := $(addprefix $(EXPAND_DIR), $(SRC_EXPAND))
ALL_HEREDOC := $(addprefix $(EXPAND_DIR), $(SRC_HEREDOC))

ALL_SRCS += $(ALL_BUILT_IN) $(ALL_EXEC) $(ALL_PARSING) $(ALL_LEXER) $(ALL_EXPAND) $(ALL_HEREDOC)

LIBFT := libft/libft.a
LIBFT_DIR := libft/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(SRC_BUILT_IN:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(SRC_EXEC:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(SRC_PARSING:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(SRC_LEXER:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(SRC_EXPAND:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(SRC_HEREDOC:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(SRC_SIGNALS:.c=.o))

vpath %.c $(SRC_DIR):$(BUILT_IN_DIR):$(EXEC_DIR):$(PARSING_DIR):$(EXPAND_DIR):$(LEXER_DIR):$(HEREDOC_DIR):$(SIGNALS_DIR)

INCLUDES := includes/

LIBFT_INCLUDES := libft/includes/

CC := cc

CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES) -I$(LIBFT_INCLUDES)

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
	@$(CC) $(CFLAGS) $(OBJ) -o $(BIN_DIR)$(NAME) -L$(LIBFT_DIR) -lft -lreadline
	@echo "-------------------------------------------------"
	@echo "|	 Finished compiling $(NAME) ✅ 		|"
	@echo "-------------------------------------------------"

debug: $(LIBFT) | $(BIN_DIR)
	@echo "[COMPILING DEBUG] $^"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I$(INCLUDES) -o $(BIN_DIR)$(NAME) $(ALL_SRCS) -Llibft -lft -lreadline

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
