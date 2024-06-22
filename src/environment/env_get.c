/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_get.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 19:20:18 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/15 19:23:14 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env(t_env *env_lst, char *key)
{
	t_env	*env;

	env = env_lst;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env_lst, char *key, char *default_str)
{
	t_env	*env;

	env = get_env(env_lst, key);
	if (env == NULL || env->value == NULL)
		return (default_str);
	return (env->value);
}

int	get_envp_index(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strcmp(envp[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	get_key_value(char *env_str, char **key, char **value)
{
	char	*sep;

	sep = ft_strchr(env_str, '=');
	if (sep == NULL || sep == env_str)
		*key = ft_strdup(env_str);
	else
		*key = ft_substr(env_str, 0, sep - env_str);
	if (*key == NULL)
		return (MALLOC_ERROR);
	if (sep == NULL || sep == env_str)
		return (SUCCESS);
	*value = ft_strdup(sep + 1);
	if (*value != NULL)
		return (SUCCESS);
	free(*key);
	return (MALLOC_ERROR);
}

char	*get_home_path(t_buffer *buffer)
{
	char	*new_path;

	new_path = get_env_value(buffer->env_list, "HOME", NULL);
	if (new_path == NULL)
		new_path = get_env_value(buffer->backup_env_list, "HOME", "");
	return (new_path);
}
