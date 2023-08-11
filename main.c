#include "minishell.h"

int main ()
{
    char *input;
    ft_begin();
    rl_bind_key('\t', rl_complete);
    signal(SIGINT, handle_ctrl_c);

    while (1) 
    {
        
        input = readline("minishell> ");
        
        if (input == NULL)
            break;
        if (input[0] != '\0')
        {
            add_history(input);
            char **splited = ft_split(input, ' ');
            if (ft_cmdcmp(input, "echo"))
                    echo(&splited[1]);
            else if (ft_cmdcmp(input, "cd"))
                cd (splited[1]);
            else if (ft_cmdcmp(input, "pwd"))
            {
                if (!splited[1])
                    pwd();
                else
                    printf("pwd: too manyarguments\n");
            }
            else  if (ft_cmdcmp(input, "exit")) 
            {
                free(input);
                break;
            }
            else
                if (splited[0])
                    printf("minishell: command not found: %s\n", splited[0]);
        }

        free(input);
    }
    clear_history();
    return 0;
}
