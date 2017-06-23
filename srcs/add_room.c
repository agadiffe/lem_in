/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 15:45:43 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/23 15:56:58 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list			*copy_lst(t_list *elem)
{
	return (elem);
}

static void		check_if_room_exist(t_data *data, t_room *room)
{
	t_list	*tmp_name;
	t_list	*tmp_coord;
	t_list	*tmp_room;
	t_room	*tmp;

	tmp_name = get_room_node_by_name(&data->room, room->name);
	tmp_coord = get_room_node_by_coord(&data->room, room->x, room->y);
	tmp_room = tmp_name ? tmp_name : tmp_coord;
	if (tmp_room)
	{
		tmp = (t_room *)tmp_room->content;
		tmp->old = 1;
		if (room->instruction)
			ft_lstaddback(&tmp->all_instruction,
					ft_lstmap(room->instruction, copy_lst));
		room->all_instruction = tmp->all_instruction;
	}
	else
	{
		room->all_instruction = room->instruction ?
			ft_lstmap(room->instruction, copy_lst) : NULL;
	}
}

static void		init_coord_new_room(t_data *data, int *room_coord, char *s)
{
	char		*str;

	str = ft_strrchr(s, ' ');
	*room_coord = ft_atoi_lemin(str + 1, data);
	*str = '\0';
}

static void		init_data_new_room(t_data *data, t_room *room, char *s)
{
	init_coord_new_room(data, &room->y, s);
	init_coord_new_room(data, &room->x, s);
	if (data->stop_get_data)
		return ;
	room->ants = 0;
	room->old = 0;
	room->start = 0;
	room->end = 0;
	room->name = s;
	room->room_pipe = NULL;
	room->path = 0;
	room->instruction = data->instruction;
	data->instruction = NULL;
}

int				add_new_room(t_data *data, char *s)
{
	t_list		*tmp;
	int			bad_data;

	bad_data = 0;
	if (*s != 'L')
	{
		tmp = ft_lstnew(&data->room_content, sizeof(t_room));
		init_data_new_room(data, (t_room *)tmp->content, s);
		if (data->stop_get_data)
		{
			bad_data = 1;
			ft_strdel(&s);
			ft_memdel((void**)&tmp->content);
			ft_memdel((void**)&tmp);
		}
		else
		{
			check_if_room_exist(data, (t_room *)tmp->content);
			ft_lstaddback(&data->room, tmp);
		}
	}
	else
		bad_data = 1;
	return (bad_data ? 1 : 0);
}
