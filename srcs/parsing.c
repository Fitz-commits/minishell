#include "minishell.h"
int			is_space(char c)
{
	if (c == ' ')
		return 1;
	return 0;
}
int			is_delim(char c)
{
	if (c == ';' || c == '>' || c == '<' || is_space(c))
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
	if (flag == 0 && c == '"')
		return (2);
	if (flag == 0 && c == '\'')
		return (1);
	if (flag == 1 && (c == '\'' || c == '"'))
		return (0);
	return (0);
}

int			count_arg(char *line)
{
	int flag;
	int i;
	int j;

	flag = 0;
	i = 0;
	j = 1;
	while (line[i])
	{
		if (line[i] == '\\' && flag != 1 && line[i + 1])
			i += 2;
		if (line[i] == '"' || line[i] == '\'')
			flag = set_quotes(flag, line[i]);
		if (!flag && is_delim(line[i]))
			{
				j += 1;
				while (is_space(line[i]))
					i++;
			}
		i += 1;
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
char		**parse_cli(char *line)
{
	int i;
	int j;
	int flag;
	int k;
	char **ret;

	if (!(ret = malloc(sizeof(char*) * (count_arg(line) + 1))))
		return (NULL);
	flag = 0;
	j = 0;
	i = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (is_delim(line[i]))
			if(!(ret[j++] = ft_strndup(&line[i++], 1)))
				return (NULL);
		k = 0;
		while (line[k + i] && !(!flag && is_delim(line[k + i])))
		{
			if (line[k + i] == '\\' && flag != 1 && line[k + i + 1])
				{
					k += 2;
					continue;
				}
			if (line[i + k] == '"' || line[i + k] == '\'')
				flag = set_quotes(flag, line[i + k]);
			k++;
		}
		if (k != 0)
			if (!(ret[j++] = ft_strndup(&line[i], k)))
				return (NULL);
		i += k;
	}
	ret[j] = 0;
	return (ret);
}
