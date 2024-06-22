/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:15:55 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/04/15 20:19:51 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	b_cd_error(t_buffer *buffer)
{
	buffer->exit_status = 1;
	perror("cd");
}

void	b_exit_error(t_buffer *buffer, char *arg_str)
{
	buffer->exit_status = 2;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg_str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	atoi_exit_code(const char *str)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	res = res % 256;
	if (sign == -1 && res > 0)
		res = 256 - res;
	return (res);
}

t_bool	is_n_option(char *str)
{
	if (ft_strncmp(str, "-n", 2) != 0)
		return (FALSE);
	str += 2;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (TRUE);
	return (FALSE);
}
