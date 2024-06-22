/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_others.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 18:26:39 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/15 20:38:30 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	b_echo(t_buffer *buffer, t_lexer *arg_lst)
{
	t_bool	n_option;

	(void)buffer;
	n_option = FALSE;
	while (arg_lst != NULL && is_n_option(arg_lst->word) == TRUE)
	{
		n_option = TRUE;
		arg_lst = arg_lst->next;
	}
	while (arg_lst != NULL)
	{
		printf("%s", arg_lst->word);
		arg_lst = arg_lst->next;
		if (arg_lst != NULL)
			printf(" ");
	}
	if (n_option == FALSE)
		printf("\n");
}

void	b_env(t_buffer *buffer, t_lexer *arg_lst)
{
	char	**line;

	(void)arg_lst;
	line = buffer->envp;
	while (*line != NULL)
		printf("%s\n", *line++);
}

void	b_exit(t_buffer *buffer, t_lexer *arg_lst)
{
	if (buffer->is_pipe == FALSE)
		ft_putstr_fd("exit\n", 2);
	if (arg_lst == NULL)
	{
		buffer->exit_status = buffer->exit_status_saved;
		if (buffer->is_pipe == FALSE)
			clean_and_exit(EXIT_BUILTIN, buffer);
		return ;
	}
	buffer->exit_status = atoi_exit_code(arg_lst->word);
	if (buffer->exit_status == -1)
		b_exit_error(buffer, arg_lst->word);
	else if (arg_lst->next != NULL)
	{
		buffer->exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	if (buffer->is_pipe == FALSE)
		clean_and_exit(EXIT_BUILTIN, buffer);
}

void	b_pwd(t_buffer *buffer, t_lexer *arg_lst)
{
	char	cwd[PATH_MAX];

	(void)buffer;
	(void)arg_lst;
	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("pwd");
		buffer->exit_status = 1;
	}
}

void	b_unset(t_buffer *buffer, t_lexer *arg_lst)
{
	int	res;

	if (buffer->is_pipe == TRUE)
		return ;
	res = 0;
	while (arg_lst != NULL && arg_lst->word != NULL)
	{
		if (ft_strcmp(arg_lst->word, "SHLVL") == 0)
			env_shlvl_set(buffer, "0");
		else
			res += delete_env(buffer, arg_lst->word);
		arg_lst = arg_lst->next;
	}
	if (res > 0)
		get_envp_array(buffer);
}
