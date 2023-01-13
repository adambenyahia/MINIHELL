/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:03 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 06:05:51 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "garbe/garb.h"
# include "libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "readline/history.h"
# include "readline/readline.h"

typedef enum tokens
{
	PIPE,
	OUTRED,
	APPEND,
	INRED,
	HERDOC,
	SQ,
	DQ,
	VAR,
	WORD,
	SP,
	CMD,
}						t_tokens_flag;

typedef enum quote_exit
{
	INITQ,
	SINGLE,
	DOUBLE,
	BAD = 4,
	EPI = 8,
}						t_quote_flag;

typedef struct s_global
{
	t_garb				*g_garb;
	int					quotes;
	int					exit_status;
	int					runing;
}						t_global;

extern t_global			g_spot;

/// edit this shit for GOD's love
typedef struct s_io
{
	int					in;
	int					out;
}						t_io_fd;

typedef struct s_cmdlist
{
	char				*cmd;
	struct s_cmdlist	*next;
}						t_cmdlist;

typedef struct s_tokens
{
	char				*token;
	int					flag;
	struct s_tokens		*next;
	struct s_tokens		*previous;
	struct s_tokens		*tail;
}						t_tokens;

typedef struct s_tree
{
	int					type;
	t_cmdlist			*cmdlist;
	size_t				cmdlen;
	t_io_fd				file;
	int					err;
	struct s_tree		*right;
	struct s_tree		*left;
}						t_tree;

typedef struct s_key_value
{
	char				*key;
	char				*value;
	struct s_key_value	*next;
}						t_key_value;

typedef struct s_env
{
	struct s_key_value	*head;
	struct s_key_value	*tail;
	char				**tab;
	size_t				size;
}						t_env;

typedef struct s_key
{
	char				*key;
	char				*value;
	struct s_key_value	*next;
}						t_key;

/////////////////TOKENIZER TOOLS\\\\\\\\\\\\\\\\\\\\

/// @brief check if a string is composed of spaces only
/// @param input string to check
/// @return 1 if spaces_only || 0 if not
int						spaces_only(char *input);

/// @brief check if the input is a special token
/// @param c input char
/// @return 0 if is yes | 1 if not
bool					if_token(char c);

/// @brief add input to token list with flag specifier
/// @param list pointer to the head of list
/// @param input token string
/// @param len lenght of token string
/// @param flag token's type (see t_token_flag)
/// @return len
int						set_token(t_tokens **list, char *input, int len,
							int flag);

/// @brief add input to token list as long as it's not a special token
/// @param list pointer to the head of the list
/// @param input token string
/// @return length of the word (to skip)
int						set_word_token(t_tokens **list, char *input);

/// @brief get new node for single quote
/// @param head pointer to tokens list
/// @param input pointer to the singel quote
/// @return length of parsed characters (to skip)
int						get_single_quote(t_tokens **head, char *input);

/// @brief get new node fordouble quote
/// @param head pointer to tokens list
/// @param input pointerto the double quote
/// @return length of parced characters (to skip)
int						get_double_quote(t_tokens **head, char *input);

/// @brief get new node for variable
/// @param head pointer to tokens list
/// @param input pointer to the '$' sign
/// @return lenght of parces characters (to skip)
int						tokenize_variables(t_tokens **head, char *input);

/// @brief check if c ain't a special token
/// @param c char to check
/// @return 1 if {'alnum', '_', '?'} || 0 if else
bool					isword(int c);

/// @brief delete a node from t_token list
/// @param tokens pointer to the head of the list
/// @param node pointer to the node to delete
/// @return deleted node
t_tokens				*shift_node(t_tokens **tokens, t_tokens *node);

/// @brief combine words and remove spaces
/// @param head pointer to the list
void					combine_words(t_tokens **head);

/////////////////SYNTAX ANALIZER\\\\\\\\\\\\\\\\\\\


/// @brief display quote prompt till it's balanced
/// @param head pointer to tokens list
/// @return error code
int						quotes_syntax(t_tokens **head);

////////////////////EXPANDER\\\\\\\\\\\\\\\\\\\\\\\\

/// @brief expand VAR tokens
/// @param env env list
/// @param head pointer to tokens
void					expand(t_env *env, t_tokens **head);

/////////////////PARCER without a V\\\\\\\\\\\\\\\\\\\\

/// @brief open redirected files
/// @param io in/out file descriptor struct
/// @param def default file descriptor
/// @param token pointer to tokens list;
/// @return error code if it exist
int						set_fd(int *io, int def, t_tokens **token);

/// @brief parce herdoc token;
/// @param head pointer to tokens list
/// @param io in/out file descriptor struct
/// @return error code if it exists

int						heredoc(t_tokens **head, int *io);

/// @brief add cmd to back of cmd list;
/// @param head pointer to t_cmdlist
/// @param cmd cmd string
/// @param cmdlen count of inserted cmds
/// @return error code if it exists(joke, no need)
int						cmd_addback(t_cmdlist **head, char *cmd,
							size_t *cmdlen);

