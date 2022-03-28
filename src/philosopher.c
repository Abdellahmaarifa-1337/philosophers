/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:23:09 by amaarifa          #+#    #+#             */
/*   Updated: 2022/03/27 16:07:01 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_current_time(void)
{
	t_time		*current_time;
	current_time = malloc(sizeof(t_time));
	gettimeofday(current_time, NULL);
	return ((current_time->tv_sec * 1000) + (current_time->tv_usec / 1000));
}

void	ft_sleep (long n)
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
	//printf("time of sleep : %ld\n",c);
}

void init_global(t_global *global, int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		throw_err("args must be 4 or 5\n");
	if (ac == 5)
		global->n_eat = -1;
	else
		global->n_eat = ft_atoi(av[ac - 1]);
	global->n_philo = ft_atoi(av[1]);
	global->time_die = ft_atoi(av[2]);
	global->time_eat = ft_atoi(av[3]);
	global->time_sleep = ft_atoi(av[4]);
	global->death = 0;
	global->start_time = 0;
	global->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * global->n_philo);
	global->ph = (t_ph *)malloc(sizeof(t_ph) * global->n_philo);
	global->set_start_time = 1;
	global->finish_philo = global->n_philo;
	i = 0;
	while (i < global->n_philo)
	{
		(global->ph[i]).meals = 0;
		i++;
	}
	return ;
}


int	take_fork(t_global *global, int id)
{
	long	time;

	pthread_mutex_lock(&global->finish);
	if (global->death)
		return (1) ;
	pthread_mutex_unlock(&global->finish);
	pthread_mutex_lock((global->forks) + id);
	pthread_mutex_lock(&(global->msg));
	time = get_current_time() - global->start_time;
	printf("%ld %d has taken a fork\n", time, id);
	pthread_mutex_unlock(&(global->msg));
	
	if (global->n_philo == 1)
	{
		global->ph[id].last_time_eat = get_current_time();
		while (!global->death)
		{
			;
		}
	}
	pthread_mutex_lock(&global->finish);
	if (global->death)
		return (1);
	pthread_mutex_unlock(&global->finish);
	pthread_mutex_lock((global->forks) + ((id + 1) % global->n_philo));
	pthread_mutex_lock(&(global->msg));
	time = get_current_time() - global->start_time;
	printf("%ld %d has taken a fork\n", time, id);
	pthread_mutex_unlock(&(global->msg));
	return (0);

}

int eat(t_global *global, int id, void *philo)
{
	long time;

	pthread_mutex_lock(&global->finish);
	if (global->death)
		return (1);
	pthread_mutex_unlock(&global->finish);
	pthread_mutex_lock(&(global->msg));
	time = get_current_time() - global->start_time;
	global->ph[id].last_time_eat = get_current_time();
	global->ph[id].meals += 1;
	if (((t_philo *)philo)->meals == global->n_eat)
		return (1);
	((t_philo *)philo)->meals += 1;
	printf("%ld %d is eating\n", time, id);
	pthread_mutex_unlock(&(global->msg));
	ft_sleep(global->time_eat);
	pthread_mutex_unlock((global->forks) + id);
	pthread_mutex_unlock((global->forks) + ((id + 1) % global->n_philo));
	return (0);
	
}

int start_sleep(t_global *global, int id)
{
	long time;
	pthread_mutex_lock(&global->finish);
	if (global->death)
		return (1);
	pthread_mutex_unlock(&global->finish);
	pthread_mutex_lock(&(global->msg));
	time = get_current_time() - global->start_time;
	printf("%ld %d is sleeping\n", time, id);
	pthread_mutex_unlock(&(global->msg));
	ft_sleep(global->time_sleep);
	return (0);
}

int think(t_global *global, int id)
{
	long time;
	pthread_mutex_lock(&global->finish);
	if (global->death)
		return (1);
	pthread_mutex_unlock(&global->finish);
	pthread_mutex_lock(&(global->msg));
	time = get_current_time() - global->start_time;
	printf("%ld %d is thinking\n", time, id);
	pthread_mutex_unlock(&(global->msg));
	return (0);
}

void	*routine(void *philo)
{
	int 		id;
	t_global 	*global;
	long		time;

	id = ((t_philo *)philo)->id;
	global = ((t_philo *)philo)->gloabl;
	if (global->set_start_time)
	{
		global->start_time = get_current_time();
		global->set_start_time = 0;
	}
	while (!global->death)
	{
		if (take_fork(global, id))
			break ;
		if (eat(global, id, philo))
			break ;
		if (start_sleep(global, id))
			break ;
		if (think(global, id))
			break ;
	}
	// pthread_mutex_lock(&global->finish);
	// global->finish_philo -= 1;
	// pthread_mutex_unlock(&global->finish);
	return (0);
}

void watcher(t_global *global)
{
	long		time;
	int			i;

	while(!(global->death))
	{
		i = 0;
		while (i < global->n_philo)
		{
			time = get_current_time(); 
			if (time - global->ph[i].last_time_eat >= global->time_die)
			{
				//printf("time == %ld\n", time);
				//printf(" last time eat == %ld\n", global->ph[i].last_time_eat);
				//printf("%ld\n", time - global->ph[i].last_time_eat);
				pthread_mutex_lock(&global->finish);
				global->death = 1;
				printf("%ld %d died\n", (get_current_time() - global->start_time), i);
				exit(1);
				pthread_mutex_unlock(&global->finish);
				break;
			}
			i++;
		}
		// i = 0;
		// while (i < global->n_philo)
		// {
		// 	if (global->ph[i].meals == global->n_eat)
		// 	{
		// 		i++;
		// 		continue ;
		// 	}
		// 	else
		// 		break;
		// }
		// printf("number of meals is : %d\n", i);
		// if (i == global->n_philo)
		// 	global->death = 1;
	}
	// while (global->finish_philo)
	// {
	// 	printf("finish %d\n", global->finish_philo);
	// 	;
	// }
	i = -1;
	while (++i < global->n_philo)
		pthread_mutex_destroy(global->forks + i);
	exit(1);
}

void create_philos(t_global *global)
{
	pthread_t	*th;
	int			i;
	t_philo		*philo;
	long		time;

	i = 0;
	th = (pthread_t *)malloc(sizeof(pthread_t) * global->n_philo);
	while (i < global->n_philo)
		(global->ph[i++]).last_time_eat = get_current_time();
	i = 0;
	while (i < global->n_philo)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		philo->gloabl = global;
		philo->id = i;
		philo->meals = 0;
		pthread_create((th + i), NULL, &routine, (void *)philo);
		if (i % 2 == 0)
			usleep(40);
		i++;
	}
	//while(1);
	watcher(global);
}

int main(int ac, char **av)
{
	t_global 	global;
	int			i;

	/* init the default values of the global */
	init_global(&global, ac, av);
	
	/* Create mutex */
	i = -1;
	while (++i < global.n_philo)
		pthread_mutex_init((global.forks + i), NULL);

	/* Create threads*/
	pthread_mutex_init(&global.finish, NULL);
	create_philos(&global);

	/* Destroy mutex */
	i = -1;
	while (++i < global.n_philo)
		pthread_mutex_destroy(global.forks + i);
	return (0);
}