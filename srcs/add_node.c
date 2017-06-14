/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:39:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/14 20:32:21 by agadiffe         ###   ########.fr       */
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

static void		init_coord_new_room(int *room_coord, char *s)
{
	char		*str;

	str = ft_strrchr(s, ' ');
	*room_coord = ft_atoi(str);
	*str = '\0';
}

static void		init_data_new_room(t_data *data, t_room *room, char *s)
{
	init_coord_new_room(&room->y, s);
	init_coord_new_room(&room->x, s);
	room->ants = 0;
	room->old = 0;
	room->start = 0;
	room->end = 0;
	room->name = s;
	room->room_pipe = NULL;
	room->path = 0;
	room->checked = 0;
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
		check_if_room_exist(data, (t_room *)tmp->content);
		ft_lstaddback(&data->room, tmp);
	}
	else
		bad_data = 1;
	return (bad_data ? 1 : 0);
}

void			add_new_instruction(t_data *data, char *s)
{
	t_list		*tmp;

	tmp = ft_lstnew(&data->instruction_content, sizeof(t_instruction));
	ft_lstaddback(&data->instruction, tmp);
	((t_instruction *)tmp->content)->instruction = s;
}

static int		check_if_start_or_end(t_list *inst)
{
	char	*tmp_inst;
	t_list	*tmp;
	t_list	*save;

	tmp = inst;
	while (tmp)
	{
		tmp_inst = ((t_instruction *)tmp->content)->instruction;
		if (!ft_strcmp(tmp_inst, "##start") || !ft_strcmp(tmp_inst, "##end"))
		{
			ft_lstdel(&tmp, free_instruction_content);
			save->next = NULL;
			return (1);
		}
		save = tmp;
		tmp = tmp->next;
	}
	return (0);
}

static void		merge_instruction(t_data *data, t_pipe *new_pipe,
									char *s, char *str)
{
	t_list		*pipe;

	if ((pipe = get_pipe_node(&data->pipe, s, str + 1)))
	{
		ft_lstaddback(&((t_pipe *)pipe->content)->all_instruction,
					ft_lstmap(new_pipe->instruction, copy_lst));
		new_pipe->all_instruction =
			((t_pipe *)pipe->content)->all_instruction;
		new_pipe->old = 1;
	}
	else
	{
		new_pipe->all_instruction =
			ft_lstmap(new_pipe->instruction, copy_lst);
	}
}

static int		handle_pipe_instruction(t_data *data, t_pipe *new_pipe,
										char *s, char *str)
{
	new_pipe->instruction = data->instruction;
	data->instruction = NULL;
	if (new_pipe->instruction)
	{
		if (check_if_start_or_end(new_pipe->instruction))
		{
			data->stop_get_data = 1;
			data->instruction = new_pipe->instruction;
			return (1);
		}
		else
			merge_instruction(data, new_pipe, s, str);
	}
	else
		new_pipe->all_instruction = NULL;
	return (0);
}

static void		init_room_new_pipe(t_data *data, char *str,
									t_list **new_pipe_room)
{
	t_list		*room;

	room = get_room_node_by_name(&data->room, str);
	*new_pipe_room = room;
}

static void		init_data_new_pipe(t_data *data, char *s, char *str,
									t_pipe *new_pipe)
{
	new_pipe->name = s;
	new_pipe->old = 0;
	init_room_new_pipe(data, str + 1, &new_pipe->room2);
	*str = '\0';
	init_room_new_pipe(data, s, &new_pipe->room1);
}

int				add_new_pipe(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	t_pipe		*new_pipe;
	int			bad_data;

	str = ft_strrchr(s, '-');
	tmp = ft_lstnew(&data->pipe_content, sizeof(t_pipe));
	new_pipe = (t_pipe *)tmp->content;
	init_data_new_pipe(data, s, str, new_pipe);
	bad_data = new_pipe->room1 && new_pipe->room2 ? 0 : 1;
	if (bad_data == 0)
	{
		if (handle_pipe_instruction(data, new_pipe, s, str))
			ft_memdel((void**)&tmp);
		ft_lstaddback(&data->pipe, tmp);
	}
	else
		ft_memdel((void**)&tmp);
	*str = '-';
	return (bad_data ? 1 : 0);
}

int				check_if_pipe_exist(t_room *room, t_room *new_pipe)
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

void			add_pipe_handle(t_data *data, t_room *room, t_room *new_pipe)
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
