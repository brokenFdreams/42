/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:52:16 by fsinged           #+#    #+#             */
/*   Updated: 2019/12/28 12:21:53 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Initialization of new command
*/

static t_command	*init_command(void)
{
	t_command	*cmnd;

	cmnd = (t_command*)malloc(sizeof(t_command));
	cmnd->next = NULL;
	cmnd->label = NULL;
	cmnd->cmnd = NULL;
	cmnd->arg1 = NULL;
	cmnd->arg2 = NULL;
	cmnd->arg3 = NULL;
	return (cmnd);
}

/*
** Reading command and its arguments
*/

static t_command	*read_command(t_cnt **cnt, size_t i)
{
	t_command	*cmnd;
	size_t		size;

	cmnd = init_command();
	if ((size = is_label((*cnt)->line + i)))
		cmnd->label = ft_strncpy(ft_strnew(size), (*cnt)->line + i, size);
	cmnd->labelpos = (*cnt)->pos;
	i = skip_spaces(cnt, i + size);
	if (*cnt && (size = is_command((*cnt)->line + i)))
	{
		cmnd->cmnd = ft_strncpy(ft_strnew(size), (*cnt)->line + i, size);
		i += size;
		if ((size = read_arguments((*cnt)->line + i, cmnd)) != -1)
			ft_error("Invalid argument", (*cnt)->pos, i + size);
		cmnd->cmndpos = (*cnt)->pos;
		cmnd_size(cmnd);
	}
	return (cmnd);
}

/*
** get all commands and save them in usable view
*/

t_command			*chk_commands(t_cnt *cnt)
{
	t_command	*cmnd;
	t_command	*tmp;
	size_t		i;

	i = skip_spaces(&cnt, 0);
	if (cnt && cnt->line)
	{
		cmnd = read_command(&cnt, i);
		if (!(cmnd->cmnd) && !(cmnd->label))
			ft_error("Invalid command", cnt->pos, i);
		tmp = cmnd;
	}
	else
		read_error("No commands in file");
	while (cnt && (cnt->next || !(tmp->cmnd)))
	{
		if (tmp->cmnd)
			cnt = cnt->next;
		i = skip_spaces(&cnt, 0);
		if (cnt && cnt->line)
			tmp->next = read_command(&cnt, i);
		if ((tmp = tmp->next) && !(tmp->cmnd || tmp->label))
			ft_error("Invalid command", cnt->pos, i);
	}
	return (cmnd);
}
