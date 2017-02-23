/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:06:15 by agadiffe          #+#    #+#             */
/*   Updated: 2017/02/23 19:26:57 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define OPTION		2

typedef struct		s_map_pipe
{
	char				*name1;
	char				*name2;
	struct s_map_pipe	*next;
}					t_map_pipe;

typedef struct		s_room_command
{
	char					*command;
	struct s_room_command	*next;
}					t_room_command;

typedef struct		s_map_room
{
	int					start;
	int					end;
	int					x;
	int					y;
	char				*name;
	t_room_command		*command;
	struct s_map_room	*next;
}					t_map_room;

#endif
