/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 17:33:29 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/16 18:58:54 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_infile(t_lexer *lexer, t_buffer *buffer)
{
	int	fd;

	fd = open(lexer->word, O_RDONLY);
	if (fd == -1)
	{
		print_error(NOT_EXIT, lexer->word);
		return (1);
	}
	replace_std_fd(fd, STDIN_FILENO, buffer);
	return (0);
}

static int	check_infile(t_lexer *lexer)
{
	if (access(lexer->word, R_OK) == 0)
		return (0);
	print_error(NOT_EXIT, lexer->word);
	return (1);
}

void	set_input(t_lexer *lexer_in, t_buffer *buffer)
{
	buffer->exit_status = 0;
	if (lexer_in == NULL && buffer->pipefd_in > 0)
		replace_std_fd(buffer->pipefd_in, STDIN_FILENO, buffer);
	if (buffer->pipefd_in > 0)
		close(buffer->pipefd_in);
	buffer->pipefd_in = 0;
	while (lexer_in != NULL && buffer->exit_status == 0)
	{
		if (lexer_in->next == NULL)
			buffer->exit_status = open_infile(lexer_in, buffer);
		else if (lexer_in->token_type != HEREDOC)
			buffer->exit_status = check_infile(lexer_in);
		lexer_in = lexer_in->next;
	}
}

static int	open_outfile(t_lexer *lexer, t_buffer *buffer)
{
	int	fd;

	if (lexer->token_type == OUT)
		fd = open(lexer->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(lexer->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(NOT_EXIT, lexer->word);
		return (1);
	}
	if (lexer->next == NULL)
		replace_std_fd(fd, STDOUT_FILENO, buffer);
	close(fd);
	return (0);
}

void	set_output(t_lexer *lexer_out, t_buffer *buffer, int fd_out)
{
	if (buffer->exit_status != 0)
	{
		if (fd_out != 1)
			replace_std_fd(fd_out, STDOUT_FILENO, buffer);
		return ;
	}
	if (lexer_out == NULL && fd_out > 1)
		replace_std_fd(fd_out, STDOUT_FILENO, buffer);
	else if (fd_out > 1)
		close(fd_out);
	else if (lexer_out == NULL && fd_out == 1)
		if (dup2(buffer->std_out, STDOUT_FILENO) == -1)
			clean_and_exit(FUNC_ERROR, buffer);
	while (lexer_out != NULL && buffer->exit_status == 0)
	{
		buffer->exit_status = open_outfile(lexer_out, buffer);
		lexer_out = lexer_out->next;
	}
}
