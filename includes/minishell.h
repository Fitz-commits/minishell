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
# include <signal.h>

typedef struct	s_proc
{
	pid_t	child_pid[512];
	int		curpro;
}				t_proc;

typedef struct	s_mshl
{
	t_proc	proc;
    char    *reader;
	char	*prompt; // malloc to free
	char	**args;  // malloc to free 
	char	**cenv; // malloc to free
	char	**buf_cmd; // malloc to free sans ;
	int		nb_args;
	int		nb_cpargs;
	int		ierr;
	char	**cpargs; // malloc to free < > | 
	int		cp; // current pipe to see on which pipe we are working currently and to close up to it after
	int		tpiped[512][2]; // we can open up to 1024 file descriptor
	int		begin; 
	int		progr;
	int		tstdin;
	int		tstdout;
	int		tstemp ;
	int		redir;
	int		error; 		//errno
	int		err;   		//erreur perso
	int		rvalue; // return value $?
	char	*crvalue; // malloc to free
}				t_mshl;

char			**free_tabs(char **tab);
int				free_str(char **str, int ret);
int				free_tab(char **tab, int ret, char code);
int				ft_exit(t_mshl *m, int ret);
int				ft_echo(t_mshl *m);
char			**ft_append(t_mshl *m, char *str);
int				clean_args(t_mshl *m);
//PARSING
int				set_quotes(int flag, char c);
int				check_for_exp(t_mshl *m);
int				check_for_qr(t_mshl *m);
int				fill_buffer(t_mshl *m, int i);
int				check_for_dc(char **args);
int				buffer_to_args(t_mshl *m);
//ENV
int     		until_dquotes(char *line);
int				find_env(char **env, char *key);
char			*pair_value_key(char *value, char *key);
char			*getvar(t_mshl *m, char *key);
int 			ft_export(t_mshl *m);
int				env(t_mshl *m);
char                    **ft_getenv(char **env);
//EXEC
char			*path_join(char *path, char *arg);
int				launch_exec(t_mshl *m, char *path);
//CD
int				ft_cd(t_mshl *m);
char			**parse_cli(char *line, t_mshl *m);
//UTILS
void			print_tab(char **tab);
int				tablen(char **tab);
void			display_prompt(void);
//UNSET
int				ft_unset(t_mshl *m);
//SET STD
int				set_stdouta(t_mshl *m);
int				set_stdout(t_mshl *m);
int				set_stdin(t_mshl *m);
int				set_apipes(t_mshl *m);
int				set_bpipes(t_mshl *m);
//REDIRECTION
int				clear_std(t_mshl *m);
char			**cpy_args(char **args, int beg, int end);
int				set_stdior(t_mshl *m);
int				choice_command(t_mshl *m);
int     		next_split(t_mshl *m);
int				close_reset(int fd, int nb);
//PIPES
int				zeroing_pipes(t_mshl *m);
int				close_pipes(t_mshl *m);
int				waiter(t_mshl *m);
int 			zeroing_process(t_mshl *m);
int				close_rp(t_mshl *m);
//SIGNAL
void			handler(int sign);
void			var_handler(int sign);
int				init_ptf(int (*pt_f[6])(t_mshl*));
int				n_command(t_mshl *m);
// $?
int				reat_crval(t_mshl *m, int i);
int             ft_pwd(t_mshl *m);
int             complete_env(t_mshl *m);
#endif
