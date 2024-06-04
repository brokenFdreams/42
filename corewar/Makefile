#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsinged <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/02 13:23:02 by fsinged           #+#    #+#              #
#    Updated: 2019/12/05 17:01:26 by fsinged          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJDIR = OBJ/

ASM = asm
ASMLIBFT = src/asm/libft/
ASMLNAM = $(addprefix $(ASMLIBFT), libft.a)

ASMINC = includes/
ASMHEADERS = $(ASMINC)asm.h $(ASMINC)commands.h $(ASMINC)op.h $(ASMLIBFT)libft.h
ASM_INC = -I $(ASMINC) -I $(ASMLIBFT)

ASMSRCDIR = src/asm/
ASMSRC = asm.c ft_error.c

ASM_ASSEMBLER_SRCDIR = $(ASMSRCDIR)assembler/
ASM_ASSEMBLER_SRC = assembler.c chk_arguments.c chk_commands.c chk_lables.c cmnd_size.c \
is_command.c is_label.c read_arguments.c read_file.c skip_space.c validation.c \
rewrite_code.c rewrite_content.c

ASMOBJDIR = $(OBJDIR)asm/
ASMOBJ = $(ASMSRC:.c=.o)
ASMOBJS = $(addprefix $(ASMOBJDIR), $(ASMOBJ))

ASM_ASSEMBLER_OBJDIR = $(ASMOBJDIR)assembler/
ASM_ASSEMBLER_OBJ = $(ASM_ASSEMBLER_SRC:.c=.o)
ASM_ASSEMBLER_OBJS = $(addprefix $(ASM_ASSEMBLER_OBJDIR), $(ASM_ASSEMBLER_OBJ))

all:$(OBJ) $(ASM)

$(OBJ):
	@mkdir -p $(OBJ)

$(ASM):$(ASMLIBFT) $(ASMOBJDIR) $(ASM_ASSEMBLER_OBJDIR) $(ASMOBJS) $(ASM_ASSEMBLER_OBJS)
	@make -C $(ASMLIBFT)
	@$(CC) $(CFLAGS) $(ASMLNAM) $(ASM_INC) $(ASMOBJS) $(ASM_ASSEMBLER_OBJS) -o $(ASM)

$(ASMOBJDIR):
	@mkdir -p $(ASMOBJDIR)

$(ASM_ASSEMBLER_OBJDIR):
	@mkdir -p $(ASM_ASSEMBLER_OBJDIR)

$(ASMOBJDIR)%.o:$(ASMSRCDIR)%.c $(ASMHEADERS)
	@$(CC) $(CFLAGS) -c $(ASM_INC) $< -o $@

clean:
	@make -C $(ASMLIBFT) fclean
	@/bin/rm -rf $(OBJDIR)

fclean:clean
	@rm -f $(ASM)

re:fclean all