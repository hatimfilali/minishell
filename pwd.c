#include "minishell.h"

void	pwd(void)
{
	char	*current_dir;

	current_dir = NULL;
	current_dir = getcwd(NULL, 0);
	printf("%s\n", current_dir);
	free(current_dir);
	// exit(0);
}