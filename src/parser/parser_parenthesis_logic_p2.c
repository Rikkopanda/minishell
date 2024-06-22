/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parenthesis_logic_p2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:15:59 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/20 10:00:29 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * 
 * copies old data into temp array
 * 
 * realloc the cmd array with space for one extra
 * copy temp array back and add new cmd.
*/
void	update_cmd_array(t_buffer *buffer, t_cmd	*cmd_cur)
{
	t_cmd	**tmp_ptr_arr;
	int		len;

	len = t_cmd_ptrs_len(buffer->group_start_cmd);
	tmp_ptr_arr = malloc(sizeof(t_cmd *) * (len + SPACE_FOR_NULL_TERM));
	if (!tmp_ptr_arr)
		clean_and_exit(MALLOC_ERROR, buffer);
	if (len != 0)
		ft_memcpy((void *)tmp_ptr_arr, (void *)buffer->group_start_cmd,
			sizeof(t_cmd *) * len);
	buffer->group_start_cmd = ft_realloc((void *)buffer->group_start_cmd,
			sizeof(t_cmd *) * (len + SPACE_FOR_NEW_CMD + SPACE_FOR_NULL_TERM));
	if (!buffer->group_start_cmd)
		clean_and_exit(MALLOC_ERROR, buffer);
	buffer->group_start_cmd[buffer->group_cmds_i
		+ SPACE_FOR_NULL_TERM] = NULL;
	if (len != 0)
	{
		init_cmd_array(len, buffer);
		ft_memcpy((void *)buffer->group_start_cmd,
			(void *)tmp_ptr_arr, sizeof(t_cmd *) * len);
		buffer->group_start_cmd[len + SPACE_FOR_NEW_CMD] = NULL;
	}
	free(tmp_ptr_arr);
	buffer->group_start_cmd[buffer->group_cmds_i] = cmd_cur;
}

/**
 * after a new cmd arises,
 * check if logic status says there is a beginning parenthesis
 * add as a newly created group
 * 
*/
void	try_add_cmd_to_ptr_array(t_cmd	*cmd_cur, t_buffer *buffer)
{
	if (buffer->cmd_group_logic_status == PARENTHESIS_BEGIN)
	{
		buffer->group_cmds_i++;
		update_cmd_array(buffer, cmd_cur);
		buffer->group_start_cmd[buffer->group_cmds_i
		]->parenthesis_status = OPEN;
		buffer->cmd_group_logic_status = NONE;
		buffer->cmd_group_temp_cnt = 0;
	}
}

int	check_group_cnts(t_buffer *buffer, t_lexer **lex_cur)
{
	int	i;

	i = 0;
	while (buffer->group_start_cmd[i] != NULL)
	{
		if (buffer->group_start_cmd[i]->parenthesis_status == OPEN)
		{
			return (set_err_and_msg(NEW_LINE, *lex_cur, buffer), SYNTAX_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	t_cmd_ptrs_len(t_cmd	**ptr_arr)
{
	int	i;

	i = 0;
	if (ptr_arr == NULL)
		return (i);
	while (ptr_arr[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	init_cmd_group_logic(t_buffer *buffer)
{
	buffer->group_start_cmd = malloc(sizeof(t_cmd *));
	if (!buffer->group_start_cmd)
		clean_and_exit(MALLOC_ERROR, buffer);
	buffer->group_start_cmd[0] = NULL;
	buffer->cmd_group_logic_status = NONE;
	buffer->group_cmds_i = -1;
	buffer->cmd_group_temp_cnt = 0;
}
