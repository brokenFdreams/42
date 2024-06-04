/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_filler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:39:29 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/23 15:19:10 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		free_filler(t_filler *filler)
{
	if (filler->map)
	{
		if (filler->map->points)
			while (--filler->map->height >= 0)
				ft_strdel(&(filler->map->points[filler->map->height]));
		free(filler->map);
	}
	if (filler->piece)
	{
		if (filler->piece->points)
			while (--filler->piece->height >= 0)
				ft_strdel(&(filler->piece->points[filler->map->height]));
		free(filler->piece);
	}
	free(filler);
}

t_filler	*init_filler(char id)
{
	t_filler	*filler;

	if (!(filler = (t_filler*)malloc(sizeof(t_filler))))
	{
		perror("Error");
		free(&filler);
		return (NULL);
	}
	filler->player = id == 1 ? 'O' : 'X';
	filler->enemy = id == 1 ? 'X' : 'O';
	filler->map = (t_map)ft_memalloc(sizeof(t_map));
	filler->piece = (t_map)ft_memalloc(sizeof(t_map));
	if (!(filler->map) || !(filler->piece))
	{
		perror("Error");
		free(&filler);
		return (NULL);
	}
	return (filler);
}
