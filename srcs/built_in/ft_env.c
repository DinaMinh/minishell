#include "minishell.h"

int builtin_env(t_env *env_list, int fd_out)
{
	t_env	*current;

	current = env_list;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			ft_putstr_fd(current->key, fd_out);
			ft_putchar_fd('=', fd_out);
			ft_putstr_fd(current->value, fd_out);
			ft_putchar_fd('\n', fd_out);
		}
		current = current->next;
	}
	return (0);
}