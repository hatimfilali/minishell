#include "minishell.h"

int main ()
{
   
    ft_begin();
    rl_bind_key('\t', rl_complete);
    signal(SIGINT, handle_ctrl_c);

    while (1) 
        ft_start();
    clear_history();
    return 0;
}
