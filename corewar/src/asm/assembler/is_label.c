/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:03:49 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/19 16:03:58 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_labelchar(char c)
{
	size_t	pos;

	pos = 0;
	while (LABEL_CHARS[pos])
		if (c == LABEL_CHARS[pos])
			return (1);
		else
			pos++;
	return (0);
}

/*
** Check is str contains only label chars or not
** return 0 if its contains only label chars
** return pos in label, where str contains invalid char for label
*/

size_t		is_labelchars(char *str)
{
	size_t	pos;

	pos = 0;
	while (str[pos] && is_labelchar(str[pos]))
		pos++;
	return (str[pos] == '\0' ? 0 : pos);
}

/*
** Check is it label or not
*/

int			is_label(char *str)
{
	size_t	pos;

	pos = is_labelchars(str);
	return (pos != 0 && str[pos] == LABEL_CHAR ? pos + 1 : 0);
}
