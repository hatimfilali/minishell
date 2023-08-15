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


void echo(char **arg);
int ft_strcmp(char *s1, char *s2);
int ft_cmdcmp(char *s1, char *s2);
char	**ft_split(char const *str, char c);
void cd(const char* dir);
void	pwd(void);
void	ft_begin(void);
void handle_ctrl_c(int sig) ;
void	rl_replace_line (const char *text, int clear_undo);
char **get_env(char **p);
void env(void);
void export(char *var);
void unset(char *name);
char *ft_str_append(char *str, char c);


#endif