/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:14:21 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/21 16:14:26 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	codeargtypes(char *arg, int tdirsize, char *bytes)
{
	if (arg && is_tdir(arg))
	{
		bytes = ft_strcat(bytes, "10");
		return (tdirsize ? 4 : 2);
	}
	if (arg && is_treg(arg))
	{
		bytes = ft_strcat(bytes, "01");
		return (1);
	}
	if (arg && is_tind(arg))
	{
		bytes = ft_strcat(bytes, "11");
		return (2);
	}
	bytes = ft_strcat(bytes, "00");
	return (0);
}

static void		codeargstypes(t_command *cmnd, int tdirsize)
{
	char	*bytes;

	if ((bytes = ft_strnew(8)) == NULL)
		read_error("Malloc error");
	cmnd->size += codeargtypes(cmnd->arg1, tdirsize, bytes);
	cmnd->size += codeargtypes(cmnd->arg2, tdirsize, bytes);
	cmnd->size += codeargtypes(cmnd->arg3, tdirsize, bytes);
	codeargtypes(NULL, tdirsize, bytes);
	cmnd->argsize = ft_atoi_base(bytes, 2);
	ft_strdel(&bytes);
}

int				tdir_size(char *cmnd)
{
	return (ft_strequ(cmnd, LIVE) || ft_strequ(cmnd, LD) ||
	ft_strequ(cmnd, LLD) || ft_strequ(cmnd, AND) ||
	ft_strequ(cmnd, OR) || ft_strequ(cmnd, XOR));
}

void			cmnd_size(t_command *cmnd)
{
	cmnd->size = cmnd->arg2 || ft_strequ(cmnd->cmnd, AFF) ? 2 : 1;
	codeargstypes(cmnd, tdir_size(cmnd->cmnd));
	if (!(cmnd->arg2 || ft_strequ(cmnd->cmnd, AFF)))
		cmnd->argsize = 0;
}
