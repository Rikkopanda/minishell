/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create_and_change.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:12:16 by alpetukh          #+#    #+#             */
/*   Updated: 2024/04/25 19:23:20 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env(t_buffer *buffer, char *key, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (new_env == NULL)
	{
		free(key);
		if (value != NULL)
			free(value);
		clean_and_exit(MALLOC_ERROR, buffer);
	}
	new_env->key = key;
	new_env->value = value;
	new_env->string = NULL;
	new_env->next = NULL;
	return (new_env);
}

t_env	*add_new_env(t_buffer *buffer, char *key, char *value, char *env_str)
{
	t_env	*new_env;

	new_env = create_env(buffer, key, value);
	new_env->next = buffer->env_list;
	buffer->env_list = new_env;
	if (value != NULL)
	{
		new_env->string = ft_strdup(env_str);
		if (new_env->string == NULL)
			clean_and_exit(MALLOC_ERROR, buffer);
	}
	return (new_env);
}

void	set_env_value_dup(t_env	*env, char *value, t_buffer *buffer)
{
	size_t	len_key;
	size_t	len_value;

	if (value == NULL)
		return ;
	env->value = ft_strdup(value);
	if (env->value == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	len_key = ft_strlen(env->key);
	len_value = ft_strlen(env->value);
	env->string = (char *)malloc(len_key + len_value + 2);
	if (env->string == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	ft_strlcpy(env->string, env->key, len_key + 1);
	env->string[len_key] = '=';
	ft_strlcpy(env->string + len_key + 1, env->value, len_value + 1);
}

static int	change_env(t_buffer *buffer, t_env *env, char *value, char *env_str)
{
	int	i;

	if (env->value != NULL)
	{
		i = get_envp_index(buffer->envp, env->string);
		free(env->value);
	}
	else
		i = -1;
	if (env->string != NULL)
		free(env->string);
	env->value = value;
	env->string = ft_strdup(env_str);
	if (env->string == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	if (i == -1)
		return (1);
	buffer->envp[i] = env->string;
	return (0);
}

int	set_env(t_buffer *buffer, char *key, char *value, char *env_str)
{
	t_env	*env;

	env = get_env(buffer->env_list, key);
	if (env == NULL)
	{
		add_new_env(buffer, key, value, env_str);
		if (value != NULL)
			return (1);
		return (0);
	}
	free(key);
	if (value == NULL)
		return (0);
	return (change_env(buffer, env, value, env_str));
}
