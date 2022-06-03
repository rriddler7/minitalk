NAME = client server
FLAGS = -Wall -Wextra -Werror
HEADER = ./minitalk.h
HEADER_B = ./minitalk_bonus.h
FILE_C = client.c utils.c
FILE_S = server.c
BONUS_FILE_C = client_bonus.c utils_bonus.c
BONUS_FILE_S = server_bonus.c

all: $(NAME)

$(NAME): $(FILE_C) $(FILE_S) $(HEADER) Makefile
		gcc $(FLAGS) $(FILE_C) -I./ -o client
		gcc $(FLAGS) $(FILE_S) -I./ -o server
bonus: fclean $(BONUS_FILE_C) $(BONUS_FILE_S) $(HEADER_B) Makefile
		gcc $(FLAGS) $(BONUS_FILE_C) -I./ -o client
		gcc $(FLAGS) $(BONUS_FILE_S) -I./ -o server

clean:
		rm -f *.o

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
