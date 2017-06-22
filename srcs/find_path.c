/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:23:34 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/22 20:41:34 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*get_lower_path(t_list **room_pipe)
{
	t_list			*tmp;
	t_list			*lower;
	t_room_pipe		*pipe;
	int				path;
	int				tmp_path;

	tmp = *room_pipe;
	path = ((t_room_pipe *)tmp->content)->room->path;
	lower = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		pipe = (t_room_pipe *)tmp->content;
		if (pipe->room->old != 1)
		{
			tmp_path = pipe->room->path;
			if (tmp_path < path)
			{
				path = tmp_path;
				lower = tmp;
			}
		}
		tmp = tmp->next;
	}
	return (lower);
}

static t_list	*add_path(t_data *data, t_list *pipe_list)
{
	t_list	*tmp;
	t_list	*new;

	tmp = get_lower_path(&pipe_list);
	new = ft_lstnew(&data->room_pipe_content, sizeof(t_room_pipe));
	((t_room_pipe *)new->content)->room = ((t_room_pipe *)tmp->content)->room;
	ft_lstadd(&data->path, new);
	return (tmp);
}

static int		create_shorter_path_list(t_data *data)
{
	t_list			*tmp;
	t_list			*new;
	t_room_pipe		*pipe;

	tmp = get_end_room(&data->room);
	if (((t_room *)tmp->content)->path == 0)
		return (0);
	new = ft_lstnew(&data->room_pipe_content, sizeof(t_room_pipe));
	((t_room_pipe *)new->content)->room = (t_room *)tmp->content;
	ft_lstadd(&data->path, new);
	tmp = add_path(data, ((t_room *)tmp->content)->room_pipe);
	pipe = (t_room_pipe *)tmp->content;
	while (pipe->room->start != 1)
	{
		tmp = add_path(data, pipe->room->room_pipe);
		pipe = (t_room_pipe *)tmp->content;
	}
	return (1);
}

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
		if (tmp2->room->checked == 0 || tmp2->room->end)
		{
			if (tmp2->room->end && tmp2->room->checked)
			{
				if (tmp->room->path + 1 < tmp2->room->path)
					tmp2->room->path = tmp->room->path + 1;
			}
			else
			{
				tmp2->room->checked = 1;
				tmp2->room->path = tmp->room->path + 1;
			}
			if (tmp2->room->end != 1)
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
	if ((tmp = ((t_room *)start->content)->room_pipe))
		ft_lstiter(tmp, handle_path);
	ft_lstiter(data->room, print_room);
	ft_lstiter(data->pipe, print_pipe);
	if (!create_shorter_path_list(data))
	{
		free_all(data);
		ft_error("ERROR", 2);
	}
}
