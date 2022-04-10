/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:33 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/10 22:42:23 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_die(t_global *g, long last_time_eat, int meals, int id)
{
	if (meals != g->meals && last_time_eat >= g->time_to_die - 1)
	{
		printf("%ld %d died\n", get_time() - g->start_time, id + 1);
		return (1);
	}
	if (g->finish_eating == g->n_philo)
	{
		printf("every one is eat\n");
		return (1);
	}
	return (0);
}

void	*watcher_th(void *philos)
{
	t_philo		*ph;
	t_global	*g;
	int			i;
	long		last_time_eat;

	ph = (t_philo *)philos;
	g = ph[0].global;
	i = -1;
	while (++i < g->n_philo)
	{
		pthread_mutex_lock(&g->msg_mutex);
		last_time_eat = (get_time() - (ph[i]).last_time_eat);
		if (is_die(g, last_time_eat, ph[i].meals, i))
			return (0);
		pthread_mutex_unlock(&g->msg_mutex);
		if (i == g->n_philo - 1)
			i = -1;
	}
	return (0);
}
