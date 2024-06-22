/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 18:55:37 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/16 20:01:32 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_backslash_handler(int signum)
{
	(void)signum;
	g_signal = 131;
}

static void	ctrl_c_handler(int signum)
{
	(void)signum;
	g_signal = 130;
	printf("\n");
}

static void	ctrl_c_handler_heredoc(int signum)
{
	(void)signum;
	g_signal = 130;
	printf("^C\n");
}

static void	ctrl_c_handler_inter(int signum)
{
	(void)signum;
	g_signal = 130;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	define_signals(t_buffer *buffer, t_sig_mode mode)
{
	if (mode == INTERACTIVE)
	{
		buffer->ctrl_c.sa_handler = ctrl_c_handler_inter;
		buffer->ctrl_back_slash.sa_handler = SIG_IGN;
	}
	else if (mode == HEREDOC_PARENT)
		buffer->ctrl_c.sa_handler = ctrl_c_handler_heredoc;
	else if (mode == HEREDOC_CHILD)
		buffer->ctrl_c.sa_handler = SIG_DFL;
	else if (mode == EXECUTION)
	{
		buffer->ctrl_c.sa_handler = ctrl_c_handler;
		buffer->ctrl_back_slash.sa_handler = ctrl_backslash_handler;
	}
	if (sigaction(SIGINT, &buffer->ctrl_c, NULL) == -1)
		clean_and_exit(FUNC_ERROR, buffer);
	if (sigaction(SIGQUIT, &buffer->ctrl_back_slash, NULL) == -1)
		clean_and_exit(FUNC_ERROR, buffer);
}
