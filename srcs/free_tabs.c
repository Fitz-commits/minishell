#include "minishell.h"

char **free_tabs(char **tab)
{
	int i;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}
