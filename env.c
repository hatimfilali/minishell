#include "minishell.h"



char	*ft_strnstr(char *str, char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str && n == 0)
		return (NULL);
	if (!needle[j])
		return (str);
	while (str[i] && i < n)
	{	
		if (str[i] == needle[j])
		{
			while (needle[j] && i + j < n)
			{
				if (needle[j] != str[i + j])
					break ;
				j++;
			}
			if (needle[j] == '\0')
				return (str + i);
		}
		i++;
		j = 0;
	}
	return (NULL);
}

int size(char **str)
{
    int i = 0;
    if (!str)
        return 0;
    while (str[i])
        i++;
    return i;
}

char	**get_env(char **p)
{
	static char	**env;
	int			i;

	i = 0;
	if (p != NULL)
	{
		env = malloc((size(p) + 1) * sizeof(char *));
		while (p[i])
		{
			env[i] = strdup(p[i]);
			i++;
		}
		env[i] = NULL;
	}
    else 
    {
        extern char **environ;
        env = environ;
    }
	return (env);
}

void env(void)
{
    extern char **environ; // External array containing environment variables
    char **env = environ;
    while ( *env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}

char *ft_str_append(char *str, char c)
{
    int i = 0 ;
    if (!str)
    {
        str = malloc(2);
        str[0] = c;
        str[1] = 0;
    }
    else 
    {
        while (str[i++]);
        str = realloc(str, i + 2);
        strcat(str, &c);
        return str;
    }
}

void remove_var(char **env, int index)
{
    int i;
    int j;
    char **new_env;

    i = 0;
    j = 0;
    new_env = malloc(sizeof(char *) * (size(env)));
    while (env[i])
    {
        if (i != index)
            new_env[j++] = strdup(env[i]);
            i++;
    }
    new_env[j] = NULL;
    get_env(new_env);
    // free(p);
    // free(new_env);
}

void add_var(char *value)
{
    int		i;
	char	**new_env;
	char	**env;

	i = 0;
	env = get_env(NULL);
	new_env = malloc(sizeof(char *) * (size(env) + 2));
	while (env[i])
	{
		new_env[i] = strdup(env[i]);
		i++;
	}
	new_env[i++] = strdup(value);
	new_env[i] = NULL;
	get_env(new_env);
	// free(p);
	// free(new_env);
}

void unset(char *name)
{
    int i = 0;
    char **env;
    char *value;

    env =get_env(NULL);
    while (env[i])
    {
        value  = ft_strnstr(env[i], name , strlen(name));
        if (value)
            return (remove_var(env, i));
        i++;
    }
}

void export(char *var)
{
    int i = 0;
    char *name = NULL;
    char *value =NULL;

    if (!var)
        return;
    while (var[i] && var[i]!= '=')
        name = ft_str_append(name, var[i++]);
    if (var[i] == '=')
        i++;
    while (var[i])
        value = ft_str_append(value, var[i++]);
    if(!name || !value)
        return;
    unset(name);
    add_var(var);
}