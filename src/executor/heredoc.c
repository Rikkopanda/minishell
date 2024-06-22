/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:15:49 by alpetukh          #+#    #+#             */
/*   Updated: 2024/04/21 14:35:05 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_tempfile(char *filename, t_buffer *buffer)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(filename);
		clean_and_exit(TEMPFILE_ERROR, buffer);
	}
	return (fd);
}

static void	open_heredoc(t_lexer *lexer_hd, t_buffer *buffer, char *filename)
{
	char	*input;
	int		fd;

	fd = -1;
	if (lexer_hd->next == NULL)
		fd = open_tempfile(filename, buffer);
	free(filename);
	input = readline("> ");
	while (input != NULL && ft_strcmp(input, lexer_hd->word) != 0)
	{
		if (fd != -1)
			ft_putendl_fd(input, fd);
		free(input);
		input = readline("> ");
	}
	if (fd != -1)
		close(fd);
	if (input == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document ", 2);
		ft_putstr_fd("delimited by end-of-file\n", 2);
	}
	else
		free(input);
	clean_and_exit(SUCCESS, buffer);
}

static void	heredoc_parent(t_lexer *lexer_hd, t_buffer *buffer, pid_t pid, \
	char *filename)
{
	get_last_child_status(pid, buffer);
	if (lexer_hd->next == NULL
		&& (buffer->exit_status == 0 || buffer->exit_status == 130))
	{
		free(lexer_hd->word);
		lexer_hd->word = filename;
		lexer_hd->token_type = HEREDOC_RESOLVED;
	}
	else
		free(filename);
}

static void	heredoc_fork(t_lexer *lexer_hd, t_buffer *buffer, int i)
{
	pid_t	pid;
	char	*filename;

	filename = get_temp_filename(i, buffer);
	pid = fork();
	if (pid < 0)
	{
		free(filename);
		clean_and_exit(FUNC_ERROR, buffer);
	}
	else if (pid == 0)
	{
		buffer->is_child = TRUE;
		define_signals(buffer, HEREDOC_CHILD);
		open_heredoc(lexer_hd, buffer, filename);
	}
	else
		heredoc_parent(lexer_hd, buffer, pid, filename);
}

void	resolve_heredocs(t_buffer *buffer)
{
	t_cmd		*cmd;
	t_lexer		*lexer_in;
	int			i;

	cmd = buffer->cmd_list;
	i = 1;
	define_signals(buffer, HEREDOC_PARENT);
	buffer->exit_status = 0;
	while (cmd != NULL)
	{
		lexer_in = cmd->in_lst;
		while (lexer_in != NULL)
		{
			if (lexer_in->token_type == HEREDOC)
				heredoc_fork(lexer_in, buffer, i++);
			if (buffer->exit_status == 130)
				return ;
			else if (buffer->exit_status > 0)
				clean_and_exit(buffer->exit_status, buffer);
			lexer_in = lexer_in->next;
		}
		cmd = cmd->next;
	}
}
