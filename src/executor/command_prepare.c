/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:39:06 by alpetukh          #+#    #+#             */
/*   Updated: 2024/04/20 09:55:10 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*create_path(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc(len1 + len2 + 2);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, len1 + 1);
	new_str[len1] = '/';
	ft_strlcpy(new_str + len1 + 1, s2, len2 + 1);
	return (new_str);
}

char	*get_cmd(char *cmd, t_buffer *buffer)
{
	char		*command;
	char		**paths;
	int			i;
	struct stat	file_info;

	if (ft_strchr(cmd, '/') != NULL || *cmd == '\0'
		|| ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "..") == 0)
		return (ft_strdup(cmd));
	paths = ft_split(get_env_value(buffer->env_list, "PATH", ""), ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		command = create_path(paths[i++], cmd);
		if (command == NULL || (stat(command, &file_info) == 0
				&& S_ISREG(file_info.st_mode) && access(command, X_OK) == 0))
		{
			free_array(paths);
			return (command);
		}
		free(command);
	}
	free_array(paths);
	return (ft_strdup(cmd));
}

static int	get_lexer_list_len(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer != NULL)
	{
		i++;
		lexer = lexer->next;
	}
	return (i);
}

char	**get_args_array(t_lexer *lexer)
{
	char	**cmd_args;
	int		len;
	int		i;

	len = get_lexer_list_len(lexer);
	cmd_args = (char **)malloc((len + 1) * sizeof(char *));
	if (cmd_args == NULL)
		return (NULL);
	cmd_args[len] = NULL;
	i = 0;
	while (lexer != NULL)
	{
		cmd_args[i++] = lexer->word;
		lexer = lexer->next;
	}
	return (cmd_args);
}

void	cmd_malloc_error_check(t_buffer *buffer, char *cmd, char **cmd_args)
{
	if (cmd != NULL && cmd_args != NULL)
		return ;
	if (cmd != NULL)
		free(cmd);
	if (cmd_args != NULL)
		free(cmd_args);
	clean_and_exit(MALLOC_ERROR, buffer);
}
