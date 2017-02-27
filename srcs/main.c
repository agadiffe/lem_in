/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:19:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/02/27 18:55:27 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>
#include <stdlib.h>

t_list		*get_room_node(t_list **alst, char *name)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp && ft_strcmp(((t_room *)tmp->content)->name, name))
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

void		delete_room_node(t_list **alst, char *name)
{
	t_list	*node_to_del;
	t_list	*tmp;

	node_to_del = get_room_node(alst, name);
	if (*alst == node_to_del)
	{
		*alst = (*alst)->next;
	}
	else
	{
		tmp = *alst;
		while (tmp->next != node_to_del)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
	}
	ft_lstdelone(&node_to_del, free_room_content);
}

void		delete_instruction_node(t_list **alst, char *name)
{
	(void)alst;
	(void)name;
}

void		command_start(t_data *data, char *s)
{
	t_list	*tmp;
	t_list	*tmp_room;

	tmp = data->room;
	while (tmp)
	{
		((t_room *)tmp->content)->start = 0;
		tmp = tmp->next;
	}
	tmp_room = get_room_node(&data->room, s);
	((t_room *)tmp_room->content)->start = 1;
}

void		command_end(t_data *data, char *s)
{
	t_list	*tmp;
	t_list	*tmp_room;

	tmp = data->room;
	while (tmp)
	{
		((t_room *)tmp->content)->end = 0;
		tmp = tmp->next;
	}
	tmp_room = get_room_node(&data->room, s);
	((t_room *)tmp_room->content)->end = 1;
}

t_command	*get_command(int to_free)
{
	static t_command	*type;

	if (!type)
	{
		if ((type = (t_command *)malloc(sizeof(t_command) * OPTION)))
		{
			type[0] = (t_command){ &command_start, "##start" };
			type[1] = (t_command){ &command_end, "##end" };
		}
		else
			ft_error("Malloc error", 2);
	}
	if (to_free)
		free(type);
	return (type);
}

int			get_ants_number(void)
{
	char	*line;
	int		ants;

	ants = 0;
	ft_get_next_line(0, &line);
	if (ft_strisnumber(line))
		ants = ft_atoi(line);
	ft_strdel(&line);
	return (ants > 0 ? ants : 0);
}

int			add_new_room(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	int			bad_data;

	bad_data = 0;
	//fail room if != "name x y" with x&y int
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
	// detect if command start or end and fill data->start & end
	// check if previous node have start or end
	// check if duplicate command / comment ??
	if (data->instruction)
	{
		((t_room *)tmp->content)->instruction = data->instruction;
		data->instruction = NULL;
	}
	else
		((t_room *)tmp->content)->instruction = NULL;
	return (bad_data ? 1 : 0);
}

void		add_new_instruction(t_data *data, char *s)
{
	t_list		*tmp;

	tmp = ft_lstnew(&data->instruction_content, sizeof(t_instruction));
	ft_lstaddback(&data->instruction, tmp);
	((t_instruction *)tmp->content)->instruction = ft_strdup(s);
}

int			fill_room(t_data *data, char *s)
{
	int		bad_data;

	bad_data = 0;
	if (*s != '#')
		bad_data = add_new_room(data, s);
	else
		add_new_instruction(data, s);
	return (bad_data ? 1 : 0);
}

int			add_new_pipe(t_data *data, char *s)
{
	char		*str;
	t_list		*tmp;
	t_list		*tmp_room;
	int			bad_data;

	bad_data = 0;
	if ((str = ft_strrchr(s, '-')))
	{
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
			if (data->instruction)
			{
				((t_pipe *)tmp->content)->instruction = data->instruction;
				data->instruction = NULL;
			}
			else
				((t_pipe *)tmp->content)->instruction = NULL;
		}
		else
			ft_memdel((void**)&tmp);
	}
	return (bad_data ? 1 : 0);
}

int			fill_pipe(t_data *data, char *s)
{
	int		bad_data;

	bad_data = 0;
	if (*s != '#')
		bad_data = add_new_pipe(data, s);
	else
		add_new_instruction(data, s);
	return (bad_data ? 1 : 0);
}

int			get_data(t_data *data, char *s)
{
	int		bad_data;

	bad_data = 0;
	if (*s != '#' && ft_strchr(s, '-') != NULL && data->get_room_data)
		data->get_room_data = 0;
	if (data->get_room_data)
		bad_data = fill_room(data, s);
	else
		bad_data = fill_pipe(data, s);
	return (bad_data ? 1 : 0);
}

void		handle_data(t_data *data)
{
	(void)data;
}

int			main(int ac, char **av)
{
	char		*line;
	t_data		data;
	int			stop_get_data;

	(void)ac;
	(void)av;
	stop_get_data = 0;
	data.get_room_data = 1;
	data.nbr_room = 0;
	data.ants = get_ants_number();
	data.room = NULL;
	data.pipe = NULL;
	data.instruction = NULL;
	if (data.ants == 0)
		ft_error("ERROR", 1);
	while (ft_get_next_line(0, &line) > 0 && !stop_get_data)
	{
		if (get_data(&data, line))
			stop_get_data = 1;
		ft_strdel(&line);
	}
	handle_data(&data);
	print_map(&data);
	return (0);
}
