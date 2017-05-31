/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 19:34:06 by agadiffe          #+#    #+#             */
/*   Updated: 2017/05/31 20:35:23 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		do_room_command(t_data *data)
{
	t_list		*tmp;
	t_list		*tmp2;
	char		*str;
	char		*room;
	int			i;

	tmp = data->room;
	while (tmp)
	{
		if (((t_room *)tmp->content)->old != 1)
		{
			room = ((t_room *)tmp->content)->name;
			tmp2 = ((t_room *)tmp->content)->instruction;
			while (tmp2)
			{
				str = ((t_instruction *)tmp2->content)->instruction;
				i = -1;
				while (++i < OPTION)
				{
					if (!ft_strcmp(str, get_command(0)[i].name))
						get_command(0)[i].choice(data, room, "");
				}
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
	char		*str;
	char		*pipe;
	int			i;

	tmp = data->pipe;
	while (tmp)
	{
		if (((t_pipe *)tmp->content)->old != 1)
		{
			pipe = ((t_pipe *)tmp->content)->name;
			tmp2 = ((t_pipe *)tmp->content)->instruction;
			while (tmp2)
			{
				str = ((t_instruction *)tmp2->content)->instruction;
				if (!ft_strcmp(str, "##start") || !ft_strcmp(str, "##end"))
				{
					//free everything
					ft_error("ERROR", 2);
				}
				i = -1;
				while (++i < OPTION)
				{
					if (!ft_strcmp(str, get_command(0)[i].name))
						get_command(0)[i].choice(data, pipe, "");
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
}

void			handle_data(t_data *data)
{
	do_room_command(data);
	do_pipe_command(data);
}
