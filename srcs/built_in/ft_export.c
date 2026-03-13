#include "minishell.h"

int	is_valid_env_name(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_env_node(t_env *env_list, char *key)
{
	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->key, key, ft_strlen(key)) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
// A VOIR ORDRE ALPHABETIQUE
int	print_export_list(t_env *env_list, int fd_out)
{
	t_env	*current;

	current = env_list;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(current->key, fd_out);
		if (current->value != NULL)
		{
			ft_putstr_fd("=\"", fd_out);
			ft_putstr_fd(current->value, fd_out);
			ft_putstr_fd("\"", fd_out);
		}
		ft_putstr_fd("\n", fd_out);
		current = current->next;
	}
	return (0);
}

int	builtin_export(t_args *cmd_node, t_env **env_list)
{
	int		i;
	int		exit_status;
	t_env	*existing_node;
	t_env	*new_node;
	char	**args;

	args = cmd_node->cmd->cmd;
	exit_status = 0;
	if (args[1] == NULL)
		return (print_export_list(*env_list, 1));
	i = 1;
	while (args[i] != NULL)
	{
		if (!is_valid_env_name(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status = 1;
		}
		else
		{
			new_node = create_env_node(args[i]);
			if (!new_node)
				return (1);
			existing_node = find_env_node(*env_list, new_node->key);
			if (existing_node != NULL)
			{
				if (new_node->value != NULL)
				{
					free(existing_node->value);
					existing_node->value = ft_strdup(new_node->value);
				}
				free(new_node->key);
				if (new_node->value)
					free(new_node->value);
				free(new_node);
			}
			else
			{
				env_add_back(env_list, new_node);
//				t_env	*tmp;
//				tmp = *env_list;
//				while (tmp)
//				{
//					printf("%s\n", tmp->key);
//					tmp = tmp->next;
//				}
			}
		}
		i++;
	}
	cmd_node->return_value = exit_status;
	return (exit_status);
}
