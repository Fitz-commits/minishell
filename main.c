#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "mylib/includes/libft.h"
#define BUFFER_SIZE 100

int		tablen(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int		main()
{
	char	reader[100];
	char	**result;
	int		ret;
	int		t_len;
	int		option;
	int		i;

	ret = 1;
	option = 0;
	while (write(1, "minishell$> ", 12) && (ret = read(0, reader, BUFFER_SIZE)) > 0)
	{
		option = 0;
		if (reader[0] != '\0')
		{
			result = ft_split(reader, ' ');
			t_len = tablen(result);

			if (!ft_strcmp(result[0], "echo\n") || !ft_strcmp(result[0], "echo"))
			{
				if (t_len > 1)
				{
					i = (!ft_strcmp(result[1], "-n") || !ft_strcmp(result[1], "-n\n")) ? 1 : 0;
					if (i)
						option = 1;
					while (++i < t_len)
					{
						ft_putstr_fd(result[i], 1);
						if (i + 1 < t_len)
							ft_putchar_fd(' ', 1);
					}
				}
				else if (!option)
					ft_putchar_fd('\n', 1);
			}
			else if (!ft_strcmp(reader, "exit\n"))
			{
				printf("Exit\n");
				break ;
			}
		}
		ft_bzero(reader, 100);
		
	}
	return (0);
}