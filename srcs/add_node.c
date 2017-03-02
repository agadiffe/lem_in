/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:39:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/03/02 22:42:11 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			add_new_room(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	int			bad_data;

	bad_data = 0;
	if (*s != 'L')
	{
		tmp = ft_lstnew(&data->room_content, sizeof(t_room));
		ft_lstaddback(&data->room, tmp);
		str = ft_strrchr(s, ' ');
		((t_room *)tmp->content)->y = ft_atoi(str);
		*str = '\0';
		str = ft_strrchr(s, ' ');
		((t_room *)tmp->content)->x = ft_atoi(str);
		*str = '\0';
		((t_room *)tmp->content)->name = ft_strdup(s);
		((t_room *)tmp->content)->room_number = data->nbr_room++;
		((t_room *)tmp->content)->instruction = data->instruction;
		data->instruction = NULL;
	}
	else
		bad_data = 1;
	return (bad_data ? 1 : 0);
}

void		add_new_instruction(t_data *data, char *s)
{
	t_list		*tmp;

	tmp = ft_lstnew(&data->instruction_content, sizeof(t_instruction));
	ft_lstaddback(&data->instruction, tmp);
	((t_instruction *)tmp->content)->instruction = ft_strdup(s);
}

int			add_new_pipe(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	t_list		*tmp_room;
	int			bad_data;

	bad_data = 0;
	str = ft_strrchr(s, '-');
	tmp = ft_lstnew(&data->pipe_content, sizeof(t_pipe));
	if ((tmp_room = get_room_node(&data->room, str + 1)) == NULL)
		bad_data = 1;
	((t_pipe *)tmp->content)->room2 = tmp_room;
	*str = '\0';
	if ((tmp_room = get_room_node(&data->room, s)) == NULL)
		bad_data = 1;
	((t_pipe *)tmp->content)->room1 = tmp_room;
	if (bad_data == 0)
	{
		ft_lstaddback(&data->pipe, tmp);
		((t_room *)tmp->content)->instruction = data->instruction;
		data->instruction = NULL;
	}
	else
		ft_memdel((void**)&tmp);
	return (bad_data ? 1 : 0);
}
