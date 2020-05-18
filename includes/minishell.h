#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"
# include "../lib/includes/get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
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
int				free_tab(char **tab, int ret, char code);
int				ft_exit(t_mshl *m, int ret);
int				tablen(char **tab);
int				ft_echo(t_mshl *m);
char			**ft_append(char **tab, char *str);
char			**ft_splitq(char *s, char c);
//PARSING
int				set_quotes(int flag, char c);
int				check_for_exp(t_mshl *m);
int				check_for_qr(t_mshl *m);
//ENV
int     		until_dquotes(char *line);
int				find_env(char **env, char *key);
char			*pair_value_key(char *value, char *key);
char    		*getvar(char **env, char *key);
int 			ft_export(t_mshl *m);
int				env(t_mshl *m);
char                    **ft_getenv(char **env);
//EXEC
char			*path_join(char *path, char *arg);
int				launch_exec(t_mshl *m, char *path);
//CD
int				ft_cd(t_mshl *m);
char			**parse_cli(char *line);
void			print_tab(char **tab);
//UNSET
int				ft_unset(t_mshl *m);
//REDIRECTION
char			*put_stdin(char *path);
#endif
