#include "minishell.h"

void handle_ctrl_c(int sig) 
{
    printf("\n"); // New line after the ^C (SIGINT) message
    rl_on_new_line();
    rl_redisplay(); // Redisplay the prompt
    printf("minishell> ");
    fflush(stdout);}