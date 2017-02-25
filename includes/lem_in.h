/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:06:15 by agadiffe          #+#    #+#             */
/*   Updated: 2017/02/25 18:45:26 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stddef.h>
# include "libft.h"

# define OPTION		2

typedef struct		s_instruction
{
	char			*instruction;
}					t_instruction;

typedef struct		s_room
{
	int				start;
	int				end;
	int				x;
	int				y;
	int				room_number;
	char			*name;
	t_list			*instruction;
}					t_room;

typedef struct		s_pipe
{
	t_list			*room1;
	t_list			*room2;
	t_list			*instruction;
}					t_pipe;

typedef struct		s_data
{
	int				ants;
	int				get_room_data;
	int				nbr_room;
	t_room			room_content;
	t_pipe			pipe_content;
	t_instruction	instruction_content;
	t_list			*room;
	t_list			*pipe;
	t_list			*instruction;
}					t_data;

typedef struct		s_command
{
	void			(*choice)(t_data *, char *);
	char			*name;
}					t_command;

/*
**	print_map.c
*/
void				print_map(t_data *data);

#endif
