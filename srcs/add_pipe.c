/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:39:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/15 18:46:02 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_if_start_or_end(t_list *inst)
{
	char	*tmp_inst;
	t_list	*tmp;
	t_list	*save;

	tmp = inst;
	while (tmp)
	{
		tmp_inst = ((t_instruction *)tmp->content)->instruction;
		if (!ft_strcmp(tmp_inst, "##start") || !ft_strcmp(tmp_inst, "##end"))
		{
			ft_lstdel(&tmp, free_instruction_content);
			save->next = NULL;
			return (1);
		}
		save = tmp;
		tmp = tmp->next;
	}
	return (0);
}

static void		merge_instruction(t_data *data, t_pipe *new_pipe,
									char *s, char *str)
{
	t_list		*pipe;

	if ((pipe = get_pipe_node(&data->pipe, s, str + 1)))
	{
		ft_lstaddback(&((t_pipe *)pipe->content)->all_instruction,
					ft_lstmap(new_pipe->instruction, copy_lst));
		new_pipe->all_instruction =
			((t_pipe *)pipe->content)->all_instruction;
		new_pipe->old = 1;
	}
	else
	{
		new_pipe->all_instruction =
			ft_lstmap(new_pipe->instruction, copy_lst);
	}
}

static int		handle_pipe_instruction(t_data *data, t_pipe *new_pipe,
										char *s, char *str)
{
	new_pipe->instruction = data->instruction;
	data->instruction = NULL;
	if (new_pipe->instruction)
	{
		if (check_if_start_or_end(new_pipe->instruction))
		{
			data->stop_get_data = 1;
			data->instruction = new_pipe->instruction;
			return (1);
		}
		else
			merge_instruction(data, new_pipe, s, str);
	}
	else
		new_pipe->all_instruction = NULL;
	return (0);
}

static void		init_data_new_pipe(t_data *data, char *s, char *str,
									t_pipe *new_pipe)
{
	t_list		*room;

	new_pipe->name = s;
	new_pipe->old = 0;
	room = get_room_node_by_name(&data->room, str + 1);
	new_pipe->room2 = room;
	*str = '\0';
	room = get_room_node_by_name(&data->room, s);
	new_pipe->room1 = room;
}

int				add_new_pipe(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	t_pipe		*new_pipe;
	int			bad_data;

	str = ft_strrchr(s, '-');
	tmp = ft_lstnew(&data->pipe_content, sizeof(t_pipe));
	new_pipe = (t_pipe *)tmp->content;
	init_data_new_pipe(data, s, str, new_pipe);
	bad_data = new_pipe->room1 && new_pipe->room2 ? 0 : 1;
	if (bad_data || handle_pipe_instruction(data, new_pipe, s, str))
	{
		ft_strdel(&s);
		ft_memdel((void**)&tmp);
	}
	else
	{
		ft_lstaddback(&data->pipe, tmp);
		*str = '-';
	}
	return (bad_data ? 1 : 0);
}
