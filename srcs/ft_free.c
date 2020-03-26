#include "minishell.h"

int	free_str(char **str, int ret)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (ret);
}

int	free_tab(char **tab, int ret)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
	return (ret);
}
