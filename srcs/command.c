/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:41:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/02 17:21:07 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static void		reset_start_room(t_list *elem)
{
	((t_room *)elem->content)->start = 0;
}

static void		command_start(t_data *data, char *room)
{
	t_list	*tmp_room;

	ft_lstiter(data->room, reset_start_room);
	tmp_room = get_room_node_by_name(&data->room, room);
	((t_room *)tmp_room->content)->start = 1;
}

static void		reset_end_room(t_list *elem)
{
	((t_room *)elem->content)->end = 0;
}

static void		command_end(t_data *data, char *room)
{
	t_list	*tmp_room;

	ft_lstiter(data->room, reset_end_room);
	tmp_room = get_room_node_by_name(&data->room, room);
	((t_room *)tmp_room->content)->end = 1;
}

t_command		*get_command(int to_free)
{
	static t_command	*type;

	if (!type)
	{
		if ((type = (t_command *)malloc(sizeof(t_command) * OPTION)))
		{
			type[0] = (t_command){ &command_start, "##start" };
			type[1] = (t_command){ &command_end, "##end" };
		}
		else
			ft_error("Malloc error", 2);
	}
	if (to_free)
		free(type);
	return (type);
}
