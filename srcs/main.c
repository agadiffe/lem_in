/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:19:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/02/23 18:19:02 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <unistd.h>

int		check_if_number_only(char *s)
{
	if (*s == '-' && *(s + 1))
		s++;
	while (*s && ft_isdigit(*s))
		s++;
	return (*s ? 0 : 1);
}

void	not_enought_data(void)
{
	//free everything
	ft_error("ERROR", 1);
}

int		get_ants_number(void)
{
	char	*line;
	int		ants;

	ants = 0;
	ft_get_next_line(0, &line);
	if (check_if_number_only(line))
		ants = ft_atoi(line);
	ft_strdel(&line);
	return (ants > 0 ? ants : 0);
}

int		main(int ac, char **av)
{
	char		*line;
	int			ants;

	(void)ac;
	(void)av;
	ants = get_ants_number();
	if (ants == 0)
		not_enought_data();
	while (ft_get_next_line(0, &line) > 0)
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
	return (0);
}
