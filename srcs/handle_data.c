/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 19:34:06 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/22 15:32:33 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		command_handle(t_data *data, char *command, char *name)
{
	int			i;

	i = -1;
	while (++i < OPTION)
	{
		if (!ft_strcmp(command, get_command(0)[i].name))
		{
			get_command(0)[i].choice(data, name);
			return ;
		}
	}
}

static void		do_room_command(t_data *data)
{
	t_list		*tmp;
	t_list		*tmp2;
	char		*str;
	char		*room;

	tmp = data->room;
	while (tmp)
	{
		if (((t_room *)tmp->content)->old != 1)
		{
			room = ((t_room *)tmp->content)->name;
			tmp2 = ((t_room *)tmp->content)->all_instruction;
			while (tmp2)
			{
				str = ((t_instruction *)tmp2->content)->instruction;
				command_handle(data, str, room);
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
}

static void		do_pipe_command(t_data *data)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_pipe		*pipe;
	char		*str;

	tmp = data->pipe;
	while (tmp)
	{
		pipe = (t_pipe *)tmp->content;
		if (pipe->old != 1)
		{
			tmp2 = pipe->all_instruction;
			while (tmp2)
			{
				str = ((t_instruction *)tmp2->content)->instruction;
				command_handle(data, str, pipe->name);
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
}

static int		check_if_start_and_end(t_list *room)
{
	t_list	*tmp;
	t_list	*start;
	t_list	*end;
	t_room	*tmp_room;

	start = NULL;
	end = NULL;
	tmp = room;
	while (tmp)
	{
		tmp_room = (t_room *)tmp->content;
		if (tmp_room->start == 1)
			start = tmp;
		if (tmp_room->end == 1)
			end = tmp;
		tmp = tmp->next;
	}
	return (!start || !end || start == end ? 0 : 1);
}

void			handle_data(t_data *data)
{
	do_room_command(data);
	do_pipe_command(data);
	if (!check_if_start_and_end(data->room))
	{
		free_all(data);
		ft_error("ERROR", 3);
	}
	find_path(data);
}
