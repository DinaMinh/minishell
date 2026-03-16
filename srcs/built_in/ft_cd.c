#include "minishell.h"

void	update_env(t_env **env_list, char *key, char *value)
{
	t_env	*node;

	node = find_env_node(*env_list, key);
	if (node != NULL)
	{
		if (node->value != NULL)
			free(node->value);
		if (value != NULL)
			node->value = ft_strdup(value);
		else
			node->value = NULL;
	}
	else
		add_env_node(env_list, key, value);
}

int	builtin_cd(char **args, t_env **env)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!args[1])
		return (0);
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(args[1]) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	if (old_pwd)
	{
		update_env(env, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env(env, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}
