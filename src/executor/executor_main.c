/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:51:19 by alpetukh          #+#    #+#             */
/*   Updated: 2024/04/20 09:55:10 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*handle_logical_operators(t_cmd *cmd, int exit_status)
{
	int	skip_cmd;

	if (cmd == NULL)
		return (NULL);
	skip_cmd = 0;
	while (cmd != NULL && \
			((cmd->operator == AND_OPERATOR && exit_status > 0) || \
			(cmd->operator == OR_OPERATOR && exit_status == 0)))
	{
		skip_cmd = cmd->cmd_group_len + 1;
		while (skip_cmd > 0)
		{
			if (!(skip_cmd == 1 && cmd->next != NULL && \
					cmd->next->operator == PIPE))
				skip_cmd--;
			cmd = cmd->next;
		}
	}
	return (cmd);
}

static t_bool	wait_all_children(pid_t pid, t_buffer *buffer)
{
	t_bool	is_interrupted;
	int		status;

	is_interrupted = FALSE;
	if (pid > 0)
		is_interrupted = get_last_child_status(pid, buffer);
	if (dup2(buffer->std_in, STDIN_FILENO) == -1 || \
			dup2(buffer->std_out, STDOUT_FILENO) == -1)
		clean_and_exit(FUNC_ERROR, buffer);
	while (wait(&status) != -1 || errno == EINTR)
		if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
			is_interrupted = TRUE;
	return (is_interrupted);
}

static void	executor_loop(t_buffer *buffer, t_cmd *cmd)
{
	int			pipefd[2];
	pid_t		pid;
	t_bool		is_interrupted;

	is_interrupted = FALSE;
	while (cmd != NULL && is_interrupted == FALSE)
	{
		pid = 0;
		buffer->is_pipe = is_cmd_in_pipe(cmd);
		set_input(cmd->in_lst, buffer);
		if (cmd->next != NULL && cmd->next->operator == PIPE)
		{
			pipe(pipefd);
			buffer->pipefd_in = pipefd[0];
		}
		else
			pipefd[1] = 1;
		set_output(cmd->out_lst, buffer, pipefd[1]);
		if (buffer->exit_status == 0 && cmd->arg_lst != NULL)
			pid = exec_command(cmd->arg_lst, cmd, buffer);
		if (cmd->next == NULL || cmd->next->operator != PIPE)
			is_interrupted = wait_all_children(pid, buffer);
		cmd = handle_logical_operators(cmd->next, buffer->exit_status);
	}
}

void	executor(t_buffer *buffer)
{
	resolve_heredocs(buffer);
	if (buffer->exit_status == 130)
		return ;
	define_signals(buffer, EXECUTION);
	executor_loop(buffer, buffer->cmd_list);
}
