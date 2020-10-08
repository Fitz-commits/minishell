#include "minishell.h"
int			is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
		return 1;
	return 0;
}

int			is_delim(char c)
{
	if (c == ';' || c == '>' || c == '<' || c == '|' || is_space(c))
		return (1);
	return (0);
}
/*
** flag == 1 -> '
** flag == 2 -> "
** flag == 0 -> unquoted
*/
int			set_quotes(int flag, char c)
{
	if (flag == 2 && c == '\\')
		return (5);
	if (flag == 5)
		return (2);
	if (flag == 0 && c == '"')
		return (2);
	if (flag == 0 && c == '\'')
		return (1);
	if (flag == 1 && c == '\'')
		return (0);
	if (flag == 2 && c == '"')
		return (0);
	if (flag == 0 && c == '\\')
		return(3);
	if (flag == 3)
		return 0;
	return (flag);
}

int			count_arg(char *line)
{
	int flag;
	int i;
	int j;
	int k;

	flag = 0;
	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		k = 0;
		while (is_space(line[i]))
			i++;
		if (is_delim(line[i]))
		{
			j++;
			i++;
		}
		while (line[k + i] && !(!(flag) && is_delim(line[k + i])))
				flag = set_quotes(flag, line[k++ + i]);
		if (k != 0)
			j ++;
		i += k;
	}
	return(j);
}
/*
**	need to differiencate between a delimiter and a space because the intaraction are not the same
**	we need to split on an unquoted unescaped space and not keep it 
**	and we need to split on an unquoted unescaped delimiter and keep it in a separate tab entry
**
**	things to do now : the line seems to be splitted accordingly now i need to perform shell expansions and manage redirections
**	Considering the different options :
**	| use the output of a commant as stdin of another command
**	> redirect the standard output of a command
**	< redirect the standard input of a command
**
**
*/
char *alloc_sep(char c, int *i)
{
	char *ret;
	if (!(ret = malloc(sizeof(char) * 2)))
		return NULL;
	ret[0] = c;
	ret[1] = 0;
	(*i) += 1;
	return ret;
}

int		triming(char **line, char ***ret, int *flag, int *j)
{
	int k;
	char *nline;
	char **nret;
	int i;

	i = 0;
	nret = *ret;
	nline = *line;
	while (nline[i])
	{
		k = 0;
		while(is_space(nline[i]))
			i += 1;
		if (is_delim(nline[i]))
			if (!(nret[(*j)++] = alloc_sep(nline[i], &i)))
				return (EXIT_FAILURE);
		while (nline[k + i] && !(!(*flag) && is_delim(nline[k + i])))
				*flag = set_quotes(*flag, nline[k++ + i]);
		if (k != 0)
			if (!(nret[(*j)++] = ft_strndup(&nline[i], k)))
				return (EXIT_FAILURE);
		i += k;
	}
	return (EXIT_SUCCESS);
}

char		**parse_cli(char *line, t_mshl *m)
{
	int j;
	int flag;
	char **ret;

	if (!(ret = malloc(sizeof(char*) * (count_arg(line) + 1))))
		return (NULL);
	flag = 0;
	j = 0;
	if ((triming(&line, &ret, &flag, &j) == EXIT_FAILURE))
	{
		free_tab(ret, 0, 1);
		return (NULL);
	}
	ret[j] = 0;
	if (flag != 0 && (m->err = 2))
		return (free_tabs(ret)); // can catch " or ' isolation
	return (ret);
}
