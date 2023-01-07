GARB = garbe/*.c
TOKENIZER = token.c tokenize_var.c tokenize_quotes.c token_tools.c
MAIN = minishell.c
TOOLS = tools.c
SIGNALS = signals.c
EXPANDER = expander.c
PARCER = parcer.c parce_tools.c parce_redirections.c
EXECUTOR = exec.c pipe.c
ENVIRONEMENT = env.c
BUILTINS = ft_echo.c ft_cd.c ft_env.c ft_unset.c
TEST = test.c
LEXER = lexer.c
PROMPT = prompt.c quotes_calibration.c
TMP = tmp_list_tools.c
INCDIR += -I /Users/beadam/.brew/opt/readline/include/ -L /Users/beadam/.brew/opt/readline/lib
FILES = $(GARB) $(LEXER)  $(TOKENIZER) $(BUILTINS) $(PARCER) $(EXECUTOR) $(TOOLS) $(SIGNALS) $(EXPANDER) $(ENVIRONEMENT) $(TEST) $(PROMPT) $(TMP)

LIBS = libft.a
CFLAGS := -Wall -Wextra -Werror

all:
	gcc $(MAIN) $(FILES) $(INCDIR)  $(LIBS) $(CFLAGS) -o minishell -lreadline
	./minishell