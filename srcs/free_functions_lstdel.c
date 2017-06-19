/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_lstdel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 16:14:52 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/15 16:15:25 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_node(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
}

void			free_all(t_data *data)
{
	ft_lstdel(&data->room, free_room_content);
	ft_lstdel(&data->pipe, free_pipe_content);
	ft_lstdel(&data->instruction, free_instruction_content);
	ft_lstdel(&data->path, free_node);
	get_command(1);
}

void			free_instruction_content(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_instruction *)content)->instruction);
}

void			free_room_content(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_room *)content)->name);
	ft_lstdel(&((t_room *)content)->instruction, free_instruction_content);
	if (((t_room *)content)->old == 0)
		ft_lstdel(&((t_room *)content)->all_instruction, free_instruction_content);
	ft_lstdel(&((t_room *)content)->room_pipe, free_node);
}

void			free_pipe_content(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_pipe *)content)->name);
	ft_lstdel(&((t_pipe *)content)->instruction, free_instruction_content);
	if (((t_pipe *)content)->old == 0)
		ft_lstdel(&((t_pipe *)content)->all_instruction, free_instruction_content);
}
