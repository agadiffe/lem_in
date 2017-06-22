/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions_lstiter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 15:59:21 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/22 15:36:03 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_inst(t_list *elem)
{
	ft_putendl(((t_instruction *)elem->content)->instruction);
}

void		print_room(t_list *elem)
{
	t_room	*tmp;

	tmp = (t_room *)elem->content;
	ft_lstiter(tmp->instruction, print_inst);
	ft_putstr(tmp->name);
	ft_putstr(" ");
	ft_putnbr(tmp->x);
	ft_putstr(" ");
	ft_putnbr_endl(tmp->y);
}

void		print_pipe(t_list *elem)
{
	t_pipe		*pipe;

	ft_lstiter(((t_pipe *)elem->content)->instruction, print_inst);
	pipe = (t_pipe *)elem->content;
	ft_putstr(((t_room *)pipe->room1->content)->name);
	ft_putstr("-");
	ft_putendl(((t_room *)pipe->room2->content)->name);
}

void		print_last_comment(t_list *elem)
{
	ft_putendl(((t_instruction *)elem->content)->instruction);
}
