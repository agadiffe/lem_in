/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:19:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/05 18:42:55 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_ants_number(void)
{
	char	*line;
	int		ants;

	line = NULL;
	ants = 0;
	ft_get_next_line(0, &line);
	if (ft_strisnumber(line))
		ants = ft_atoi(line);
	ft_strdel(&line);
	return (ants > 0 ? ants : 0);
}

int			get_data(t_data *data, char *s)
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

void		init_data(t_data *data)
{
	data->get_room_data = 1;
	data->ants = get_ants_number();
	data->room = NULL;
	data->pipe = NULL;
	data->instruction = NULL;
}

int			main(int ac, char **av)
{
	char		*line;
	t_data		data;
	int			stop_get_data;

	(void)ac;
	(void)av;
	stop_get_data = 0;
	init_data(&data);
	if (data.ants == 0)
		ft_error("ERROR", 1);
	while (!stop_get_data && ft_get_next_line(0, &line) > 0)
	{
		if (get_data(&data, line))
			stop_get_data = 1;
	}
	add_pipe_to_room_list(&data);
	handle_data(&data);
	print_map(&data);
	return (0);
}
