#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"
# include "../lib/includes/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_mshl
{
	char	*prompt;
	char	**args;  	//Tab contenant les arguments splites
	int		nb_args;
}				t_mshl;

int				free_str(char **str, int ret);
int				free_tab(char **tab, int ret);
int				ft_exit(t_mshl *m, int ret);
int				tablen(char **tab);
int				ft_echo(t_mshl *m);
#endif