#include "minishell.h" 
  
// Most of the C compilers support a third parameter to main which 
// store all envorinment variables 
//int main(int argc, char *argv[], char * envp[])
// makes a copy of env to work with

char	**ft_getenv(char **env)
{
	int i;
	char **ret;
	i = 0;
	while (env[i])
		i++;
	if (!(ret = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!(ret[i] = ft_strdup(env[i])))
			return (free_tabs(ret));
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
