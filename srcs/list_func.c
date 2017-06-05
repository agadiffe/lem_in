/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:37:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/05/31 19:32:30 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*get_instruction_node(t_list **alst, char *name)
{
	t_list			*tmp;

	tmp = *alst;
	while (tmp)
	{
		if (!ft_strcmp(((t_instruction*)tmp->content)->instruction, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list		*get_room_node_by_name(t_list **alst, char *name)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		if (((t_room *)tmp->content)->old != 1
				&& !ft_strcmp(((t_room *)tmp->content)->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list		*get_room_node_by_coord(t_list **alst, int x, int y)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		if (((t_room *)tmp->content)->old != 1
				&& ((t_room *)tmp->content)->x == x
				&& ((t_room *)tmp->content)->y == y)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list		*get_pipe_node(t_list **alst, char *name1, char *name2)
{
	t_list	*tmp;
	t_pipe	*tmp_pipe;
	t_room	*tmp_room1;
	t_room	*tmp_room2;

	tmp = *alst;
	while (tmp)
	{
		tmp_pipe = (t_pipe *)tmp->content;
		tmp_room1 = (t_room *)tmp_pipe->room1->content;
		tmp_room2 = (t_room *)tmp_pipe->room2->content;
		if ((!ft_strcmp(tmp_room1->name, name1)
					&& !ft_strcmp(tmp_room2->name, name2))
				|| (!ft_strcmp(tmp_room1->name, name2)
					&& !ft_strcmp(tmp_room2->name, name1)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		free_instruction_content(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_instruction *)content)->instruction);
}

void		free_room_content(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_room *)content)->name);
	ft_lstdel(&((t_room *)content)->instruction, free_instruction_content);
}

void		free_pipe_content(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_pipe *)content)->name);
	ft_lstdel(&((t_pipe *)content)->instruction, free_instruction_content);
}
