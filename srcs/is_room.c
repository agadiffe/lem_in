/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:43:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/03/02 22:47:11 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_room(char *name)
{
	int		len;
	int		ret;
	int		coord;
	int		i;

	ret = 1;
	coord = 0;
	if ((len = ft_strlen(name) - 1) < 1)
		ret = 0;
	while (len && ret && coord != 2)
	{
		i = 0;
		while (len && name[len] != ' ')
		{
			len--;
			i++;
		}
		if (len && ft_strnisnumber(name + len + 1, i))
		{
			coord++;
			len--;
		}
		else
			ret = 0;
	}
	i = len;
	while (ret && len > -1)
	{
		if (name[len] != '-')
			len--;
		else
			ret = 0;
	}
	len = i;
	while (len > -1 && (name[len] == ' ' || name[len] == '\t'))
		len--;
	if (len < 0)
		ret = 0;
	return (ret);
}
