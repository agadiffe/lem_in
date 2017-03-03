/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:37:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/03/03 18:26:05 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*get_instruction_node(t_list **alst, char *name1, char *name2)
{
	t_list	*tmp;

	(void)name2;
	tmp = *alst;
	while (tmp && ft_strcmp(((t_instruction *)tmp->content)->name, name1))
		tmp = tmp->next;
	return (tmp);
}

t_list		*get_room_node(t_list **alst, char *name1, char *name2)
{
	t_list	*tmp;

	(void)name2;
	tmp = *alst;
	while (tmp && ft_strcmp(((t_room *)tmp->content)->name, name1))
		tmp = tmp->next;
	return (tmp);
}

t_list		*get_pipe_node(t_list **alst, char *name1, char *name2)
{
	t_list	*tmp;
	t_pipe	*tmp_pipe;
	t_room	*tmp_room1;
	t_room	*tmp_room2;

	tmp = *alst;
	tmp_pipe = (t_pipe *)tmp->content;
	tmp_room1 = (t_room *)tmp_pipe->room1->content;
	tmp_room2 = (t_room *)tmp_pipe->room2->content;
	while (tmp && ((ft_strcmp(tmp_room1->name, name1)
					&& ft_strcmp(tmp_room2->name, name2))
				|| (ft_strcmp(tmp_room1->name, name2)
					&& ft_strcmp(tmp_room2->name, name1))))
		tmp = tmp->next;
	return (tmp);
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
	ft_lstdel(&((t_pipe *)content)->instruction, free_instruction_content);
}

void		delete_node(t_list **alst, char *room1, char *room2)
{
	t_list	*node_to_del;

	node_to_del = get_room_node(alst, room1, room2);
	ft_lstdelnode(alst, &node_to_del, free_room_content);
}
