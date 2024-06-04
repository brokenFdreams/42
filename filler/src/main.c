/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:28:01 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/23 15:19:30 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

/*
** Reading map after first time
*/

static void	read_map(char *line, t_map *map)
{
	int		i;
	int		j;
	char	*line;
	char	*tmp;

	i = -1;
	while (++i < map->height && get_next_line(0, &line))
	{
		j = -1;
		tmp = ft_strchr(line, ' ') + 1;
		while (++j < map->width && line[j])
			if (line[j] == 'x' || line[j] == 'o')
				map->points[i][j] = line[j];
		ft_strdel(&line);
	}
}

/*
** Reading piece and read map in first time
*/

static void	read_piece(char *line, t_map *map, int flag)
{
	int	i;

	map->height = ft_atoi(ft_strchr(line, ' '));
	map->width = ft_atoi(ft_strchr(ft_strchr(line, ' '), ' '));
	map->points = (char**)ft_memalloc(sizeof(char*) * map->height);
	if (flag && get_next_line(0, &line))
		ft_strdel(&line);
	i = -1;
	while (++i < map->height && get_next_line(0, &line))
		map->points[i] = line;
}


static void	fight(t_filler *filler)
{
	char	*line;

	while (get_next_line(0, &line) > -1)
	{
		if (!ft_strncmp(line, "Plateau ", 8))
		{
			if (!(filler->map->points))
				read_piece(line, filler->map, 1);
			else
				read_map(filler->map);
		}
		else if (!ft_strncmp(line, "Piece ", 6))
		{
			read_piece(line, filler->piece);
			place(filler);
		}
		ft_strdel(&line);
	}
}

int			main(void)
{
	char		*line;
	int			gnl;
	t_filler	*filler;

	if ((gnl = get_next_line(0, &line)) > 0 && line && ft_strlen(line) > 10 &&
		!ft_strncmp(line, "$$$ exec p", 9) &&
		(line[10] == '1' || line[10] == '2'))
	{
		filler = init_filler(line[10]);
		if (!(filler))
			return (1);
		ft_strdel(&line);
		fight(filler);
		free_filler(filler);
	}
	else
		return (1);
	return (0);
}