/// @brief assemble set_fd, heredoc, anc cmd_addback functions
/// @param token pointer to t_lokens list
/// @param io in?out file descriptor struct
/// @param list pointer to cmd_list
/// @param cmdlen count of inserted cmds
/// @return error code if it exists (m not joking now u'll need it)
int						cmd_lister(t_tokens **token, t_io_fd *io,
							t_cmdlist **list, size_t *cmdlen);

/// @brief extention to commander...
void					init_variables(int *v, t_io_fd *io, t_cmdlist **cmdlist,
							size_t *cmdlen);

/// @brief parce to T_CMD type (while no PIPE exists)
/// @param token pointer to t_tokens list
/// @return T_TREE node with cmd parced
t_tree					*commander(t_tokens **token);

/// @brief crete t_tree node
/// @param type node type
/// @param io io file discriptors
/// @param left pointer to the left tree node
/// @param right pointer to the right tree node
/// @return chajara
t_tree					*plant_tree(int type, t_io_fd *io, t_tree *left,
							t_tree *right);

/// @brief connect trees
/// @param chajara pointer to the tree root
/// @param cmd pointer to t_cmdlist
/// @param cmdlen cmd lenght
/// @param err error number
/// @return chajara
t_tree					*water_tree(t_tree *chajara, t_cmdlist *cmd,
							size_t cmdlen, int err);

/// @brief when you start begging ur code to work(extention)
/// @param head pointer to t_tokens list
/// @return parced final t_tree (ready to execute)
t_tree					*parce_please(t_tokens **head);

/////////////////EXECUTOR\\\\\\\\\\\\\\\\\\\\

/// @brief convert t_cmd type to double array
/// @param node parce tree node
/// @return pointer to cmds array
char					**cmdstring(t_tree *node);

/// @brief execute t_tree node
/// @param cmd pointer to t_tree node
/// @param env pointer to t_env list
void					exec(t_tree *cmd, t_env **env);

void					piper(t_tree *cmd, t_env **env);

void					exec_cmd(t_tree *cmd, t_env **env);

char					*cmd_path(char *cmd, t_env *env);

/////////////////SIGNAL HANDLERS\\\\\\\\\\\\\\\\\\\\

/// @brief handel sig int
/// @param sig returned by signal function
void					sig_int(int sig);

/// @brief signals handler
void					sig_handler(void);

////////////////////BUILT_INS\\\\\\\\\\\\\\\\\\\\\\\\

/// @brief echo cmd implementation with -n flag
/// @param cmd cmd array
/// @param fd out file discriptor
void					ft_echo(char **cmd, int fd);

/// @brief change directory cmd implementation
/// @param cmd cmd array
/// @param env pointer to t_env list
void					ft_cd(char **cmd, t_env *env);

/// @brief printf env variables
/// @param cmd cmd array
/// @param env pointer to t_env list
/// @param fd out FileDescriptor
void					ft_env(char **cmd, t_env *env, int fd);

/// @brief unset env variable
/// @param cmd cmd array
/// @param env pointer to t_env
void					ft_unset(char **cmd, t_env **env);

/// @brief export env variable
/// @param cmd cmd array
/// @param env pointer to t_env
void					ft_export(char **cmd, t_env **env);

/// @brief clear garb and exit;
void					ft_exit(char **cmd);

/// @brief print working directory
/// @param cmd cmd array
/// @param fd out file discriptor
void					pwd_cmd(char **cmd, int fd);

/////////////////ENVIREMENT TOOLS\\\\\\\\\\\\\\\\\\\\

/// @brief get string table lenght
/// @param c pointer to string table
size_t					string_table_len(char **c);

/// @brief convert env double array to t_env linked list
/// @param env env string table
/// @return pointer to the head of the list
t_env					*init_env(char **env);

/// @brief convert env array to key_value node (malloc used)
/// @param c env array
/// @param previous pointer to the previous node
/// @return (t_key_value node);
t_key_value				*key_retreave(char *c);

/// @brief find env value
/// @param key env key
/// @param env t_env list
/// @return value corresponding to key
char					*find_env(char *key, t_env *env);

/// @brief remove a variable from the list
/// @param tf variable name
/// @param env pointer to t_env list
void					remove_env(char *tf, t_env **env);

/////////////////TESTING TOOLS\\\\\\\\\\\\\\\\\\\\

/// @brief display token linked list content
/// @param token_list tokens list
void					token_list_test(t_tokens *token_list);

/// @brief display env_list content
/// @param env_list env_list
void					env_list_test(t_env *env_list);

/// @brief display double pointer array
/// @param str pointer to the array
void					display_cmd_string(char **str);

/////////////////TOOLS\\\\\\\\\\\\\\\\\\\\

/// @brief tokenize the input cmd
/// @param head pointer to the list
/// @param line cmd line
void					ft_token(t_tokens **head, char *line);

t_key_value				*ft_create_node(char **args);

char					**ft_split_export(char *cmd, int pos, int size);

void					ft_append_var(char **args, t_env **env);

void					ft_add_var(char **args, t_env **env);

t_key_value				*find_env2(char *key, t_env *env);

/// @brief display prompt / tokenize cmd line
/// @return (pointer to tokens list);
t_tokens				*prompt(void);

///////////////TMP\\\\\\\\\\\\\\/
// t_tokens				*node_del_dll(t_tokens **dll, t_tokens *node);
int						ft_isspace(int c);
#endif