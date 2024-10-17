# Project Names
NAME_SERVER = server
NAME_CLIENT = client

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Libft Paths and Files
LIBFT_PATH = ./libft
LIBFT = ${LIBFT_PATH}/libft.a

# Source Files
SRC_SERVER = server.c
SRC_CLIENT = client.c

# Object Files
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# All Target
all: $(NAME_SERVER) $(NAME_CLIENT)
	@echo "\033[32m[ $(SRC_SERVER) and $(SRC_SERVER) are ready for use]\033[0m"

# Server Target
$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIBFT)

# Client Target
$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIBFT)

# Compile Libft
$(LIBFT):
	make -C $(LIBFT_PATH)

# Clean Target
clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	make -C $(LIBFT_PATH) clean
	@echo "\033[33m[Cleaned up]\033[0m"

# Full Clean Target
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make -C $(LIBFT_PATH) fclean
	@echo "\033[33m[Cleaned up]\033[0m"

# Rebuild Target
re: fclean all

.PHONY: all clean fclean re
