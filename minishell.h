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
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

void	echo(char **arg);
int		ft_strcmp(char *s1, char *s2);
int		ft_cmdcmp(char *s1, char *s2);
char	**ft_split(char const *str, char c);
void	cd(const char* dir);
void	pwd(void);
void	ft_begin(void);
void	handle_ctrl_c(int sig) ;
void	rl_replace_line (const char *text, int clear_undo);
char	**get_env(char **p);
void	env(void);
void	export(char *var);
void	unset(char *name);
char	*ft_str_append(char *str, char c);
void	ft_start(struct termios origin, struct termios fake);
void	ft_exec(char *str);
void	execute_absolute_path(char *path, char **args);
void execute_command(char *command, char **args);


#endif