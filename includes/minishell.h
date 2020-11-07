/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:33:12 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 19:12:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct	s_proc
{
	pid_t	child_pid[512];
	int		curpro;
}				t_proc;

typedef struct	s_mshl
{
	t_proc	proc;
	char	*reader;
	char	*prompt;
	char	**args;
	char	**cenv;
	char	*buff_cmd;
	int		curs;
	int		nb_args;
	int		nb_cpargs;
	int		ierr;
	char	**cpargs;
	int		cp;
	int		tpiped[512][2];
	int		progr;
	int		tstdin;
	int		tstdout;
	int		redir;
	int		err;
	int		rvalue;
	char	*crvalue;
	int		pos;
	char	err_to_print[PATH_MAX + 1];
}				t_mshl;

/*
** FREE
*/
char			**free_tabs(char **tab);
int				free_str(char **str, int ret);
int				free_tab(char **tab, int ret, char code);
void			free_all(t_mshl *m);
int				ft_exit(t_mshl *m, int ret);
/*
** ECHO
*/
int				ft_echo(t_mshl *m);
char			**ft_append(t_mshl *m, char *str);
int				clean_args(t_mshl *m);
/*
** PARSING
*/
int				set_quotes(int flag, char c);
int				check_for_exp(t_mshl *m);
int				check_for_qr(t_mshl *m);
int				check_for_dc(char **args);
/*
** ENV
*/
int				until_dquotes(char *line);
int				find_env(char **env, char *key);
char			*pair_value_key(char *value, char *key);
char			*getvar(t_mshl *m, char *key);
int				ft_export(t_mshl *m);
int				env(t_mshl *m);
char			**ft_getenv(char **env);
int				env_init(t_mshl *m, char **env);
/*
** EXEC
*/
char			*path_join(char *path, char *arg);
int				launch_exec(t_mshl *m, char *path);
/*
** CD
*/
int				ft_cd(t_mshl *m);
char			**parse_cli(char *line, t_mshl *m);
/*
** UTILS
*/
void			print_tab(char **tab);
int				tablen(char **tab);
void			display_prompt(void);
char			**tabdup(char **tab);
void			sort_tab(char **tab);
/*
** UNSET
*/
int				ft_unset(t_mshl *m);
/*
** SET_STDC
*/
int				set_stdouta(t_mshl *m);
int				set_stdout(t_mshl *m);
int				set_stdin(t_mshl *m);
int				set_apipes(t_mshl *m);
int				set_bpipes(t_mshl *m);
/*
** REDIRECTION
*/
int				err_redir(t_mshl *m);
int				qr_line(t_mshl *m);
int				is_redir(char *line);
int				clear_std(t_mshl *m);
int				set_stdior(t_mshl *m);
int				choice_command(t_mshl *m);
int				close_reset(int fd, int nb);
/*
** PIPES
*/
int				zeroing_pipes(t_mshl *m);
int				close_pipes(t_mshl *m);
int				waiter(t_mshl *m);
int				zeroing_process(t_mshl *m);
int				close_rp(t_mshl *m);
/*
** SIGNAL
*/
void			handler(int sign);
void			var_handler(int sign);
int				init_ptf(int (*pt_f[6])(t_mshl*));
int				n_command(t_mshl *m);
void			start_sig(void);
/*
** $?
*/
int				reat_crval(t_mshl *m, int i);
int				ft_pwd(t_mshl *m);
int				complete_env(t_mshl *m);
/*
** PERM
*/
int				check_dperm(t_mshl *m, char *path);
int				check_fperm(t_mshl *m, char *path, struct stat *test);
/*
** ERROR
*/
void			print_errno(t_mshl *m, char *str);
void			set_zpb(t_mshl *m);
int				main_error(t_mshl *m);
int				del_varenv(t_mshl *m, int j);
int				is_space(char c);
/*
** BUFF_CMD
*/
int				find_dq(char *str);
char			*copy_until_next_dq(char *src);
int				alloc_bufcmd(t_mshl *m);
int				buf_cmd_to_args(t_mshl *m);
/*
** QUOTE_REDUCTION
*/
char			*remove_quotes(char *line, int j);
int				check_quotes(char *line);
int				reset_cpargs(t_mshl *m);
/*
** FIRST_PARSING
*/
int				check_chev_o(t_mshl *m, char *str, int i);
int				check_pipe(t_mshl *m, char *str, int i);
int				check_dq(t_mshl *m, char *str, int i);
int				check_chev_f(t_mshl *m, char *str, int i);
int				check_pni_errors(t_mshl *m, char *str, int i);
/*
** ERROR
*/
int				set_err(t_mshl *m, int ret, int opt, ...);
int				size(int a);
int				init_shlvl(t_mshl *m);
int				change_pwd(t_mshl *m);
int				add_var(t_mshl *m);
int				print_warning(t_mshl *m, int nb);
int				go_home(t_mshl *m);
int				handle_error(t_mshl *m);
int				prep_rv(t_mshl *m);
void			ft_init(t_mshl *m);
int				first_parsing(t_mshl *m, char *str);
int				is_delim(char c);
int				reset_struct(t_mshl *m);
int				exp_error(t_mshl *m, int i);
#endif
