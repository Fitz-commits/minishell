#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"
# include "../lib/includes/get_next_line.h"
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>

# define NOT_VALID_ID 9
# define SUCCESS 0

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
	char	*buff_cmd;
	int		curs;
    char    cerr;
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
	int		errarg;
	int		rvalue; // return value $?
	char	*crvalue; // malloc to free
	int		pos;
	char	err_to_print[PATH_MAX + 1];
}				t_mshl;

//FREE
char			**free_tabs(char **tab);
int				free_str(char **str, int ret);
int				free_tab(char **tab, int ret, char code);
void			free_all(t_mshl *m);
int				ft_exit(t_mshl *m, int ret);
//ECHO
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
char			**ft_getenv(char **env);
int				env_init(t_mshl *m, char **env);
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
char			**tabdup(char **tab);
void			sort_tab(char **tab);
//UNSET
int				ft_unset(t_mshl *m);
//SET STD
int				set_stdouta(t_mshl *m);
int				set_stdout(t_mshl *m);
int				set_stdin(t_mshl *m);
int				set_apipes(t_mshl *m);
int				set_bpipes(t_mshl *m);
//REDIRECTION
int				err_redir(t_mshl *m);
int				qr_line(t_mshl *m);
int 			is_redir(char *line);
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
int				ft_pwd(t_mshl *m);
int				complete_env(t_mshl *m);
// perm
int				check_dperm(t_mshl *m, char *path);
int				check_fperm(t_mshl *m, char *path, struct stat *test);
//Error
int				ft_error(t_mshl *m);
void			print_error(t_mshl *m);
void			print_errno(t_mshl *m, char *str);
void			set_zpb(t_mshl *m);
int				main_error(t_mshl *m);
int				del_varenv(t_mshl *m, int j);
int				is_space(char c);
//new buff cmd
int				find_dq(char *str);
char			*copy_until_next_dq(char *src);
int				alloc_bufcmd(t_mshl *m);
int				buf_cmd_to_args(t_mshl *m);
//quote_reduction
char 			*remove_quotes(char *line, int j);
int				check_quotes(char *line);
int				reset_cpargs(t_mshl *m);
// first parsing
int				check_chev_o(t_mshl *m, char *str, int i);
int				check_pipe(t_mshl *m, char *str, int i);
int				check_dq(t_mshl *m, char *str, int i);
int				check_chev_f(t_mshl *m, char *str, int i);
int				check_pni_errors(t_mshl *m, char *str, int i);
//error
int				set_err(t_mshl *m, int ret, int opt, ...);
#endif
