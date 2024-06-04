/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:35:29 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/12 12:16:13 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_valid(char c)
{
	return (is_space(c) || c == DIRECT_CHAR);
}

static int	is_small_cmnd(char *str)
{
	return (!(!(ft_strnequ(str, LD, ft_strlen(LD)) &&
	is_valid(str[ft_strlen(LD)])) &&
	!(ft_strnequ(str, ST, ft_strlen(ST)) && is_valid(str[ft_strlen(ST)])) &&
	!(ft_strnequ(str, OR, ft_strlen(OR)) && is_valid(str[ft_strlen(OR)]))));
}

static int	is_medium_cmnd(char *str)
{
	return (!(
	!(ft_strnequ(str, ADD, ft_strlen(ADD)) && is_valid(str[ft_strlen(ADD)])) &&
	!(ft_strnequ(str, SUB, ft_strlen(SUB)) && is_valid(str[ft_strlen(SUB)])) &&
	!(ft_strnequ(str, AND, ft_strlen(AND)) && is_valid(str[ft_strlen(AND)])) &&
	!(ft_strnequ(str, XOR, ft_strlen(XOR)) && is_valid(str[ft_strlen(XOR)])) &&
	!(ft_strnequ(str, LDI, ft_strlen(LDI)) && is_valid(str[ft_strlen(LDI)])) &&
	!(ft_strnequ(str, STI, ft_strlen(STI)) && is_valid(str[ft_strlen(STI)])) &&
	!(ft_strnequ(str, LLD, ft_strlen(LLD)) && is_valid(str[ft_strlen(LLD)])) &&
	!(ft_strnequ(str, AFF, ft_strlen(AFF)) && is_valid(str[ft_strlen(AFF)]))));
}

/*
** Check is it command or not
*/

int			is_command(char *str)
{
	if (!(!(ft_strnequ(str, LIVE, ft_strlen(LIVE)) &&
	is_valid(str[ft_strlen(LIVE)])) &&
	!(ft_strnequ(str, ZJMP, ft_strlen(ZJMP)) &&
	is_valid(str[ft_strlen(ZJMP)])) &&
	!(ft_strnequ(str, FFORK, ft_strlen(FFORK)) &&
	is_valid(str[ft_strlen(FFORK)])) &&
	!(ft_strnequ(str, LLDI, ft_strlen(LLDI)) &&
	is_valid(str[ft_strlen(LLDI)]))))
		return (4);
	else if (!(!(ft_strnequ(str, LFORK, ft_strlen(LFORK)) &&
			is_valid(str[ft_strlen(LFORK)]))))
		return (5);
	else if (is_small_cmnd(str))
		return (2);
	else if (is_medium_cmnd(str))
		return (3);
	return (0);
}
