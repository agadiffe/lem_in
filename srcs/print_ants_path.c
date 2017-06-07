/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 20:22:13 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/07 18:17:52 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print(t_list *elem)
{
	ft_putendl(((t_room_pipe *)elem->content)->room->name);
}

void			print_ants_path(t_data *data)
{
	ft_lstiter(data->path, print);
}
