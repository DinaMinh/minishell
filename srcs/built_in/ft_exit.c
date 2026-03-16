#include "minishell.h"

static int	is_numeric_argument(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_env *env_list, int last_status)
{
	int exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	(void)env_list;
	if (args[1] == NULL)
	{
		//free_tout(env_list);
		exit(last_status);
	}
	if (!is_numeric_argument(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		//free_tout(env_list);
		exit(255);
	}
	if (args[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	//free_tout(env_list);
	exit(exit_code % 256); 
}
