/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_delete_and_free.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 19:03:23 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/15 19:06:11 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_env(t_env *env)
{
	free(env->key);
	if (env->value != NULL)
		free(env->value);
	if (env->string != NULL)
		free(env->string);
	free(env);
}

void	free_env_value(t_env *env)
{
	if (env->value != NULL)
		free(env->value);
	if (env->string != NULL)
		free(env->string);
	env->value = NULL;
	env->string = NULL;
}

void	free_env_list(t_buffer *buffer)
{
	t_env	*env;

	while (buffer->env_list != NULL)
	{
		env = buffer->env_list;
		buffer->env_list = env->next;
		free_env(env);
	}
	while (buffer->backup_env_list != NULL)
	{
		env = buffer->backup_env_list;
		buffer->backup_env_list = env->next;
		free_env(env);
	}
	if (buffer->envp != NULL)
		free(buffer->envp);
}

t_bool	delete_env(t_buffer *buffer, char *key)
{
	t_env	*env;
	t_env	*prev_env;

	env = buffer->env_list;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env == buffer->env_list)
				buffer->env_list = env->next;
			else
				prev_env->next = env->next;
			free_env(env);
			return (TRUE);
		}
		prev_env = env;
		env = env->next;
	}
	return (FALSE);
}
