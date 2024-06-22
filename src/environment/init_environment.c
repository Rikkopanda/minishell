/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_environment.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/13 18:27:56 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/15 19:43:14 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_env_list_len(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
			i++;
		env = env->next;
	}
	return (i);
}

void	get_envp_array(t_buffer *buffer)
{
	t_env	*env;
	int		len;

	if (buffer->envp != NULL)
		free(buffer->envp);
	env = buffer->env_list;
	len = get_env_list_len(env);
	buffer->envp = (char **)malloc((len + 1) * sizeof(char *));
	if (buffer->envp == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	buffer->envp[len--] = NULL;
	while (env != NULL)
	{
		if (env->value != NULL)
			buffer->envp[len--] = env->string;
		env = env->next;
	}
}

static void	backup_env_vars(t_buffer *buffer)
{
	t_env	*var;
	char	*key;
	char	*value;

	var = get_env(buffer->env_list, "HOME");
	if (var == NULL || var->value == NULL)
		return ;
	key = ft_strdup(var->key);
	if (key == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	value = ft_strdup(var->value);
	if (value == NULL)
	{
		free(key);
		clean_and_exit(MALLOC_ERROR, buffer);
	}
	buffer->backup_env_list = create_env(buffer, key, value);
}

static void	create_pwd(t_buffer *buffer)
{
	t_env	*env;
	char	*key;
	char	dir[PATH_MAX];

	key = ft_strdup("PWD");
	if (key == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	env = add_new_env(buffer, key, NULL, NULL);
	if (getcwd(dir, PATH_MAX) != NULL)
		set_env_value_dup(env, dir, buffer);
}

void	clone_environment(char *envp[], t_buffer *buffer)
{
	char	*key;
	char	*value;

	while (*envp != NULL)
	{
		key = NULL;
		value = NULL;
		if (get_key_value(*envp, &key, &value) == MALLOC_ERROR)
			clean_and_exit(MALLOC_ERROR, buffer);
		add_new_env(buffer, key, value, *envp);
		envp++;
	}
	if (get_env(buffer->env_list, "PWD") == NULL)
		create_pwd(buffer);
	env_shlvl_init(buffer);
	get_envp_array(buffer);
	backup_env_vars(buffer);
}
