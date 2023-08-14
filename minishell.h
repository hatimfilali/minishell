#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>



typedef struct node
{
	int				input_file;
	char			*command;
	char			**arguments;
	int				output_file;
}					m_node;

enum				EXIT_STATUS
{
	M_SIG_INT = 78
};

enum				file_input
{
	NONE = -3,
	NO_FILE = -1,
	ERROR = -2,
};

typedef struct s_tree
{
	int				op;
	char			*content;

	struct s_tree	*left;
	struct s_tree	*right;
	struct node		*node;
}					t_tree;


typedef struct prooccess
{
	int lenght;
	int *proccess;
} t_proccess;


void echo(char **arg);
int ft_strcmp(char *s1, char *s2);
int ft_cmdcmp(char *s1, char *s2);
char	**ft_split(char const *str, char c);
void cd(const char* dir);
void	pwd(void);
void	ft_begin(void);
void handle_ctrl_c(int sig) ;
void	rl_replace_line (const char *text, int clear_undo);

#endif