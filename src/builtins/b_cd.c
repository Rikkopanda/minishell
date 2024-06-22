/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:12:35 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/15 20:16:29 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_path_to_oldpwd(t_buffer *buffer, char **new_path)
{
	*new_path = get_env_value(buffer->env_list, "OLDPWD", NULL);
	if (*new_path == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		buffer->exit_status = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

static int	check_dir_path(t_buffer *buffer, char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
	}
	else if (!S_ISDIR(file_info.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (access(path, X_OK) == 0)
		return (SUCCESS);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
	}
	buffer->exit_status = 1;
	return (ERROR);
}

static void	change_env_pwds(t_buffer *buffer, char *old_path, char *new_path)
{
	t_env	*oldpwd;
	t_env	*pwd;

	oldpwd = get_env(buffer->env_list, "OLDPWD");
	pwd = get_env(buffer->env_list, "PWD");
	if (oldpwd != NULL)
	{
		free_env_value(oldpwd);
		if (pwd != NULL)
			set_env_value_dup(oldpwd, pwd->value, buffer);
		else
			set_env_value_dup(oldpwd, old_path, buffer);
	}
	if (pwd != NULL)
		free_env_value(pwd);
	if (pwd != NULL)
		set_env_value_dup(pwd, new_path, buffer);
	if (oldpwd != NULL || pwd != NULL)
		get_envp_array(buffer);
}

static char	*get_new_path(t_buffer *buffer, t_lexer *arg_lst)
{
	char	*new_path;

	if (arg_lst == NULL)
		new_path = get_home_path(buffer);
	else if (arg_lst->next != NULL)
	{
		buffer->exit_status = 1;
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (NULL);
	}
	else if (ft_strcmp(arg_lst->word, "-") == 0)
	{
		if (get_path_to_oldpwd(buffer, &new_path) == ERROR)
			return (NULL);
	}
	else
		new_path = arg_lst->word;
	if (*new_path == '\0')
		return (".");
	return (new_path);
}

void	b_cd(t_buffer *buffer, t_lexer *arg_lst)
{
	char	*new_path;
	char	old_path[PATH_MAX];
	char	cur_path[PATH_MAX];

	new_path = get_new_path(buffer, arg_lst);
	if (new_path == NULL || check_dir_path(buffer, new_path) == ERROR
		|| buffer->is_pipe == TRUE)
		return ;
	if (getcwd(old_path, PATH_MAX) == NULL)
		ft_strcpy(old_path, "");
	if (chdir(new_path) == -1)
		return (b_cd_error(buffer));
	if (arg_lst != NULL && ft_strcmp(arg_lst->word, "-") == 0)
		printf("%s\n", new_path);
	if (getcwd(cur_path, PATH_MAX) == NULL)
		return (b_cd_error(buffer));
	change_env_pwds(buffer, old_path, cur_path);
}
