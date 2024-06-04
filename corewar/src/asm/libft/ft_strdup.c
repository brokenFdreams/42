/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:51 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/22 13:23:31 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*ch;
	unsigned int	i;

	if (!(s1 && (ch = ft_strnew(ft_strlen(s1)))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ch[i] = s1[i];
		i++;
	}
	ch[i] = '\0';
	return (ch);
}
