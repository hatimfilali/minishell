#include "minishell.h"

int ft_strlen (const char *str)
{
    int i = 0;
    while (str[i++]);
    return (i);
}

void cd(const char* dir)
{
    if (dir == NULL || (dir[0] == '~' && !dir[1]) || !ft_strlen(dir))
    {
        char* home_dir = getenv("HOME");
        if (home_dir == NULL)
        {
            perror("Failed to retrieve HOME environment variable.\n");
            return;
        }
        if (chdir(home_dir) != 0)
            perror("chdir");
    } 
    else
    {
        if (chdir(dir) != 0)
            perror("chdir");
    }
}