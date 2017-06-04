/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:31:11 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/02 18:25:46 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_inst(t_list *elem)
{
	ft_putendl(((t_instruction *)elem->content)->instruction);
}

static void		print_room(t_list *elem)
{
	ft_lstiter(((t_room *)elem->content)->instruction, print_inst);
	ft_putstr(((t_room *)elem->content)->name);
	ft_putstr(" ");
	ft_putnbr(((t_room *)elem->content)->x);
	ft_putstr(" ");
	ft_putnbr_endl(((t_room *)elem->content)->y);
}

static void		print_pipe(t_list *elem)
{
	t_pipe		*pipe;

	ft_lstiter(((t_pipe *)elem->content)->instruction, print_inst);
	pipe = (t_pipe *)elem->content;
	ft_putstr(((t_room *)pipe->room1->content)->name);
	ft_putstr("-");
	ft_putendl(((t_room *)pipe->room2->content)->name);
}

static void		check_if_command_after_pipe(t_data *data)
{
	t_list	*tmp;
	t_list	*save;
	t_list	*last_node;
	char	*str;

	if (data->instruction)
	{
		tmp = data->instruction;
		save = tmp;
		while (tmp)
		{
			str = ((t_instruction *)tmp->content)->instruction;
			if (*(str + 1) == '#')
			{
				ft_lstdel(&tmp, free_instruction_content);
				last_node->next = NULL;
				tmp = save;
				return;
			}
			last_node = tmp;
			tmp = tmp->next;
		}
	}
}

static void		print_last_comment(t_list *elem)
{
	ft_putendl(((t_instruction *)elem->content)->instruction);
}

void			print_map(t_data *data)
{
	//t_list	*tmp;

	check_if_command_after_pipe(data);
	//if ((tmp = check_if_command_after_pipe(data)))
	//	ft_lstdel(&tmp, free_instruction_content);
	ft_putnbr_endl(data->ants);
	ft_lstiter(data->room, print_room);
	ft_lstiter(data->pipe, print_pipe);
	if (data->instruction)
		ft_lstiter(data->instruction, print_last_comment);
}
