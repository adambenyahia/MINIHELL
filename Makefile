NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = env.c export++.c ft_env.c \
		lexer.c parcer.c tmp_list_tools.c\
		tokenize_var.c exec.c extra_tokens.c \
		ft_exit.c minishell.c pipe.c token.c \
		tools.c exec2.c ft_cd.c ft_export.c \
		parce_redirections.c prompt.c token_tools.c \
		expander.c ft_echo.c ft_unset.c parce_tools.c \
		signals.c tokenize_quotes.c garbe/point.c

LIB = libft/libft.a 

HEADERS = minishell.h garbe/garb.h

OBJ = $(SRC:%.c=%.o)

RFLAGS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

INC = -I/Users/$(USER)/.brew/opt/readline/include

all : $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(RFLAGS)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

clean :
	make clean -C libft
	rm -rf $(OBJ)

fclean : clean
	make fclean -C libft
	rm -rf $(NAME)
	
re : fclean all