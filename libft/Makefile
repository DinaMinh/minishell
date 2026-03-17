NAME := libft.a

#-------------------------------------------------------------------------------
#								LIBFT

SRCS_LIBFT := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c \
	ft_atoi.c ft_tolower.c ft_toupper.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strchr.c ft_strlcpy.c ft_strlcat.c \
	ft_strlen.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
	ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strncat.c \
	ft_putchar.c ft_putnbr.c ft_atol.c ft_strcmp.c

SRCS_BONUS := ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c  \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
LIBFT_PATH := $(addprefix srcs/libft/, $(SRCS_LIBFT))

LIBFT_BONUS_PATH := $(addprefix srcs/libft/, $(SRCS_BONUS))

OBJ_LIBFT := $(LIBFT_PATH:.c=.o)

OBJ_BONUS := $(LIBFT_BONUS_PATH:.c=.o)

#-------------------------------------------------------------------------------
#								GNL

SRCS_GNL := get_next_line.c get_next_line_utils.c

GNL_PATH := $(addprefix srcs/get_next_line/, $(SRCS_GNL))

OBJ_GNL := $(GNL_PATH:.c=.o)

#-------------------------------------------------------------------------------
#								FT_PRINTF

SRCS_FT_PRINTF := ft_printf.c ft_str.c ft_numbers.c ft_pointer.c 

FT_PRINTF_PATH := $(addprefix srcs/ft_printf/, $(SRCS_FT_PRINTF))

OBJ_FT_PRINTF := $(FT_PRINTF_PATH:.c=.o)

#-------------------------------------------------------------------------------
#								COMPILATION

ALL_OBJ := $(OBJ_LIBFT) $(OBJ_BONUS) $(OBJ_GNL) $(OBJ_FT_PRINTF)

INCLUDES := ./includes/

CC := cc

CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES)

all: $(NAME) bonus

%.o: %.c
	@echo "[COMPILING] $@";$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(ALL_OBJ)
	@ar rcs $(NAME) $(ALL_OBJ)
	@echo "-------------------------------------------------"
	@echo "|	    Finished compiling libft.a ✅ 	|"
	@echo "-------------------------------------------------"

bonus: $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ_BONUS)

clean:
	@printf "[DELETING] %s\n" $(ALL_OBJ)
	@rm -f $(ALL_OBJ)

fclean: clean
	@printf "[DELETING] %s\n", $(NAME)
	@rm -f $(NAME)
	@echo "-------------------------------------------------"
	@echo "|	   Removed libft archive ✅	 	|"
	@echo "-------------------------------------------------"
re: fclean all

.SILENT: $(ALL_OBJ)
.PHONY: all bonus clean fclean re
