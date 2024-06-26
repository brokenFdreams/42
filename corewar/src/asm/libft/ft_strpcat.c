/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:57:27 by fsinged           #+#    #+#             */
/*   Updated: 2019/06/26 16:00:21 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpcat(char *s1, const char *s2, size_t n, size_t pos)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		s1[pos + i] = s2[i];
		i++;
	}
	return (s1);
}
