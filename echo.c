#include "minishell.h"

int ft_cmdcmp(char *s1, char *s2)
{
   int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (!s2[i])
        return 1;
    return 0;
}

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (!s1[i] && !s2[i])
        return 1;
    return 0;
}

void echo(char **arg)
{
    int i = 0;
    int j = 0;
    int new_line = 0;

    if (!*arg)
    {
        printf("\n");
        return;
    }
    while (arg[i][0] == '-')
    {
        new_line =1;
        j=1;
        while (arg[i][j] == 'n')
            j++;
        if (arg[i][j])
        {
            break;
        }
        i++;
        if (!arg[i])
            break;
    }
    while (arg[i])
    {
        printf("%s", arg[i]);
        i++;
        if (arg[i] != NULL)
            printf(" ");
        else 
            break;
    }
    if (!new_line)
        printf("\n");
    // exit(0);
}
