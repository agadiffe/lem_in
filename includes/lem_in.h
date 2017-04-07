/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:06:15 by agadiffe          #+#    #+#             */
/*   Updated: 2017/04/07 20:00:25 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stddef.h>
# include "libft.h"

# define OPTION			2

# define ROOM			0
# define PIPE			1

typedef struct		s_instruction
{
	char			*instruction;
}					t_instruction;

typedef struct		s_room
{
	int				old;
	int				start;
	int				end;
	int				x;
	int				y;
	int				room_number;
	char			*name;
	t_list			*instruction;
	t_list			*room_pipe;
}					t_room;

typedef struct		s_pipe
{
	char			*name;
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
	void			(*choice)(t_data *, char *, char *);
	char			*name;
}					t_command;

/*
**	add_node.c.c
*/
int					add_new_room(t_data *data, char *s);
void				add_new_instruction(t_data *data, char *s);
int					add_new_pipe(t_data *data, char *s);

/*
**	command.c
*/
t_command			*get_command(int to_free);

/*
**	is_room.c
*/
int					is_room(char *name);

/*
**	list_func.c
*/
t_list				*get_room_node(t_list **alst, char *name1, char *name2);
t_list				*get_pipe_node(t_list **alst, char *name1, char *name2);
t_list				*get_instruction_node(t_list **alst, char *name1,
											char *name2);
void				delete_node(t_list **alst, char *room1, char *room2,
								int choice);

/*
**	print_map.c
*/
void				print_map(t_data *data);

/*
**	handle_data.c
*/
void				handle_data(t_data *data);

#endif
