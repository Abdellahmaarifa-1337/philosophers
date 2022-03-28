/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 12:10:26 by amaarifa          #+#    #+#             */
/*   Updated: 2022/03/18 09:38:40 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char	*str)
{
	int				i;
	int				ng;
	long			res;

	i = 0;
	ng = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		ng *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		throw_err("the arg shouls be a number\n");
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i++] - '0');
		if ((res >= 2147483648 && ng > 0) || (res > 2147483648 && ng < 0))
			throw_err("one of the args is over tha max/min of int\n");
	}
	if (str[i] && !ft_isdigit(str[i]))
		throw_err("the arg shouls be a number\n");
	return (res * ng);
}
