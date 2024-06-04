/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:51:54 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/13 13:25:11 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strarraydel(char ***src)
{
	char	**tmp;

	tmp = *src;
	while (*tmp)
	{
		ft_strdel(&(*tmp));
		tmp++;
	}
	free(*src);
	*src = NULL;
}
