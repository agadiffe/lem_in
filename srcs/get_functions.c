/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:37:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/15 16:54:53 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*get_end_room(t_list **alst)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		if (((t_room *)tmp->content)->end == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list		*get_start_room(t_list **alst)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		if (((t_room *)tmp->content)->start == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list		*get_room_node_by_name(t_list **alst, char *name)
{
	t_list	*tmp;
	t_room	*room;

	tmp = *alst;
	while (tmp)
	{
		room = (t_room *)tmp->content;
		if (room->old != 1 && !ft_strcmp(room->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list		*get_room_node_by_coord(t_list **alst, int x, int y)
{
	t_list	*tmp;
	t_room	*room;

	tmp = *alst;
	while (tmp)
	{
		room = (t_room *)tmp->content;
		if (room->old != 1 && room->x == x && room->y == y)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list		*get_pipe_node(t_list **alst, char *name1, char *name2)
{
	t_list	*tmp;
	t_pipe	*pipe;
	char	*room1;
	char	*room2;

	tmp = *alst;
	while (tmp)
	{
		pipe = (t_pipe *)tmp->content;
		room1 = ((t_room *)pipe->room1->content)->name;
		room2 = ((t_room *)pipe->room2->content)->name;
		if ((!ft_strcmp(room1, name1) && !ft_strcmp(room2, name2))
				|| (!ft_strcmp(room1, name2) && !ft_strcmp(room2, name1)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
