#include "minishell.h"

int	free_str(char **str, int ret)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (ret);
}

/*
**	if the code is 0 just free the pointer of the tab
**	else if the code is 1 the function free ALL the tab
*/

int	free_tab(char **tab, int ret, char code)
{
	int i;

	i = 0;
	if (tab)
	{
		if (code)
		{
			while (tab[i])
			{
				free(tab[i]);
				i++;
			}
		}
		free(tab);
	}
	tab = NULL;
	return (ret);
}
