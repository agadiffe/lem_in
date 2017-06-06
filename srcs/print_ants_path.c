/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 20:22:13 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/06 21:20:23 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_ants_path(t_data *data)
{
	t_list	*new;
	t_list	*path;
	t_list	*tmp;

	tmp = get_end_room(&data->room);
	if (((t_room *)tmp->content)->path == 0)
		ft_error("ERROR", 2);
	new = ft_lstnew(&data->room_pipe_content, sizeof(t_room_pipe));
	((t_room_pipe *)new->content)->room = tmp->content;
	ft_lstadd(&path, new);
	tmp = ((t_room *)tmp->content)->room_pipe;
	while (((t_room_pipe *)tmp->content)->room->path != 0)
	{
	}
}
