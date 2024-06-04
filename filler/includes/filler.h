/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:33:52 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/23 14:59:55 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include <stdio.h>

typedef struct	s_map
{
	int			width;
	int			height;
	char		**points;
}				t_map;

typedef struct	s_filler
{
	char		player;
	char		enemy;
	t_map		map;
	t_map		piece;
}				t_filler;

t_filler	*init_filler(char id);

#endif
