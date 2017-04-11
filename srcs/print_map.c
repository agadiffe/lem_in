/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:31:11 by agadiffe          #+#    #+#             */
/*   Updated: 2017/04/11 18:23:26 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_pipe_room_inside_room_list(t_list *room_pipe)
{
	t_list		*tmp;
	t_room		*tmp_room;

	tmp = room_pipe;
	while (tmp)
	{
		tmp_room = (t_room *)((t_room_pipe *)tmp->content)->room;
		ft_putstr("     -> pipe with: ");
		ft_putendl(tmp_room->name);
		tmp = tmp->next;
	}
}

static void		print_room(t_data *data)
{
	t_list		*tmp;
	t_list		*tmp2;

	tmp = data->room;
	while (tmp)
	{
		tmp2 = ((t_room *)tmp->content)->instruction;
		while (tmp2)
		{
			ft_putendl(((t_instruction *)tmp2->content)->instruction);
			tmp2 = tmp2->next;
		}
		ft_putstr(((t_room *)tmp->content)->name);
		ft_putstr(" ");
		ft_putnbr(((t_room *)tmp->content)->x);
		ft_putstr(" ");
		ft_putnbr_endl(((t_room *)tmp->content)->y);
		print_pipe_room_inside_room_list(((t_room *)tmp->content)->room_pipe);
		tmp = tmp->next;
	}
}

static void		print_pipe(t_data *data)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_pipe		*pipe;

	tmp = data->pipe;
	while (tmp)
	{
		tmp2 = ((t_pipe *)tmp->content)->instruction;
		while (tmp2)
		{
			ft_putendl(((t_instruction *)tmp2->content)->instruction);
			tmp2 = tmp2->next;
		}
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

static void		print_last_comment(t_data *data)
{
	t_list		*tmp;
	char		*str;

	if (data->instruction)
	{
		tmp = data->instruction;
		while (tmp)
		{
			str = ((t_instruction *)tmp->content)->instruction;
			if (*(str + 1) != '#')
				ft_putendl(str);
			tmp = tmp->next;
		}
	}
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
	print_last_comment(data);
}
