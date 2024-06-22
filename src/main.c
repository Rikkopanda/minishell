/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 19:15:59 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/29 18:18:39 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	init_buffer(t_buffer *buffer)
{
	buffer->env_list = NULL;
	buffer->backup_env_list = NULL;
	buffer->lexer_list = NULL;
	buffer->cmd_list = NULL;
	buffer->lex_ptrs = NULL;
	buffer->err_msg = NULL;
	buffer->std_in = dup(STDIN_FILENO);
	buffer->std_out = dup(STDOUT_FILENO);
	buffer->pipefd_in = 0;
	buffer->exit_status = 0;
	buffer->exit_status_saved = 0;
	buffer->envp = NULL;
	buffer->group_start_cmd = NULL;
	buffer->is_child = FALSE;
	buffer->input_line = NULL;
	if (buffer->std_in == -1 || buffer->std_out == -1)
		clean_and_exit(FUNC_ERROR, buffer);
	ft_bzero(&buffer->ctrl_c, sizeof(buffer->ctrl_c));
	ft_bzero(&buffer->ctrl_back_slash, sizeof(buffer->ctrl_back_slash));
}

void	read_input(t_buffer *buffer)
{
	buffer->input_line = readline("minishell> ");
	if (g_signal == 130)
		buffer->exit_status_saved = g_signal;
	if (buffer->input_line == NULL)
		b_exit(buffer, NULL);
	else if (buffer->input_line[0] == '\0')
	{
		free(buffer->input_line);
		buffer->input_line = NULL;
	}
}

static void	loop(t_buffer *buffer)
{
	while (1)
	{
		g_signal = 0;
		buffer->is_pipe = FALSE;
		define_signals(buffer, INTERACTIVE);
		read_input(buffer);
		if (buffer->input_line == NULL)
			continue ;
		add_history(buffer->input_line);
		buffer->exit_status = 0;
		if (lexer(buffer->input_line, buffer) == ERROR)
			continue ;
		parser(&buffer->cmd_list, buffer->lexer_list, buffer);
		if (buffer->exit_status != SYNTAX_ERROR)
			executor(buffer);
		buffer->exit_status_saved = buffer->exit_status;
		clean_and_exit(NOT_EXIT, buffer);
	}
}
// print_lex(buffer->lexer_list);
// print_lex(buffer->lexer_list);
// print_cmd_lst(buffer->cmd_list);

int	main(int argc, char *argv[], char *envp[])
{
	t_buffer	buffer;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	init_buffer(&buffer);
	clone_environment(envp, &buffer);
	loop(&buffer);
	return (0);
}
