/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:37:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/03/02 22:40:11 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*get_room_node(t_list **alst, char *name)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp && ft_strcmp(((t_room *)tmp->content)->name, name))
		tmp = tmp->next;
	return (tmp);
}

/*
void		free_pipe_content(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
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

void		delete_pipe_node(t_list **alst, char *name)
{
	t_list	*node_to_del;

	node_to_del = get_pipe_node(alst, name);
	ft_lstdelnode(alst, &node_to_del, free_room_content);
}

void		delete_room_node(t_list **alst, char *name)
{
	t_list	*node_to_del;

	node_to_del = get_room_node(alst, name);
	ft_lstdelnode(alst, &node_to_del, free_room_content);
}

void		delete_instruction_node(t_list **alst, char *name)
{
	t_list	*node_to_del;

	node_to_del = get_instruction_node(alst, name);
	ft_lstdelnode(alst, &node_to_del, free_instruction_content);
}
*/
