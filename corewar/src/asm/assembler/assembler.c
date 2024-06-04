/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:54:42 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/19 16:02:12 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			cmnd_del(t_command **cmnd)
{
	t_command	*tmp;
	t_command	*buf;

	if (cmnd && *cmnd)
	{
		buf = *cmnd;
		while (buf)
		{
			tmp = buf->next;
			ft_strdel(&(buf->label));
			ft_strdel(&(buf->cmnd));
			ft_strdel(&(buf->arg1));
			ft_strdel(&(buf->arg2));
			ft_strdel(&(buf->arg3));
			free(buf);
			buf = tmp;
		}
		*cmnd = NULL;
	}
}

/*
** Initialisation of content struct
*/

static t_header	*init_header(void)
{
	t_header	*header;

	if (!(header = (t_header*)malloc(sizeof(t_header))))
		read_error("Malloc error");
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	return (header);
}

/*
** Check the code in file, check it,
** translate it to bytecode and write in new file
*/

void			assembler(char *filename)
{
	int			fd;
	t_header	*header;
	t_cnt		*cnt;
	t_command	*cmnd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		read_error("There's no file");
	cnt = read_file(fd);
	close(fd);
	header = init_header();
	cmnd = validation(cnt, header);
	cnt_del(&cnt);
	rewrite_content(cmnd, header,
			ft_strcpy(ft_strnew(ft_strlen(filename) + 2), filename));
	cmnd_del(&cmnd);
	free(header);
}
