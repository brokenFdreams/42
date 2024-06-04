/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:56:44 by fsinged           #+#    #+#             */
/*   Updated: 2019/12/28 12:23:48 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check name
*/

static void		chk_name(char *content, t_header *header, size_t pos)
{
	size_t	name_size;

	name_size = 0;
	if (!content || !(ft_strnequ(content + pos, NAME_CMD_STRING,
		ft_strlen(NAME_CMD_STRING))))
		ft_error("No name", 0, pos);
	pos += ft_strlen(NAME_CMD_STRING);
	pos += skip_space(content, pos);
	if (content[pos] != '"')
		ft_error("Invalid name", 0, pos);
	pos++;
	while (content[pos] && content[pos] != '"' && ++name_size)
		pos++;
	if (name_size > PROG_NAME_LENGTH)
		lenght_error("name", PROG_NAME_LENGTH);
	if (content[pos] != '"')
		ft_error("Invalid name", 0, pos);
	ft_strncat(header->prog_name, content + (pos - name_size), name_size);
	pos++;
	pos += skip_space(content, pos);
	if (content[pos] != '\0')
		ft_error("No newline after name", 0, pos + 1);
}

/*
** Check comment
*/

static void		chk_comment(char *content, t_header *header, size_t pos)
{
	size_t	cmnt_size;

	cmnt_size = 0;
	if (!content || !(ft_strnequ(content + pos, COMMENT_CMD_STRING,
		ft_strlen(COMMENT_CMD_STRING))))
		ft_error("No comment", 1, pos);
	pos += ft_strlen(COMMENT_CMD_STRING);
	pos += skip_space(content, pos);
	if (content[pos] != '"')
		ft_error("Invalid comment", 1, pos);
	pos++;
	while (content[pos] && content[pos] != '"' && ++cmnt_size)
		pos++;
	if (cmnt_size > COMMENT_LENGTH)
		lenght_error("comment", COMMENT_LENGTH);
	if (content[pos] != '"')
		ft_error("Invalid comment", 1, pos);
	ft_strncat(header->comment, content + (pos - cmnt_size), cmnt_size);
	pos++;
	pos += skip_space(content, pos);
	if (content[pos] != '\0')
		ft_error("No newline after comment", 1, pos + 1);
}

t_command		*validation(t_cnt *cnt, t_header *header)
{
	t_command	*cmnd;
	size_t		i;

	i = skip_spaces(&cnt, 0);
	if (!cnt)
		read_error("File is empty");
	chk_name(cnt->line, header, i);
	cnt = cnt->next;
	i = skip_spaces(&cnt, 0);
	if (!cnt)
		read_error("Only name in file");
	chk_comment(cnt->line, header, i);
	cmnd = chk_commands(cnt->next);
	chk_labels(cmnd);
	return (cmnd);
}
