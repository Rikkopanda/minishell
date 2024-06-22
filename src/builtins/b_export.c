/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_export.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:09:21 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/15 20:16:09 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	check_export_key(char *str)
{
	if (ft_isalpha(*str) == 0 && *str != '_')
		return (FALSE);
	str++;
	while (*str != '=' && *str != '\0')
	{
		if (ft_isalnum(*str) == 0 && *str != '_')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	b_export_print(t_buffer *buffer)
{
	t_env	*env;

	env = buffer->env_list;
	while (env != NULL)
	{
		if (env->value != NULL)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

static void	b_export_error(t_buffer *buffer, char *arg)
{
	buffer->exit_status = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	b_export_env(t_buffer *buffer, char *env_str)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (ft_strncmp(env_str, "SHLVL=", 6) == 0)
	{
		env_shlvl_export(buffer, env_str + 6);
		return (0);
	}
	if (get_key_value(env_str, &key, &value) == MALLOC_ERROR)
		clean_and_exit(MALLOC_ERROR, buffer);
	return (set_env(buffer, key, value, env_str));
}

void	b_export(t_buffer *buffer, t_lexer *arg_lst)
{
	int		new_envs;

	if (arg_lst == NULL)
		return (b_export_print(buffer));
	new_envs = 0;
	while (arg_lst != NULL)
	{
		if (check_export_key(arg_lst->word) == FALSE)
			b_export_error(buffer, arg_lst->word);
		else if (buffer->is_pipe == FALSE)
			new_envs += b_export_env(buffer, arg_lst->word);
		arg_lst = arg_lst->next;
	}
	if (new_envs > 0)
		get_envp_array(buffer);
}
