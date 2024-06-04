/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_lables.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:02:29 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/22 13:25:50 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	arg_islabel(char *arg)
{
	if (arg[0] == DIRECT_CHAR && arg[1] == LABEL_CHAR)
		return (is_labelchars(arg + 2) == 0);
	else if (arg[0] == LABEL_CHAR)
		return (is_labelchars(arg + 1) == 0);
	return (0);
}

static void	simillar_labels(t_command *cmnd, t_command *tmp)
{
	while (cmnd)
		if (ft_strequ(cmnd->label, tmp->label) && cmnd->next != tmp->next)
			label_error("This label was found twice", tmp->labelpos);
		else
			cmnd = cmnd->next;
}

static int	chk_label(t_command *cmnd, char *arg)
{
	if (arg[0] == DIRECT_CHAR)
		arg += 2;
	else
		arg++;
	while (cmnd)
		if (ft_strnequ(arg, cmnd->label, ft_strlen(arg)))
			return (0);
		else
			cmnd = cmnd->next;
	return (1);
}

void		chk_labels(t_command *cmnd)
{
	t_command	*tmp;
	int			res;

	tmp = cmnd;
	while (tmp)
	{
		res = 0;
		if (tmp->arg1 && arg_islabel(tmp->arg1))
			res = chk_label(cmnd, tmp->arg1);
		if (tmp->arg2 && arg_islabel(tmp->arg2))
			res += chk_label(cmnd, tmp->arg2);
		if (tmp->arg3 && arg_islabel(tmp->arg3))
			res += chk_label(cmnd, tmp->arg3);
		if (res != 0)
			label_error("Label in argument not found", tmp->cmndpos);
		if (tmp->label)
			simillar_labels(cmnd, tmp);
		tmp = tmp->next;
	}
}
