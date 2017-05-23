/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:39:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/05/23 19:06:23 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			add_new_room(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	int			bad_data;

	bad_data = 0;
	if (*s != 'L')
	{
		tmp = ft_lstnew(&data->room_content, sizeof(t_room));
		ft_lstaddback(&data->room, tmp);
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
	int			bad_data;

	str = ft_strrchr(s, '-');
	tmp = ft_lstnew(&data->pipe_content, sizeof(t_pipe));
	((t_pipe *)tmp->content)->name = s;
	tmp_room = get_room_node(&data->room, str + 1, "");
	((t_pipe *)tmp->content)->room2 = tmp_room;
	*str = '\0';
	tmp_room = get_room_node(&data->room, s, "");
	((t_pipe *)tmp->content)->room1 = tmp_room;
	*str = '-';
	bad_data = ((t_pipe *)tmp->content)->room1
					&& ((t_pipe *)tmp->content)->room2 ? 0 : 1;
	if (bad_data == 0)
	{
		ft_lstaddback(&data->pipe, tmp);
		((t_pipe *)tmp->content)->instruction = data->instruction;
		data->instruction = NULL;
	}
	else
		ft_memdel((void**)&tmp);
	return (bad_data ? 1 : 0);
}

#include <stdio.h>

void		print_t_room_pipe(t_room *room)
{
	t_list	*tmp;

	ft_putendl("---------");
	tmp = room->room_pipe;
	while (tmp)
	{
		ft_putendl(((t_room_pipe *)tmp->content)->room->name);
		tmp = tmp->next;
	}
	ft_putendl("---------");
}

int			check_if_pipe_exist(t_room *room, t_room *new_pipe)
{
	t_list	*tmp;

	print_t_room_pipe(room);
	tmp = room->room_pipe;
	printf("check function room1(%s): %p\n", room->name, room);
	printf("check function room2(%s): %p\n", new_pipe->name, new_pipe);
	ft_putendl("      |-> check if pipe");
	while (tmp)
	{
		ft_putendl("t_room_pipe not empty");
		printf("room(%s) :    %p\n",
				((t_room_pipe *)tmp->content)->room->name,
				((t_room_pipe *)tmp->content)->room);
		printf("new_pipe(%s): %p\n", new_pipe->name, new_pipe);
		if (((t_room_pipe *)tmp->content)->room == new_pipe)
		{
			ft_putendl("duplicate");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		add_pipe_to_room_list(t_data *data)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_pipe	*pipe;
	t_room	*room1;
	t_room	*room2;

	tmp = data->pipe;
	while (tmp)
	{
		pipe = (t_pipe *)tmp->content;
		room1 = (t_room *)pipe->room1->content;
		room2 = (t_room *)pipe->room2->content;
		printf("original room1(%s): %p\n", room1->name, room1);
		printf("original room2(%s): %p\n", room2->name, room2);
		if (!check_if_pipe_exist(room1, room2))
		{
			ft_putendl("add pipe to room1");
			tmp2 = ft_lstnew(&data->room_pipe_content, sizeof(t_room_pipe));
			((t_room_pipe *)tmp2->content)->room = room2;
			ft_lstaddback(&room1->room_pipe, tmp2);
		}
		if (!check_if_pipe_exist(room2, room1))
		{
			ft_putendl("add pipe to room2");
			tmp2 = ft_lstnew(&data->room_pipe_content, sizeof(t_room_pipe));
			((t_room_pipe *)tmp2->content)->room = room1;
			ft_lstaddback(&room2->room_pipe, tmp2);
		}
		tmp = tmp->next;
	}
}
