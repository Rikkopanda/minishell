/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 07:59:27 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/23 08:12:12 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_FUNCTIONS_H
# define HELPER_FUNCTIONS_H

# include "../minishell.h"

typedef enum e_strpart_type		t_strpart_type;
typedef enum e_bool				t_bool;
typedef struct s_quotes_part	t_quotes_part;

void			strpart_lstadd_back(t_quotes_part **lst, t_quotes_part *new);
t_quotes_part	*strpart_lstlast(t_quotes_part *lst);
t_quotes_part	*strpart_lstnew(char *str, int quote_type, t_buffer *buffer);
int				strpart_lst_size(t_quotes_part *node);

void			free_lex_ptrs(t_buffer *buffer);
int				lex_size(t_lexer *lex_node);
int				cmd_lex_size(t_lexer *lex_node);
void			set_err_and_msg(int type, t_lexer *lex, t_buffer *buffer);

t_cmd			*cmd_lstnew(char **args, int token, t_buffer *buffer);
void			lexnode_to_redir_lst(t_lexer **redir_lst, t_lexer **lex_cur);

#endif