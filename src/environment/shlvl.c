/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shlvl.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 18:50:52 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/15 19:12:51 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	atoi_shlvl(char *str)
{
	int	res;

	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (res <= 1000)
			res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (0);
	return (res);
}

static void	itoa_shlvl(int num, char *str)
{
	int		len;
	int		i;

	len = 1;
	i = num;
	while (i > 9)
	{
		len++;
		i /= 10;
	}
	i = 0;
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = num % 10 + '0';
		num /= 10;
	}
}

void	env_shlvl_init(t_buffer *buffer)
{
	t_env	*env;
	char	*key;
	int		num;
	char	str[4];

	env = get_env(buffer->env_list, "SHLVL");
	if (env == NULL)
	{
		key = ft_strdup("SHLVL");
		if (key == NULL)
			clean_and_exit(MALLOC_ERROR, buffer);
		env = add_new_env(buffer, key, NULL, NULL);
		set_env_value_dup(env, "1", buffer);
		return ;
	}
	num = atoi_shlvl(env->value) + 1;
	if (num > 999)
		num = 1;
	itoa_shlvl(num, str);
	free_env_value(env);
	set_env_value_dup(env, str, buffer);
}

void	env_shlvl_set(t_buffer *buffer, char *new_value)
{
	t_env	*env;
	int		i;

	env = get_env(buffer->env_list, "SHLVL");
	if (ft_strcmp(env->value, new_value) == 0)
		return ;
	i = get_envp_index(buffer->envp, env->string);
	free_env_value(env);
	set_env_value_dup(env, new_value, buffer);
	buffer->envp[i] = env->string;
}

void	env_shlvl_export(t_buffer *buffer, char *str)
{
	int		num;
	char	new_value[4];

	num = atoi_shlvl(str);
	if (num > 1000)
		num = 1;
	else if (num > 0)
		num -= 1;
	itoa_shlvl(num, new_value);
	env_shlvl_set(buffer, new_value);
}
