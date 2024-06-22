/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:13:22 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/26 11:51:06 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "../minishell.h"

typedef struct s_lexer				t_lexer;
typedef struct s_command			t_cmd;
typedef struct s_buffer				t_buffer;
typedef struct s_quotes_part		t_quotes_part;

void	print_cmd_lst(t_cmd	*cmd_lst);
void	print_lex(t_lexer	*lex_lst);
void	print_lex_ptrs(t_lexer **lex_arr);
void	check_cmd_position(t_cmd **cmd_current, t_buffer *buffer);
void	print_strparts(t_quotes_part *cur_strpart);

#endif