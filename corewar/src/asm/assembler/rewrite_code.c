/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:14:38 by fsinged           #+#    #+#             */
/*   Updated: 2019/12/28 12:12:08 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Return how much bytes we got to go to label from out command
*/

static int		rewrite_label(t_command *head, t_command *cmnd, char *arg)
{
	int	size;
	int	flag;

	if (arg[0] == LABEL_CHAR)
		arg++;
	else if (arg[0] == DIRECT_CHAR && arg[1] == LABEL_CHAR)
		arg += 2;
	if (ft_strnequ(cmnd->label, arg, ft_strlen(arg)) &&
		cmnd->label[ft_strlen(arg)] == LABEL_CHAR)
		return (0);
	size = 0;
	while (!(ft_strnequ(head->label, arg, ft_strlen(arg)) &&
		head->label[ft_strlen(arg)] == LABEL_CHAR) && head->next != cmnd->next)
		head = head->next;
	flag = ft_strnequ(head->label, arg, ft_strlen(arg));
	size += flag ? -head->size : 0;
	head = head->next;
	while (head && !(ft_strnequ(head->label, arg, ft_strlen(arg)) &&
		head->label[ft_strlen(arg)] == LABEL_CHAR) && head->next != cmnd->next)
	{
		size += flag ? -head->size : head->size;
		head = head->next;
	}
	return (size + (flag ? 0 : cmnd->size));
}

/*
** Rewrite tdir and tind in bytecode and write it in code
*/

void			rewrite_num(int arg, char *code, int tdirsize)
{
	int		pos;
	size_t	size;
	char	*num;
	char	*tmp;

	pos = tdirsize ? 3 : 1;
	num = ft_itoa_base(tdirsize ? (unsigned long int)arg :
			(unsigned short int)arg, 2);
	size = ft_strlen(num);
	while (pos >= 0)
	{
		if (size > 8)
			tmp = ft_strncpy(ft_strnew(8), num + (size - 8), 8);
		else
			tmp = ft_strncpy(ft_strnew(size), num, size);
		code[pos--] = ft_atoi_base(tmp, 2);
		ft_strdel(&tmp);
		size = size > 8 ? size - 8 : 0;
	}
	ft_strdel(&num);
}

/*
** Rewrite arguments in byte code in char *code
*/

static void		rewrite_arg(t_command *head, char *arg,
		t_command *cmnd, char *code)
{
	if (!arg)
		return ;
	if (is_treg(arg))
		code[0] = (char)ft_atoi(arg + 1);
	else if ((is_tind(arg) && arg[0] != LABEL_CHAR) ||
			(is_tdir(arg) && arg[1] != LABEL_CHAR))
	{
		if (arg[0] == DIRECT_CHAR && arg[1] == 0 &&
			(arg[2] == 'x' || arg[2] == 'X'))
			rewrite_num(ft_atoi_base(arg + 3, 16), code,
					is_tdir(arg) && tdir_size(cmnd->cmnd));
		else
			rewrite_num(ft_atoi(arg[0] == DIRECT_CHAR ? arg + 1 : arg), code,
					is_tdir(arg) && tdir_size(cmnd->cmnd));
	}
	else
		rewrite_num(rewrite_label(head, cmnd, arg), code,
			is_tdir(arg) && tdir_size(cmnd->cmnd));
}

/*
** Return a command code (live - 1, ld - 2, ..., aff - 16)
*/

static size_t	command_code(char *cmnd)
{
	size_t res;

	res = ft_strequ(cmnd, LIVE) ? 1 : 0;
	res = ft_strequ(cmnd, LD) ? 2 : res;
	res = ft_strequ(cmnd, ST) ? 3 : res;
	res = ft_strequ(cmnd, ADD) ? 4 : res;
	res = ft_strequ(cmnd, SUB) ? 5 : res;
	res = ft_strequ(cmnd, AND) ? 6 : res;
	res = ft_strequ(cmnd, OR) ? 7 : res;
	res = ft_strequ(cmnd, XOR) ? 8 : res;
	res = ft_strequ(cmnd, ZJMP) ? 9 : res;
	res = ft_strequ(cmnd, LDI) ? 10 : res;
	res = ft_strequ(cmnd, STI) ? 11 : res;
	res = ft_strequ(cmnd, FFORK) ? 12 : res;
	res = ft_strequ(cmnd, LLD) ? 13 : res;
	res = ft_strequ(cmnd, LLDI) ? 14 : res;
	res = ft_strequ(cmnd, LFORK) ? 15 : res;
	res = ft_strequ(cmnd, AFF) ? 16 : res;
	return (res);
}

/*
** Rewrite command and its arguments in bytecode in char *code
*/

size_t			rewrite_command(t_command *cmnd, t_command *head,
		char *code)
{
	size_t	pos;

	if (!(cmnd->cmnd))
		return (cmnd->size);
	pos = 0;
	code[pos++] = command_code(cmnd->cmnd);
	if (cmnd->argsize != 0 || ft_strequ(cmnd->cmnd, AFF))
		code[pos++] = cmnd->argsize;
	rewrite_arg(head, cmnd->arg1, cmnd, code + pos);
	pos += is_treg(cmnd->arg1) ? 1 : 2;
	pos += is_tdir(cmnd->arg1) && tdir_size(cmnd->cmnd) ? 2 : 0;
	rewrite_arg(head, cmnd->arg2, cmnd, code + pos);
	pos += cmnd->arg2 && is_treg(cmnd->arg2) ? 1 : 2;
	pos += cmnd->arg2 && is_tdir(cmnd->arg2) && tdir_size(cmnd->cmnd) ? 2 : 0;
	rewrite_arg(head, cmnd->arg3, cmnd, code + pos);
	return (cmnd->size);
}
