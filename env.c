#include "minishell.h"



int	fill_int(long nbr, int i, char *n, int neg)
{
	while (n[i] <= '9' && n[i] >= '0')
	{
		nbr = nbr * 10 + (n[i] - 48);
		if (((nbr * neg) > 2147483647) || ((nbr * neg) < -2147483648))
			{
                printf("minishell: exit: %s: numeric argument required", n);
                return (2);
            }
		i++;
	}
	if (n[i] != ' ' && n[i] != '\t' && n[i] != '\r'
		&& n[i] != '\n' && n[i] != '\v' && n[i] != '\f' && n[i])
	{
		printf("minishell: exit: %s: numeric argument required", n);
        return (2);
	}
	if (neg == -1)
		return (-nbr);
	return (nbr);
}

int	ftt_atoi(char	*n)
{
	int					i;
	int					neg;
	unsigned long long	nbr;

	nbr = 0;
	i = 0;
	neg = 1;
	while (n[i] == ' ' || n[i] == '\t' || n[i] == '\r'
		|| n[i] == '\n' || n[i] == '\v' || n[i] == '\f')
		i++;
	if (n[i] == '-' || n[i] == '+')
	{
		if (n[i] == '-')
			neg = -1;
		i++;
	}
	return (fill_int(nbr, i, n, neg));
}

void ft_exit(char *status)
{
    int s;
    printf("exit\n");
    if (!status)
        exit (0);
    s = ftt_atoi(status);
    exit(s);
}

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
    extern char **environ;
	i = 0;
    if (!env)
        env  = environ;
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
	return (env);
}

void env(void)
{
    char **env = get_env(NULL);
    while ( *env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}

void ft_strncpy(char *dest, char *src, int n)
{
    int i= 0;
    while (i <= n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
}

char *ft_str_append(char *str, char c)
{
    int i = 0 ;
    char *s;
    if (!str)
    {
        s = malloc(2);
        s[0] = c;
        s[1] = 0;
    }
    else 
    {
        
        while (str[i++]);
        s = malloc(sizeof(char) * i + 1);
        
        ft_strncpy(s, str, i+1);
        s[i-1] = c;
        s[i] = 0;
    }
    return s;
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

int ft_strcmpare(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i]==s2[i])
        i++;
    return (int)(s1[i] - s2[i]);
}

void sort_env(char **env)
{
    char **envi = env;
    char *tmp;
    int i = 0;
    int j;
    // while (env[i])
    // {
    //     ft_strncpy(envi[i], env[i], strlen(env[i]));
    //     i++;
    // }
    // envi[i] = 0;
    // i = 0;
    while (env[i])
    {
        j = i + 1;
        while (env[j])
        {
            if (ft_strcmpare(env[i], env[j]) > 0)
            {
                tmp = envi[i];
                envi[i] = envi[j];
                envi[j] = tmp;
                break;
            }
            j++;
        }
        if(!envi[j])
            i++;
    }
    // return (envi);
}

void test_export(void)
{
    char **env = get_env(NULL);
    sort_env(env);
    while (*env)
    {
        printf("declare -x %s\n", *env);
        env++;
    }
}

void export(char **var)
{
    int j = 0;
    int i = 0;
    char *name = NULL;
    char *value =NULL;

    if (!var[++j])
    {
        test_export();
        return;
    }
    while (var[j][i] && var[j][i]!= '=')
        name = ft_str_append(name, var[j][i++]);
    if (var[j][i] == '=')
        i++;
    while (var[j][i])
        value = ft_str_append(value, var[j][i++]);
    if(!name || !value)
        return;
    unset(name);
    add_var(var[j]);
}