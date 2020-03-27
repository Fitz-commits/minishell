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
	char	**cenv;
	int		nb_args;
}				t_mshl;
char				**free_tabs(char **tab);
int				free_str(char **str, int ret);
int				free_tab(char **tab, int ret);
int				ft_exit(t_mshl *m, int ret);
int				tablen(char **tab);
int				ft_echo(t_mshl *m);
char			**ft_append(char **tab, char *str);
char			**ft_splitq(char *s, char c);
//ENV
int     		until_dquotes(char *line);
int			find_env(char **env, char *key);
char			*pair_value_key(char *value, char *key);
char    		*getvar(char **env, char *key);
char 			**export(t_mshl *m, char *key, char *value);
void			env(t_mshl *m);
char                    **ft_getenv(char **env);
#endif
