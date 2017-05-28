/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:31:11 by agadiffe          #+#    #+#             */
/*   Updated: 2017/05/28 20:03:03 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_pipe_inside_room(t_list *elem)
{
	t_room		*tmp_room;

	tmp_room = (t_room *)((t_room_pipe *)elem->content)->room;
	ft_putstr("     -> pipe with: ");
	ft_putendl(tmp_room->name);
}

static void		print_inst(t_list *elem)
{
	ft_putendl(((t_instruction *)elem->content)->instruction);
}

static void		print_room(t_data *data)
{
	t_list		*tmp;

	tmp = data->room;
	while (tmp)
	{
		ft_lstiter(((t_room *)tmp->content)->instruction, print_inst);
		ft_putstr(((t_room *)tmp->content)->name);
		ft_putstr(" ");
		ft_putnbr(((t_room *)tmp->content)->x);
		ft_putstr(" ");
		ft_putnbr_endl(((t_room *)tmp->content)->y);
		ft_lstiter(((t_room *)tmp->content)->room_pipe, print_pipe_inside_room);
		tmp = tmp->next;
	}
}

static void		print_pipe(t_data *data)
{
	t_list		*tmp;
	t_pipe		*pipe;

	tmp = data->pipe;
	while (tmp)
	{
		ft_lstiter(((t_pipe *)tmp->content)->instruction, print_inst);
		ft_putendl("[+]--->");
		ft_lstiter(((t_pipe *)tmp->content)->all_instruction, print_inst);
		ft_putendl("---<");
		pipe = (t_pipe *)tmp->content;
		ft_putstr(((t_room *)pipe->room1->content)->name);
		ft_putstr("-");
		ft_putendl(((t_room *)pipe->room2->content)->name);
		tmp = tmp->next;
	}
}

static int		check_if_command_after_pipe(t_data *data)
{
	t_list		*tmp;
	char		*str;

	if (data->instruction)
	{
		tmp = data->instruction;
		while (tmp)
		{
			str = ((t_instruction *)tmp->content)->instruction;
			if (*(str + 1) == '#')
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

static void		print_last_comment(t_list *elem)
{
	char		*str;

	str = ((t_instruction *)elem->content)->instruction;
	if (*(str + 1) != '#')
		ft_putendl(str);
}

void			print_map(t_data *data)
{
	if (check_if_command_after_pipe(data))
	{
		//free everything
		ft_error("ERROR", 1);
	}
	ft_putnbr_endl(data->ants);
	print_room(data);
	print_pipe(data);
	if (data->instruction)
		ft_lstiter(data->instruction, print_last_comment);
}
