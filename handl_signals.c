#include "minishell.h"

void handle_ctrl_c(int sig) 
{
   (void)sig;
	write(0, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}