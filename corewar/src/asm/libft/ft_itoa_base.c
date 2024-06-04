/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:05:18 by fsinged           #+#    #+#             */
/*   Updated: 2019/06/26 16:13:02 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_length(uintmax_t nbr, int base)
{
	size_t count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr / base || nbr % base)
	{
		count++;
		nbr /= base;
	}
	return (count);
}

char			*ft_itoa_base(uintmax_t nbr, int base)
{
	char	*num;
	int		rem;
	size_t	size;

	size = ft_itoa_length(nbr, base);
	if (!(num = ft_strnew(size)))
		return (NULL);
	while (size-- > 0)
	{
		rem = nbr % base;
		num[size] = rem >= 10 ? rem + 'a' - 10 : rem + '0';
		nbr /= base;
	}
	return (num);
}
