/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:16:44 by fsinged           #+#    #+#             */
/*   Updated: 2019/11/08 15:32:38 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include <stdio.h>


# include "libft.h"
# include <fcntl.h>
# include "op.h"
# include "commands.h"

typedef struct			s_command
{
	char				*label;
	char				*cmnd;
	char				*arg1;
	char				*arg2;
	char				*arg3;
	unsigned char		argsize;
	size_t				labelpos;
	size_t 				cmndpos;
	size_t				size;
	struct s_command	*next;
}						t_command;

typedef struct 			s_cnt
{
	char 				*line;
	size_t 				pos;
	struct s_cnt		*next;
}						t_cnt;

void					assembler(char *filename);
/*
** Read file in list t_cnt and return its header
*/
t_cnt					*read_file(int fd);
/*
** Check the content for validation,
** if its valid, return comands else exit with error massage (call ft_error)
*/
t_command				*validation(t_cnt *cnt, t_header *header);
int						is_label(char *str);
size_t					is_labelchars(char *str);
int						is_command(char *str);
int						is_tind(char *arg);
int						is_tdir(char *arg);
int						is_treg(char *arg);
int						read_arguments(char *data, t_command *cmnd);
/*
** Checking commands for validation
** if its valid, return command and its args else exit (call ft_error)
*/
t_command				*chk_commands(t_cnt *cnt);
/*
** Checking args for validation
** if its valid return -1 else return position in str, where is error
*/
int						chk_arguments(t_command *cmnd);
void					cmnd_size(t_command *cmnd);
int						tdir_size(char *cmnd);
/*
** Checking arg witch is link to label
*/
void					chk_labels(t_command *cmnd);
/*
** write msg in stdout about error and exit program
*/
void					ft_error(char *msg, size_t pos, size_t i);
/*
** write msg in stdout about error in reading file and exit program
*/
void					read_error(char *msg);
/*
** write msg in stdout about error
*/
void					label_error(char *msg, size_t pos);
/*
** write msg in stdout about too long name or comment
*/
void		lenght_error(char *msg, size_t size);
/*
** return 1 if c is equal to '\t' or ' ' else 0
*/
int						is_space(char c);
/*
** skip spaces in str, return position of next char after space
*/
size_t					skip_space(char *content, size_t place);
/*
** skip spaces in str and empty str, return position of next char after space
*/
size_t					skip_spaces(t_cnt **cnt, size_t i);
void					cnt_del(t_cnt **cnt);
/*
** Rewrite content in file.cor
*/
void					rewrite_content(t_command *cmnd, t_header *header, char *file);
size_t					rewrite_command(t_command *cmnd, t_command *head, char *code);
void					rewrite_num(int arg, char *code, int tdirsize);

#endif
