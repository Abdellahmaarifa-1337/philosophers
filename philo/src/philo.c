/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:58:22 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/10 17:14:41 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lanch_philo(t_philo *philos)
{
	int			i;
	int			n;
	pthread_t	observer_thread;

	i = 0;
	n = philos[0].global->n_philo;
	while (i < n)
	{
		pthread_create(&(philos[i].th), NULL, &routine, (void *)(philos + i));
		usleep(60);
		i++;
	}
	pthread_create(&observer_thread, NULL, &watcher_th, (void *)philos);
	pthread_join(observer_thread, NULL);
	return ;
}

t_philo	*init_data(t_global *global)
{
	int		i;
	t_philo	*philos;

	global->death = 0;
	global->start_time = 0;
	global->finish_eating = 0;
	global->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* global->n_philo);
	global->finish = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * global->n_philo);
	pthread_mutex_init(&global->msg_mutex, NULL);
	pthread_mutex_init(&global->death_mutex, NULL);
	pthread_mutex_init(&global->finish_mutex, NULL);
	pthread_mutex_init(&global->finish_eating_mutex, NULL);
	i = 0;
	while (i < global->n_philo)
	{
		pthread_mutex_init(global->fork_mutex + i, NULL);
		i++;
	}
	return (philos);
}

int	main(int ac, char **av)
{
	t_global	global;
	t_philo		*philos;
	int			i;

	if (parse_data(ac, av, &global))
		return (1);
	philos = init_data(&global);
	i = 0;
	while (i < global.n_philo)
	{
		philos[i].global = &global;
		philos[i].id = i;
		philos[i].meals = 0;
		philos[i].last_time_eat = get_time();
		i++;
	}
	lanch_philo(philos);
	return (0);
}
