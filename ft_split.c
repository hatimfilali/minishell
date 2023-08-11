#include "minishell.h"

static int	str_len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	words_count(char const *str, char c)
{
	int	i;
	int	j;

	j = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		i = str_len(str, c);
		str += i;
		if (i)
			j++;
	}
	return (j);
}

static char	*fill_str(char const *src, int n)
{
	char	*dest;

	dest = (char *)malloc((n + 1) * sizeof(char));
	if (!dest)
		return (0);
	dest[n] = '\0';
	while (n--)
		dest[n] = src[n];
	return (dest);
}

static char	**free_it(char **biggy, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(biggy[i++]);
	free(biggy);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	char	**biggy;
	size_t	size;
	size_t	i;
	size_t	n;

	if (!str)
		return (0);
	size = words_count(str, c);
	biggy = (char **)malloc((size + 1) * sizeof(char *));
	if (!biggy)
		return (0);
	i = -1;
	while (++i < size)
	{
		while (*str && *str == c)
			str++;
		n = str_len(str, c);
		if (*str)
			biggy[i] = fill_str(str, n);
		if (!biggy[i])
			return (free_it(biggy, i));
		str += n;
	}
	biggy[size] = 0;
	return (biggy);
}