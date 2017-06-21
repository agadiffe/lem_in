/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:19:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/21 16:31:11 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		get_ants_number(t_data *data)
{
	char	*line;
	int		ants;

	line = NULL;
	ants = 0;
	ft_get_next_line(0, &line);
	ants = ft_atoi_lemin(line, data);
	ft_strdel(&line);
	return (ants > 0 ? ants : 0);
}

static void		add_new_instruction(t_data *data, char *s)
{
	t_list		*tmp;

	tmp = ft_lstnew(&data->instruction_content, sizeof(t_instruction));
	ft_lstaddback(&data->instruction, tmp);
	((t_instruction *)tmp->content)->instruction = s;
}

static int		get_data(t_data *data, char *s)
{
	int		bad_data;

	bad_data = 0;
	if (*s != '#' && data->get_room_data && !is_room(s))
		data->get_room_data = 0;
	if (*s == '#')
		add_new_instruction(data, s);
	else if (data->get_room_data)
		bad_data = add_new_room(data, s);
	else if (ft_strrchr(s, '-'))
		bad_data = add_new_pipe(data, s);
	else
		bad_data = 1;
	return (bad_data ? 1 : 0);
}

void			init_data(t_data *data)
{
	data->get_room_data = 1;
	data->stop_get_data = 0;
	data->ants = get_ants_number(data);
	data->room = NULL;
	data->pipe = NULL;
	data->instruction = NULL;
	data->path = NULL;
}

int				main(int ac, char **av)
{
	char		*line;
	t_data		data;

	(void)ac;
	(void)av;
	init_data(&data);
	if (data.ants == 0)
		ft_error("ERROR", 1);
	while (ft_get_next_line(0, &line) > 0)
	{
		if (data.stop_get_data)
			ft_strdel(&line);
		else if (get_data(&data, line))
			data.stop_get_data = 1;
	}
	add_pipe_to_room_list(&data);
	handle_data(&data);
	print_map(&data);
	print_ants_path(&data);
	free_all(&data);
	return (0);
}
