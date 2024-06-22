/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 19:34:50 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/26 18:38:24 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_exit_code code, char *err_msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (code == ERROR)
		ft_putstr_fd("too many arguments", 2);
	else if (err_msg != NULL)
		ft_putstr_fd(err_msg, 2);
	if (err_msg != NULL && errno != 0)
		ft_putstr_fd(": ", 2);
	if (errno != 0)
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

static void	free_cmd_list(t_buffer *buffer)
{
	t_cmd	*cmd;

	while (buffer->cmd_list != NULL)
	{
		cmd = buffer->cmd_list;
		buffer->cmd_list = cmd->next;
		free(cmd);
	}
}

static void	free_buffer_pointers(t_buffer *buffer)
{
	if (buffer->input_line != NULL)
	{
		free(buffer->input_line);
		buffer->input_line = NULL;
	}
	if (buffer->group_start_cmd != NULL)
	{
		free(buffer->group_start_cmd);
		buffer->group_start_cmd = NULL;
	}
	buffer->lexer_list = NULL;
	buffer->err_msg = NULL;
}

void	clean_and_exit(t_exit_code code, t_buffer *buffer)
{
	if (code > 0)
		print_error(code, buffer->err_msg);
	if (code != NOT_EXIT)
		free_env_list(buffer);
	free_cmd_list(buffer);
	free_lex_ptrs(buffer);
	free_buffer_pointers(buffer);
	if (buffer->std_in != -1 && code != NOT_EXIT)
		close(buffer->std_in);
	if (buffer->std_out != -1 && code != NOT_EXIT)
		close(buffer->std_out);
	if (buffer->pipefd_in > 0)
		close(buffer->pipefd_in);
	if (code != NOT_EXIT)
		rl_clear_history();
	if (code >= 0)
		exit(code);
	else if (code == EXIT_BUILTIN)
		exit(buffer->exit_status);
}
