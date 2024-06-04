/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:35:45 by fsinged           #+#    #+#             */
/*   Updated: 2019/12/28 13:43:14 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check is argument t_reg or not
** if t_reg return 1 else return 0
*/

int			is_treg(char *arg)
{
	size_t i;

	i = 1;
	if (arg[0] == 'r' && arg[i] && ft_isdigit(arg[i]))
		while (arg[i] && ft_isdigit(arg[i]))
			i++;
	else
		return (0);
	if (arg[i] == '\0')
		return (1);
	return (0);
}

/*
** Check is argument t_ind or not
** if t_ind return 1 else return 0
*/

int			is_tind(char *arg)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	if (arg[i] == LABEL_CHAR)
	{
		i = is_labelchars(arg + 1) + 1;
		if (i == 1)
			return (1);
		flag = 1;
		i += skip_space(arg, i);
	}
	if (arg[i] && arg[i] == '-')
		i++;
	else if (flag)
		return (0);
	if (!(arg[i] && ft_isdigit(arg[i])))
		return (0);
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	return (arg[i] == '\0');
}

/*
** Check is argument t_dir or not
** if t_dir return 1 else return 0
*/

int			is_tdir(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] != DIRECT_CHAR)
		return (0);
	if (arg[++i] == LABEL_CHAR)
		return (is_labelchars(arg + 2) == 0);
	if (arg[i] == '-')
		i++;
	else if (arg[i] == '0' && arg[i + 1] == 'x')
		i += 2;
	if (!(arg[i] && ft_isdigit(arg[i])))
		return (0);
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	return (arg[i] == '\0');
}

/*
** Checking can this argument be with this cmnd
** flag show the number of argument
*/

static int	chk_argument(char *arg, char *cmnd, int flag)
{
	if (!(!(flag == 1 && (ft_strequ(cmnd, ST) || ft_strequ(cmnd, STI) ||
		ft_strequ(cmnd, AFF))) &&
		!(flag == 2 && (ft_strequ(cmnd, LD) || ft_strequ(cmnd, LLD))) &&
		!(flag == 3 && (ft_strequ(cmnd, AND) || ft_strequ(cmnd, OR) ||
		ft_strequ(cmnd, XOR) || ft_strequ(cmnd, LDI) ||
		ft_strequ(cmnd, LLDI))) &&
		!(flag >= 1 && flag <= 3 && (ft_strequ(cmnd, ADD) ||
		ft_strequ(cmnd, SUB)))))
		return (is_treg(arg));
	if (flag == 1 && (ft_strequ(cmnd, LIVE) || ft_strequ(cmnd, FFORK) ||
		ft_strequ(cmnd, LFORK) || ft_strequ(cmnd, ZJMP)))
		return (is_tdir(arg));
	if (flag == 1 && (ft_strequ(cmnd, LD) || ft_strequ(cmnd, LLD)))
		return (is_tdir(arg) || is_tind(arg));
	if (flag == 2 && ft_strequ(cmnd, ST))
		return (is_treg(arg) || is_tind(arg));
	if (!(!(flag == 2 && (ft_strequ(cmnd, LDI) || ft_strequ(cmnd, LLDI))) &&
		!(flag == 3 && ft_strequ(cmnd, STI))))
		return (is_treg(arg) || is_tdir(arg));
	if (!(!(flag == 1 && (ft_strequ(cmnd, LDI) || ft_strequ(cmnd, LLDI))) &&
		!(flag == 2 && (ft_strequ(cmnd, STI))) &&
		!(flag >= 1 && flag <= 2 && (ft_strequ(cmnd, AND) ||
		ft_strequ(cmnd, OR) || ft_strequ(cmnd, XOR)))))
		return (is_tdir(arg) || is_treg(arg) || is_tind(arg));
	return (0);
}

int			chk_arguments(t_command *cmnd)
{
	if (cmnd->arg1 && cmnd->arg2 && cmnd->arg3)
		return (chk_argument(cmnd->arg1, cmnd->cmnd, 1) &&
				chk_argument(cmnd->arg2, cmnd->cmnd, 2) &&
				chk_argument(cmnd->arg3, cmnd->cmnd, 3));
	else if (cmnd->arg1 && cmnd->arg2)
		return (chk_argument(cmnd->arg1, cmnd->cmnd, 1) &&
				chk_argument(cmnd->arg2, cmnd->cmnd, 2));
	else if (cmnd->arg1)
		return (chk_argument(cmnd->arg1, cmnd->cmnd, 1));
	return (0);
}
