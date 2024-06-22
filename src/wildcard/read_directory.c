/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:05:40 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/22 21:14:29 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	read_all_content(t_read_dir_ptrs *p)
{
	char	*new_str;

	p->dir_stream = opendir(p->current_dir_of_process);
	p->dir_data = readdir(p->dir_stream);
	while (p->dir_data)
	{
		if (!(p->pattern->type != HIDDEN_FILES
				&& p->dir_data->d_name[0] == '.')
			|| (p->pattern->type == HIDDEN_FILES
				&& p->dir_data->d_name[0] == '.'))
		{
			new_str = ft_strdup(p->dir_data->d_name);
			if (!new_str)
				clean_and_exit(MALLOC_ERROR, p->buffer);
			strpart_lstadd_back(p->content_list,
				strpart_lstnew(new_str, 0, p->buffer));
		}
		p->dir_data = readdir(p->dir_stream);
	}
	closedir(p->dir_stream);
}

void	read_dir_assign_ptrs(t_read_dir_ptrs *p, t_quotes_part	**content_list,
	t_asterix_pattern	*pattern, t_buffer *buffer)
{
	p->content_list = content_list;
	p->pattern = pattern;
	p->buffer = buffer;
}

/**
 * read content of current directory and store it in linkedlist
 * sort list in alphabetical order
*/
void	read_current_directory_into_list(t_quotes_part	**content_list,
	t_buffer *buffer, t_asterix_pattern	*pattern)
{
	t_read_dir_ptrs	p;

	read_dir_assign_ptrs(&p, content_list, pattern, buffer);
	p.current_dir_of_process = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!p.current_dir_of_process)
		clean_and_exit(MALLOC_ERROR, buffer);
	getcwd(p.current_dir_of_process, PATH_MAX);
	if (!p.current_dir_of_process)
		clean_and_exit(FUNC_ERROR, buffer);
	read_all_content(&p);
	sort_linked_list_alphabetical(content_list,
		0, 0, linked_list_size(*content_list));
	free(p.current_dir_of_process);
}
