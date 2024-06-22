/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:39:26 by alpetukh          #+#    #+#             */
/*   Updated: 2024/04/20 09:55:10 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static pid_t	exec_fork(t_buffer *buffer, char *command, char **cmd_args)
{
	pid_t	pid;

	pid = fork();
	if (pid <= 0 && buffer->pipefd_in > 0)
	{
		close(buffer->pipefd_in);
		buffer->pipefd_in = 0;
	}
	if (pid == 0)
	{
		buffer->is_child = TRUE;
		execve(command, cmd_args, buffer->envp);
	}
	return (pid);
}

static void	cmd_not_found_error(t_buffer *buffer, char *cmd_str)
{
	buffer->exit_status = 127;
	ft_putstr_fd(cmd_str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

static void	check_command(t_buffer *buffer, char *command, char **cmd_args)
{
	struct stat	file_info;

	if (ft_strchr(command, '/') == NULL)
		return (cmd_not_found_error(buffer, *cmd_args));
	if (stat(command, &file_info) < 0)
	{
		if (errno == EACCES)
			buffer->exit_status = 126;
		else
			buffer->exit_status = 127;
	}
	else
	{
		if (S_ISDIR(file_info.st_mode))
		{
			errno = EISDIR;
			buffer->exit_status = 126;
		}
		else if (access(command, X_OK) != 0)
			buffer->exit_status = 126;
	}
	if (buffer->exit_status != 0)
		print_error(NOT_EXIT, command);
}

pid_t	exec_command(t_lexer *lexer_arg, t_cmd *cmd, t_buffer *buffer)
{
	char	*command;
	char	**cmd_args;
	pid_t	pid;

	if (cmd->builtin != NULL)
	{
		cmd->builtin(buffer, lexer_arg->next);
		return (-1);
	}
	command = get_cmd(lexer_arg->word, buffer);
	cmd_args = get_args_array(lexer_arg);
	cmd_malloc_error_check(buffer, command, cmd_args);
	check_command(buffer, command, cmd_args);
	if (buffer->exit_status == 0)
		pid = exec_fork(buffer, command, cmd_args);
	else
		pid = 0;
	free(command);
	free(cmd_args);
	if (pid <= 0 && buffer->exit_status == 0)
		clean_and_exit(FUNC_ERROR, buffer);
	return (pid);
}
