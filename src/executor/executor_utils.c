/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:43:34 by alpetukh          #+#    #+#             */
/*   Updated: 2024/08/01 12:02:12 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_std_fd(int fd, int std_fd, t_buffer *buffer)
{
	int	flag;

	flag = dup2(fd, std_fd);
	if (fd != buffer->pipefd_in)
		close(fd);
	if (flag == -1)
		clean_and_exit(FUNC_ERROR, buffer);
}

t_bool	get_last_child_status(pid_t pid, t_buffer *buffer)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		continue ;
	if (WIFEXITED(status))
		buffer->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		buffer->exit_status = 128 + WTERMSIG(status);
		if (buffer->exit_status == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (buffer->exit_status == 130)
			return (TRUE);
	}
	return (FALSE);
}

t_bool	is_cmd_in_pipe(t_cmd *cmd)
{
	if (cmd->operator == PIPE)
		return (TRUE);
	if (cmd->next != NULL && cmd->next->operator == PIPE)
		return (TRUE);
	return (FALSE);
}

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

char	*get_temp_filename(int i, t_buffer *buffer)
{
	char	*num;
	char	*filename;

	num = ft_itoa(i);
	if (num == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	filename = ft_strjoin(".heredoc_", num);
	free(num);
	if (filename == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	return (filename);
}
