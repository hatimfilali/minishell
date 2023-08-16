#include "minishell.h"

int main ()
{
    struct termios	origin;
	struct termios	fake;

	tcgetattr(0, &origin);
	tcgetattr(0, &fake);
    ft_begin();
    rl_bind_key('\t', rl_complete);
    signal(SIGINT, handle_ctrl_c);

    while (1) 
        ft_start(origin, fake);
    clear_history();
    return 0;
}
