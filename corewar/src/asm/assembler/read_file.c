/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:04:16 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/19 16:10:05 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			cnt_del(t_cnt **cnt)
{
	t_cnt	*tmp;
	t_cnt	*buf;

	if (cnt && *cnt)
	{
		buf = *cnt;
		while (buf)
		{
			tmp = buf->next;
			ft_strdel(&(buf->line));
			free(buf);
			buf = tmp;
		}
		*cnt = NULL;
	}
}

static t_cnt	*new_cnt(char **line, size_t pos)
{
	t_cnt	*cnt;

	cnt = (t_cnt*)malloc(sizeof(t_cnt));
	cnt->line = *line;
	cnt->pos = pos;
	cnt->next = NULL;
	return (cnt);
}

t_cnt			*read_file(int fd)
{
	t_cnt	*cnt;
	t_cnt	*tmp;
	int		gnl;
	char	*line;

	cnt = NULL;
	while ((gnl = get_next_line(fd, &line)) == 1)
		if (cnt == NULL)
		{
			cnt = new_cnt(&line, 0);
			tmp = cnt;
		}
		else if ((tmp->next = new_cnt(&line, tmp->pos + 1)))
			tmp = tmp->next;
	if (gnl == -1)
		read_error("Read error");
	if (!(line && line[skip_space(line, 0)] == '\0'))
		read_error("No new line at the end of file");
	ft_strdel(&line);
	return (cnt);
}
