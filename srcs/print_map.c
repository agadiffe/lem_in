/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:31:11 by agadiffe          #+#    #+#             */
/*   Updated: 2017/02/25 16:26:35 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_room(t_data *data)
{
	t_list		*tmp;
	t_list		*tmp2;

	tmp = data->room;
	while (tmp)
	{
		tmp2 = ((t_room *)tmp->content)->instruction;
		while (tmp2)
		{
			ft_putendl(((t_instruction *)tmp2->content)->instruction);
			tmp2 = tmp2->next;
		}
		ft_putstr(((t_room *)tmp->content)->name);
		ft_putstr(" ");
		ft_putnbr(((t_room *)tmp->content)->x);
		ft_putstr(" ");
		ft_putnbr_endl(((t_room *)tmp->content)->y);
		tmp = tmp->next;
	}
}

static void		print_pipe(t_data *data)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_pipe		*pipe;

	tmp = data->pipe;
	while (tmp)
	{
		tmp2 = ((t_pipe *)tmp->content)->instruction;
		while (tmp2)
		{
			ft_putendl(((t_instruction *)tmp2->content)->instruction);
			tmp2 = tmp2->next;
		}
		pipe = (t_pipe *)tmp->content;
		ft_putstr(((t_room *)pipe->room1->content)->name);
		ft_putstr("-");
		ft_putendl(((t_room *)pipe->room2->content)->name);
		tmp = tmp->next;
	}
}

void			print_map(t_data *data)
{
	ft_putnbr_endl(data->ants);
	print_room(data);
	print_pipe(data);
}
