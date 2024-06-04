/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:59:40 by fsinged           #+#    #+#             */
/*   Updated: 2019/12/28 18:14:37 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	chk_num_of_args(t_command *cmnd, char *cmd)
{
	if (ft_strequ(cmd, LIVE) || ft_strequ(cmd, ZJMP) ||
		ft_strequ(cmd, FFORK) || ft_strequ(cmd, LFORK))
		return (cmnd->arg1 ? 1 : 0);
	else if (ft_strequ(cmd, LD) || ft_strequ(cmd, ST) ||
			 ft_strequ(cmd, LLD))
		return (cmnd->arg1 && cmnd->arg2 ? 1 : 0);
	return (cmnd->arg1 && cmnd->arg2 && cmnd->arg3 ? 1 : 0);
}

/*
** Return the size of argument
*/

static int	size_of_arg(char *data)
{
	int	size;

	size = 0;
	while (data[size] != SEPARATOR_CHAR && !(is_space(data[size])) &&
		data[size] != '\0' && data[size] != COMMENT_CHAR &&
		data[size] != ';')
		size++;
	if (is_space(data[size]) && data[size + skip_space(data, size)] == '-')
	{
		size += skip_space(data, size);
		if (data[size] == '-')
			while (data[size] && data[size] != SEPARATOR_CHAR &&
			!(is_space(data[size]) && ft_isdigit(data[size])))
				size++;
	}
	if (size == 0)
		return (-1);
	return (size);
}

static int	read_argument(char *data, t_command *cmnd, size_t i, size_t a)
{
	size_t	size;

	if ((size = size_of_arg(data + i)) == -1)
		return (-1);
	if (a == 1)
		cmnd->arg1 = ft_strncpy(ft_strnew(size), data + i, size);
	else if (a == 2)
		cmnd->arg2 = ft_strncpy(ft_strnew(size), data + i, size);
	else if (a == 3)
		cmnd->arg3 = ft_strncpy(ft_strnew(size), data + i, size);
	return (i + skip_space(data, i + size) + size);
}

/*
** Reading arguments
*/

int			read_arguments(char *data, t_command *cmnd)
{
	size_t	i;
	size_t	arg;
	int		tmp;

	i = 0;
	arg = 0;
	if (!(is_space(data[i])) && data[i] != DIRECT_CHAR)
		return (i);
	i = skip_space(data, i);
	while (++arg <= 3)
	{
		if ((tmp = read_argument(data, cmnd, i, arg)) == -1)
			return (i);
		i = skip_space(data, tmp) + tmp;
		if (data[i] != SEPARATOR_CHAR)
			break ;
		i += skip_space(data, i + 1) + 1;
	}
	if (!(tmp != -1 && (data[i] == '\0' || data[i] == ';' ||
		data[i] == COMMENT_CHAR) && chk_arguments(cmnd) &&
		  chk_num_of_args(cmnd, cmnd->cmnd)))
		return (i);
	return (-1);
}
