#include "minishell.h"

void	ft_begin(void)
{
	printf("\e[1;1H\e[2J\n");
	printf("\n");
    printf(" *****     *****  ***  *****     ***  ***       *****     *****  ***  *****     ***  ***\n");
    printf(" *** **   ** ***  ***  *** **    ***  ***       *****     *****  ***  *****     ***  ***\n");
    printf(" ***  ** **  ***  ***  ***  **   ***  ***       ***  ** **  ***  ***  ***  **   ***  ***\n");
    printf(" ***   ***   ***  ***  ***   **  ***  ***       ***   ***   ***  ***  ***   **  ***  ***\n");
    printf(" ***    *    ***  ***  ***    ** ***  ***       ***    *    ***  ***  ***    ** ***  ***\n");
    printf(" ***         ***  ***  ***     *****  ***       ***         ***  ***  ***     *****  ***\n");
    printf(" ***         ***  ***  ***      ****  ***       ***         ***  ***  ***      ****  ***\n");
    printf( "\n");
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

void rubnbilt(char **splited)
{
    if (ft_cmdcmp(splited[0], "echo"))
                    echo(&splited[1]);
            else if (ft_cmdcmp(splited[0], "cd"))
                cd (splited[1]);
            else if (ft_cmdcmp(splited[0], "pwd"))
            {
                if (!splited[1])
                    pwd();
                else
                    printf("pwd: too manyarguments\n");
            }
            else  if (ft_cmdcmp(splited[0], "exit")) 
            {
                // free(splited[1]);
                exit (0);
            }
            else if (ft_cmdcmp(splited[0], "env"))
            {
                env();
            }
            else if (ft_cmdcmp(splited[0], "export"))
            {
                export(splited);
            }
            else if (ft_cmdcmp(splited[0], "unset"))
            {
                unset(splited[1]);
            }
            
}

void ft_exec(char *str)
{
    if (str[0] != '\0')
        {
            add_history(str);
            char **splited = ft_split(str, ' ');
            if (ft_cmdcmp(splited[0], "unset") || ft_cmdcmp(splited[0], "export") \
                    || ft_cmdcmp(splited[0], "env") || ft_cmdcmp(splited[0], "exit") \
                    || ft_cmdcmp(splited[0], "pwd") || ft_cmdcmp(splited[0], "cd"))
            {
                rubnbilt(splited);
            }
            else if (splited[0] && strchr(splited[0], '/') != NULL)
                execute_absolute_path(splited[0], splited);
            else
                if (splited[0])
                    execute_command(splited[0], splited);
        }
}