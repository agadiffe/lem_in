/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 13:31:11 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/15 16:00:23 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		check_if_command_after_pipe(t_data *data)
{
	t_list	*tmp;
	t_list	*last_node;
	char	*str;

	if (data->instruction)
	{
		tmp = data->instruction;
		while (tmp)
		{
			str = ((t_instruction *)tmp->content)->instruction;
			if (*(str + 1) == '#')
			{
				ft_lstdel(&tmp, free_instruction_content);
				last_node->next = NULL;
				return ;
			}
			last_node = tmp;
			tmp = tmp->next;
		}
	}
}

void			print_map(t_data *data)
{
	check_if_command_after_pipe(data);
	ft_putnbr_endl(data->ants);
	ft_lstiter(data->room, print_room);
	ft_lstiter(data->pipe, print_pipe);
	if (data->instruction)
		ft_lstiter(data->instruction, print_last_comment);
	ft_putendl("");
}
