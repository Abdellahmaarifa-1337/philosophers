/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:39:52 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/10 15:15:27 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char	*str)
{
	int				i;
	unsigned long	res;
	unsigned long	l_max;

	i = 0;
	l_max = INT_MAX;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i++] - '0');
		if (res > l_max)
			return (-2);
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-3);
	return (res);
}
