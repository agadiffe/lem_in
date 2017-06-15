/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe_to_room_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 18:45:48 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/15 18:46:00 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_if_pipe_exist(t_room *room, t_room *new_pipe)
{
	t_list	*tmp;

	tmp = room->room_pipe;
	while (tmp)
	{
		if (((t_room_pipe *)tmp->content)->room == new_pipe)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void		add_pipe_handle(t_data *data, t_room *room, t_room *new_pipe)
{
	t_list	*tmp2;

	if (!check_if_pipe_exist(room, new_pipe))
	{
		tmp2 = ft_lstnew(&data->room_pipe_content, sizeof(t_room_pipe));
		((t_room_pipe *)tmp2->content)->room = new_pipe;
		ft_lstaddback(&room->room_pipe, tmp2);
	}
}

void			add_pipe_to_room_list(t_data *data)
{
	t_list	*tmp;
	t_pipe	*pipe;
	t_room	*room1;
	t_room	*room2;

	tmp = data->pipe;
	while (tmp)
	{
		pipe = (t_pipe *)tmp->content;
		room1 = (t_room *)pipe->room1->content;
		room2 = (t_room *)pipe->room2->content;
		add_pipe_handle(data, room1, room2);
		add_pipe_handle(data, room2, room1);
		tmp = tmp->next;
	}
}
