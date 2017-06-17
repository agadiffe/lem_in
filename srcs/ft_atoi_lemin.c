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

int		ft_atoi_lemin(const char *s)
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
		ft_error("ERROR", 4);
	while (*s && ft_isdigit(*s))
	{
		n = n * 10 + (*s++ - '0');
		if (n > INT_MAX + is_neg)
			ft_error("ERROR", 4);
	}
	if (*s)
		ft_error("ERROR", 4);
	return (is_neg ? -n : n);
}
