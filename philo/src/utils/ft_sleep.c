/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:24:20 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/06 17:25:12 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_sleep(long n)
{
	t_time		current_time;
	long a;
	long c;
	gettimeofday(&current_time, NULL);
	a = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	c = 0;
	usleep((n - 6) * 1000);
	while (c < n)
	{
		gettimeofday(&current_time, NULL);
		c = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000) - a;
	}
}