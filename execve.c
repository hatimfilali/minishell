#include "minishell.h"

void execute_absolute_path(char *path, char **args) 
{
    pid_t pid = fork();
    extern char **environ;
    if (pid == 0) 
    {
        execve(path, args, environ);
        perror("execve"); 
        exit(EXIT_FAILURE);
    } 
    else if (pid < 0) 
    {
        perror("fork");
    } 
    else 
    {
        
        int status;
        waitpid(pid, &status, 0);
    }
}

int find_command(char *command, char *full_path) 
{
    int i = 0;
    // Get the PATH environment variable
    char *path = getenv("PATH");
    if (path == NULL) 
    {
        return 0; // PATH variable not found
    }

    // Split the PATH into individual directories
    char **dir = ft_split(path, ':');
    while (dir && dir[i]) 
    {
        // Construct the full path to the executable
        snprintf(full_path, PATH_MAX, "%s/%s", dir[i], command);

        // Check if the file is executable
        if (access(full_path, X_OK) == 0) 
        {
            return 1; // Executable found
        }
        i++;
    }

    return 3; // Executable not found
}

void execute_command(char *command, char **args) {
    char full_path[PATH_MAX];

    if (find_command(command, full_path)==1) 
    {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            execv(full_path, args);
            perror("execv"); // Execv failed
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork"); // Fork failed
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    } 
    else 
        printf("minishell: command not found\n");
    
}
