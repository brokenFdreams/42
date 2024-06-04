/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:34:02 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/31 13:34:37 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void		lenght_error(char *msg, size_t size)
{
	ft_putstr("Champion ");
	ft_putstr(msg);
	ft_putstr(" too long (Max length ");
	ft_putnbr(size);
	ft_putstr(")\n");
	exit(0);
}

void		label_error(char *msg, size_t pos)
{
	ft_putstr(msg);
	ft_putstr(" [");
	ft_putnbr(pos);
	ft_putstr("]\n");
	exit(0);
}

void		read_error(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

void		ft_error(char *msg, size_t pos, size_t i)
{
	ft_putstr(msg);
	ft_putstr(" [");
	ft_putnbr(pos + 1);
	ft_putstr("][");
	ft_putnbr(i + 1);
	ft_putstr("]\n");
	exit(0);
}
