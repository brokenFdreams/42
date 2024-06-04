/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:46:42 by fsinged           #+#    #+#             */
/*   Updated: 2019/12/28 16:01:59 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_filename(char *filename, char *dot)
{
	if (ft_strequ(filename + (ft_strlen(filename) - ft_strlen(dot)), dot))
		return (1);
	return (0);
}

static void	print_help(void)
{
	write(1, "Usage: ./asm [filename]\n", 24);
	write(1, "For assembler - filename.s\n", 27);
}

int			main(int argc, char **argv)
{
	if (argc == 2 && is_filename(*(argv + 1), ".s"))
		assembler(*(argv + 1));
	else
		print_help();
	return (0);
}
