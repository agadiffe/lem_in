/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:23:34 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/05 20:39:03 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		handle_path(t_list *elem)
{
	t_room_pipe		*tmp;
	t_room_pipe		*tmp2;
	t_list			*pipe_lst;

	tmp = (t_room_pipe *)elem->content;
	if (tmp->room->checked == 0)
	{
		tmp->room->path++;
		tmp->room->checked = 1;
	}
	pipe_lst = tmp->room->room_pipe;
	while (pipe_lst)
	{
		tmp2 = (t_room_pipe *)pipe_lst->content;
		if (tmp2->room->checked == 0)
		{
			tmp2->room->checked = 1;
			tmp2->room->path = tmp->room->path + 1;
			ft_lstiter(pipe_lst, handle_path);
		}
		pipe_lst = pipe_lst->next;
	}
}

void			find_path(t_data *data)
{
	t_list			*tmp;
	t_list			*start;

	start = get_start_room(&data->room);
	((t_room *)start->content)->checked = 1;
	tmp = ((t_room *)start->content)->room_pipe;
	if (tmp)
		ft_lstiter(tmp, handle_path);
}
