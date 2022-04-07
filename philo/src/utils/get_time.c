/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:53:38 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/07 14:11:10 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t get_time(void)
{
	t_time		*current_time;
	size_t		time;

	current_time = malloc(sizeof(t_time));
	gettimeofday(current_time, NULL);
	time = (size_t)(current_time->tv_sec * 1000) + (current_time->tv_usec / 1000);
	free(current_time);
	return (time);
}