/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:06:54 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/19 16:07:09 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Rewrite magic number in char*
*/

static void		rewrite_magic(char *head)
{
	char	*magic;
	int		size;
	size_t	pos;

	pos = 4;
	magic = ft_itoa_base(COREWAR_EXEC_MAGIC, 16);
	size = ft_strlen(magic);
	while (--size >= 0 && pos != 0)
	{
		head[--pos] = ft_isdigit(magic[size]) ? magic[size] - '0' :
				magic[size] - 'a' + 10;
		if (--size >= 0)
			head[pos] += ft_isdigit(magic[size]) ? (magic[size] - '0') * 16 :
					(magic[size] - 'a' + 10) * 16;
	}
	ft_strdel(&magic);
}

/*
** Rewrite head(name, comment and codesize) in char*
*/

static size_t	rewrite_head(t_header *header, char **head, size_t codesize)
{
	size_t	size;
	size_t	pos;

	size = PROG_NAME_LENGTH + COMMENT_LENGTH + 4 * 4;
	if (!((*head) = ft_strnew(size)))
		read_error("Malloce error");
	rewrite_magic(*head);
	pos = 4;
	ft_strpcat(*head, header->prog_name, PROG_NAME_LENGTH, pos);
	pos += PROG_NAME_LENGTH + 4;
	rewrite_num(codesize, (*head) + pos, 1);
	ft_strpcat(*head, header->comment, COMMENT_LENGTH, pos + 4);
	return (size);
}

/*
** Rewrite code(all commands) in char*
*/

static size_t	rewrite_code(t_command *cmnd, char **code)
{
	t_command	*tmp;
	size_t		size;

	size = 0;
	tmp = cmnd;
	while (tmp)
	{
		size += tmp->size;
		tmp = tmp->next;
	}
	if (!(*code = ft_strnew(size)))
		read_error("Malloc error");
	tmp = cmnd;
	size = 0;
	while (tmp)
	{
		size += rewrite_command(tmp, cmnd, (*code) + size);
		tmp = tmp->next;
	}
	return (size);
}

/*
** Rewrite all data in .cor file
*/

void			rewrite_content(t_command *cmnd, t_header *header, char *file)
{
	char	*head;
	char	*code;
	size_t	codesize;
	int		fd;

	codesize = rewrite_code(cmnd, &code);
	header->prog_size = rewrite_head(header, &head, codesize);
	file[ft_strlen(file) - 1] = '\0';
	ft_strcat(file, "cor");
	if ((fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0)
		read_error("Can't create file");
	write(fd, (unsigned char*)head, header->prog_size);
	write(fd, (unsigned char*)code, codesize);
	if (close(fd))
		read_error("Can't close file");
	ft_strdel(&file);
	ft_strdel(&head);
	ft_strdel(&code);
}
