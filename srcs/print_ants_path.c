/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 20:22:13 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/08 20:08:54 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_ants_in_room(t_list *elem)
{
	if (((t_room_pipe *)elem->content)->room->ants > 0)
	{
		ft_putstr("L");
		ft_putnbr(((t_room_pipe *)elem->content)->room->ants);
		ft_putstr("-");
		ft_putstr(((t_room_pipe *)elem->content)->room->name);
		if (elem->next && ((t_room_pipe *)elem->next->content)->room->ants > 0)
			ft_putstr(" ");
	}
}

static void		move_ants(t_list *path, int ants)
{
	t_list	*tmp;
	int		save;

	tmp = path;
	save = 1;
	while (tmp)
	{
		if (((t_room_pipe *)tmp->content)->room->ants == 0
				|| ((t_room_pipe *)tmp->content)->room->end)
		{
			((t_room_pipe *)tmp->content)->room->ants = save;
			return ;
		}
		save = ((t_room_pipe *)tmp->content)->room->ants;
		((t_room_pipe *)tmp->content)->room->ants =
			save < ants && save > 0 ? save + 1 : -1;
		tmp = tmp->next;
	}
}

void			print_ants_path(t_data *data)
{
	t_list	*end_node;
	t_room	*end;

	end_node = get_end_room(&data->room);
	end = (t_room *)end_node->content;
	while (end->ants < data->ants)
	{
		move_ants(data->path, data->ants);
		ft_lstiter(data->path, print_ants_in_room);
		ft_putendl("");
	}
}
