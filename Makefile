NAME	= minitalk
SERVER	= server
CLIENT	= client
NAME_BONUS = minitalk_bonus
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): server.c minitalk.h
	$(CC) $(CFLAGS) -o server server.c

$(CLIENT): client.c minitalk.h
	$(CC) $(CFLAGS) -o client client.c

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): server_bonus.c minitalk.h
	$(CC) $(CFLAGS) -o server server_bonus.c

$(CLIENT_BONUS): client_bonus.c minitalk.h
	$(CC) $(CFLAGS) -o client client_bonus.c

clean:
	$(RM) $(SERVER) $(CLIENT) 

fclean: clean

re: fclean all

.PHONY: all clean fclean re