/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:41:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/04/06 21:14:55 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static void		command_start(t_data *data, char *room1, char *room2)
{
	t_list	*tmp;
	t_list	*tmp_room;

	tmp = data->room;
	while (tmp)
	{
		((t_room *)tmp->content)->start = 0;
		tmp = tmp->next;
	}
	tmp_room = get_room_node(&data->room, room1, room2);
	((t_room *)tmp_room->content)->start = 1;
}

static void		command_end(t_data *data, char *room1, char *room2)
{
	t_list	*tmp;
	t_list	*tmp_room;

	tmp = data->room;
	while (tmp)
	{
		((t_room *)tmp->content)->end = 0;
		tmp = tmp->next;
	}
	tmp_room = get_room_node(&data->room, room1, room2);
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
