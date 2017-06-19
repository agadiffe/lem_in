/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_lemin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 10:13:45 by agadiffe          #+#    #+#             */
/*   Updated: 2017/06/17 10:38:04 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

static int		atoi_error(t_data *data)
{
	data->stop_get_data = 1;
	return (0);
}

int				ft_atoi_lemin(const char *s, t_data *data)
{
	long long	is_neg;
	long long	n;

	is_neg = 0;
	n = 0;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		is_neg = 1;
		s++;
	}
	if (!*s)
		return (atoi_error(data));
	while (*s && ft_isdigit(*s))
	{
		n = n * 10 + (*s++ - '0');
		if (n > INT_MAX + is_neg)
			return (atoi_error(data));
	}
	if (*s)
		return (atoi_error(data));
	return (is_neg ? -n : n);
}
