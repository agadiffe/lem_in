/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:39:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/04 19:01:30 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*copy_lst(t_list *elem)
{
	return (elem);
}

static void		check_if_room_exist(t_data *data, t_room *room)
{
	t_list	*tmp_name;
	t_list	*tmp_coord;
	t_list	*tmp;

	tmp_name = get_room_node_by_name(&data->room, room->name);
	tmp_coord = get_room_node_by_coord(&data->room, room->x, room->y);
	tmp = tmp_name ? tmp_name : tmp_coord;
	if (tmp)
	{
		((t_room *)tmp->content)->old = 1;
		if (room->instruction)
			ft_lstaddback(&((t_room *)tmp->content)->all_instruction,
					ft_lstmap(room->instruction, copy_lst));
		room->all_instruction = ((t_room *)tmp->content)->all_instruction;
	}
	else
	{
		room->all_instruction = room->instruction ?
			ft_lstmap(room->instruction, copy_lst) : NULL;
	}
}

int			add_new_room(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	int			bad_data;

	bad_data = 0;
	if (*s != 'L')
	{
		tmp = ft_lstnew(&data->room_content, sizeof(t_room));
		str = ft_strrchr(s, ' ');
		((t_room *)tmp->content)->y = ft_atoi(str);
		*str = '\0';
		str = ft_strrchr(s, ' ');
		((t_room *)tmp->content)->x = ft_atoi(str);
		*str = '\0';
		((t_room *)tmp->content)->old = 0;
		((t_room *)tmp->content)->start = 0;
		((t_room *)tmp->content)->end = 0;
		((t_room *)tmp->content)->name = s;
		((t_room *)tmp->content)->room_pipe = NULL;
		((t_room *)tmp->content)->room_number = data->nbr_room++;
		((t_room *)tmp->content)->instruction = data->instruction;
		data->instruction = NULL;
		check_if_room_exist(data, (t_room *)tmp->content);
		ft_lstaddback(&data->room, tmp);
	}
	else
		bad_data = 1;
	return (bad_data ? 1 : 0);
}

void		add_new_instruction(t_data *data, char *s)
{
	t_list		*tmp;

	tmp = ft_lstnew(&data->instruction_content, sizeof(t_instruction));
	ft_lstaddback(&data->instruction, tmp);
	((t_instruction *)tmp->content)->instruction = s;
}

int			add_new_pipe(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	t_list		*tmp_room;
	t_list		*tmp_pipe;
	int			bad_data;

	str = ft_strrchr(s, '-');
	tmp = ft_lstnew(&data->pipe_content, sizeof(t_pipe));
	((t_pipe *)tmp->content)->name = s;
	((t_pipe *)tmp->content)->old = 0;
	tmp_room = get_room_node_by_name(&data->room, str + 1);
	((t_pipe *)tmp->content)->room2 = tmp_room;
	*str = '\0';
	tmp_room = get_room_node_by_name(&data->room, s);
	((t_pipe *)tmp->content)->room1 = tmp_room;
	bad_data = ((t_pipe *)tmp->content)->room1
					&& ((t_pipe *)tmp->content)->room2 ? 0 : 1;
	if (bad_data == 0)
	{
		((t_pipe *)tmp->content)->instruction = data->instruction;
		data->instruction = NULL;
		if (((t_pipe *)tmp->content)->instruction)
		{
			if ((tmp_pipe = get_pipe_node(&data->pipe, s, str + 1)))
			{
				ft_lstaddback(&((t_pipe *)tmp_pipe->content)->all_instruction,
							ft_lstmap(((t_pipe *)tmp->content)->instruction,
									copy_lst));
				((t_pipe *)tmp->content)->all_instruction =
					((t_pipe *)tmp_pipe->content)->all_instruction;
				((t_pipe *)tmp->content)->old = 1;
			}
			else
			{
				((t_pipe *)tmp->content)->all_instruction =
					ft_lstmap(((t_pipe *)tmp->content)->instruction, copy_lst);
			}
		}
		else
			((t_pipe *)tmp->content)->all_instruction = NULL;
		ft_lstaddback(&data->pipe, tmp);
	}
	else
		ft_memdel((void**)&tmp);
	*str = '-';
	return (bad_data ? 1 : 0);
}

int			check_if_pipe_exist(t_room *room, t_room *new_pipe)
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

void		add_pipe_handle(t_data *data, t_room *room, t_room *new_pipe)
{
	t_list	*tmp2;

	if (!check_if_pipe_exist(room, new_pipe))
	{
		tmp2 = ft_lstnew(&data->room_pipe_content, sizeof(t_room_pipe));
		((t_room_pipe *)tmp2->content)->room = new_pipe;
		ft_lstaddback(&room->room_pipe, tmp2);
	}
}

void		add_pipe_to_room_list(t_data *data)
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
