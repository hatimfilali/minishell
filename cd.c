#include "minishell.h"

void cd(const char* dir)
{
    if (dir == NULL)
    {
    // If no argument is provided, get the home directory and change to it
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
        // If an argument is provided, change to the specified directory
        if (chdir(dir) != 0)
            perror("chdir");
    }
    // Get the current working directory and display it
    // char cwd[1024];
    // if (getcwd(cwd, sizeof(cwd)) != NULL) {
    //     printf("Current directory: %s\n", cwd);
    // } else {
    //     perror("getcwd");
    // }
}
