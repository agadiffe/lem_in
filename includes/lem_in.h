/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:06:15 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/06 20:27:53 by agadiffe         ###   ########.fr       */
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
	int				path;
	int				checked;
	int				old;
	int				start;
	int				end;
	int				x;
	int				y;
	char			*name;
	t_list			*instruction;
	t_list			*all_instruction;
	t_list			*room_pipe;
}					t_room;

typedef struct		s_room_pipe
{
	t_room			*room;
}					t_room_pipe;

typedef struct		s_pipe
{
	int				old;
	char			*name;
	t_list			*room1;
	t_list			*room2;
	t_list			*instruction;
	t_list			*all_instruction;
}					t_pipe;

typedef struct		s_data
{
	int				ants;
	int				get_room_data;
	int				stop_get_data;
	t_room			room_content;
	t_pipe			pipe_content;
	t_instruction	instruction_content;
	t_room_pipe		room_pipe_content;
	t_list			*room;
	t_list			*pipe;
	t_list			*instruction;
	t_list			*path;
}					t_data;

typedef struct		s_command
{
	void			(*choice)(t_data *, char *);
	char			*name;
}					t_command;

/*
**	add_node.c.c
*/
int					add_new_room(t_data *data, char *s);
void				add_new_instruction(t_data *data, char *s);
int					add_new_pipe(t_data *data, char *s);
void				add_pipe_to_room_list(t_data *data);

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
t_list				*get_end_room(t_list **alst);
t_list				*get_start_room(t_list **alst);
t_list				*get_room_node_by_name(t_list **alst, char *name);
t_list				*get_room_node_by_coord(t_list **alst, int x, int y);
t_list				*get_pipe_node(t_list **alst, char *name1, char *name2);
t_list				*get_instruction_node(t_list **alst, char *name);
void				free_instruction_content(void *content,
											size_t content_size);
void				free_room_content(void *content, size_t content_size);
void				free_pipe_content(void *content, size_t content_size);

/*
**	print_map.c
*/
void				print_map(t_data *data);

/*
**	handle_data.c
*/
void				handle_data(t_data *data);

/*
**	find_path.c
*/
void				find_path(t_data *data);
void				create_shorter_path_list(t_data *data);

/*
**	print_ants_path.c
*/
void				print_ants_path(t_data *data);

#endif
