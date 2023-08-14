#include "minishell.h"

void ft_exec(char *str)
{
    if (str[0] != '\0')
        {
            add_history(str);
            char **splited = ft_split(str, ' ');
            if (ft_cmdcmp(str, "echo"))
                    echo(&splited[1]);
            else if (ft_cmdcmp(str, "cd"))
                cd (splited[1]);
            else if (ft_cmdcmp(str, "pwd"))
            {
                if (!splited[1])
                    pwd();
                else
                    printf("pwd: too manyarguments\n");
            }
            else  if (ft_cmdcmp(str, "exit")) 
            {
                free(str);
                exit (0);
            }
            else
                if (splited[0])
                    printf("minishell: command not found: %s\n", splited[0]);
        }
}

void ft_start(struct termios origin, struct termios fake)
{
    char *str;
    tcsetattr(STDIN_FILENO, TCSANOW, &fake);
    signal(SIGINT, handle_ctrl_c);
    str = readline("minshell: ");
    signal(SIGQUIT, SIG_IGN);
    tcsetattr(STDIN_FILENO, TCSANOW, &origin);
    if (!str)
        exit(0);
    ft_exec(str);
    free(str);
}

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
