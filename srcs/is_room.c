/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:43:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/14 17:47:54 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_if_coord_at_end(char *name, int *len)
{
	int		coord;
	int		i;

	coord = 0;
	while (*len && coord != 2)
	{
		i = 0;
		while (*len && name[*len] != ' ')
		{
			(*len)--;
			i++;
		}
		if (*len && ft_strnisnumber(name + *len + 1, i))
		{
			coord++;
			(*len)--;
		}
		else
			return (0);
	}
	return (coord == 2 ? 1 : 0);
}

int			is_room(char *name)
{
	int		len;
	int		ret;
	int		save;

	ret = 1;
	if ((len = ft_strlen(name) - 1) < 1)
		ret = 0;
	ret = check_if_coord_at_end(name, &len);
	save = len;
	while (ret && len > -1)
	{
		if (name[len] != '-')
			len--;
		else
			ret = 0;
	}
	len = save;
	while (len > -1 && (name[len] == ' ' || name[len] == '\t'))
		len--;
	if (len < 0)
		ret = 0;
	return (ret);
}
