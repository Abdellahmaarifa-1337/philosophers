/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 08:13:15 by amaarifa          #+#    #+#             */
/*   Updated: 2022/03/21 23:05:53 by amaarifa         ###   ########.fr       */
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
void	*routine(void *philo_th)  
{
	int			id;
	t_global	*global;
	int			i;
	t_time		*current_time;

	id = ((t_philo_th *)philo_th)->id;
	global = ((t_philo_th *)philo_th)->global;
	while (1)
	{
		if (global->n_philo == 1)
			continue ;
		//printf("id of thread : %d\n", id);
		int re = pthread_mutex_lock((global->forks) + id);

		//pthread_mutex_lock(&(global->curr_time));
		global->current_time = get_current_time();
		//pthread_mutex_unlock(&(global->curr_time));
		pthread_mutex_lock(&(global->fork_msg_mutex));
		printf("%ld %d %s\n", (global->current_time) - (global->start_time) , id + 1,global->fork_msg);
		pthread_mutex_unlock(&(global->fork_msg_mutex));
		int re2 = pthread_mutex_lock( global->forks + ((id + 1 )% (global->n_philo)));
		//printf("mutx re2 = %d id = %d\n", re, ((id + 1 )% (global->n_philo)));

		// if (id == global->n_philo - 1)
		// 	pthread_mutex_lock((global->forks));
		// else
		// 	pthread_mutex_lock((global->forks) + id + 1);
			global->current_time = get_current_time();

		//
		//

		pthread_mutex_lock(&(global->fork_msg_mutex));
		printf("%ld %d %s\n", (global->current_time) - (global->start_time) , id + 1,global->fork_msg);
		pthread_mutex_unlock(&(global->fork_msg_mutex));

		//pthread_mutex_lock(&(global->curr_time));
		global->current_time = get_current_time();
		//pthread_mutex_unlock(&(global->curr_time));
		// if ((global->philos)[id].time == -1)
		// {
		// 	if (global->current_time - global->start_time >= global->time_eat)
		// 	{
		// 		printf("end 1 \n");
		// 		global->game_over = 0;
		// 	}
		// } else
		// {
		// 	if (global->current_time - (global->philos)[id].time >= global->time_eat)
		// 	{
		// 		printf("end 2\n");
		// 		global->game_over = 0;
		// 	}
		// }
		//pthread_mutex_lock(&(global->curr_time));
		//pthread_mutex_lock(&((global->philos)[id].time));
		(global->philos)[id].time = get_current_time();
		//printf("the %d is reset  to the current time\n", id);
		//pthread_mutex_lock(&((global->philos)[id].time));
		//pthread_mutex_unlock(&(global->curr_time));

		pthread_mutex_lock(&(global->eat_msg_mutex));
		printf("%ld %d %s\n", (global->current_time) - (global->start_time), id + 1, (global->eat_msg));
		pthread_mutex_unlock(&(global->eat_msg_mutex));

		ft_sleep(global->time_eat);
		// if (id == global->n_philo - 1)
		// 	pthread_mutex_unlock((global->forks));
		// else
		// 	pthread_mutex_unlock((global->forks) + id + 1);

		pthread_mutex_unlock((global->forks) + id);
		pthread_mutex_unlock( global->forks + ((id + 1 )% (global->n_philo)));

		//pthread_mutex_lock(&(global->curr_time));
		global->current_time = get_current_time();
		//pthread_mutex_unlock(&(global->curr_time));

		pthread_mutex_lock(&(global->sleep_msg_mutex));
		printf("%ld %d %s\n",(global->current_time) - (global->start_time), id + 1, (global->sleep_msg));
		pthread_mutex_unlock(&(global->sleep_msg_mutex));

		ft_sleep(global->time_sleep);
		//pthread_mutex_lock(&(global->curr_time));
		global->current_time = get_current_time();
		//pthread_mutex_unlock(&(global->curr_time));

		pthread_mutex_lock(&(global->think_msg_mutex));
		printf("%ld %d %s\n",(global->current_time) - (global->start_time), id + 1, global->think_msg);
		pthread_mutex_unlock(&(global->think_msg_mutex));


		//usleep(1);
	}
	printf("hello thread! %d\n", id);
	return (0);
}


void	start_philo(t_global *philo)
{
	pthread_t	*th;
	int			i;
	t_philo_th	*philo_th;

	i = 0;
	th = malloc(sizeof(pthread_t) * philo->n_philo);
	while (i < philo->n_philo)
	{
		philo_th = (t_philo_th *)malloc(sizeof(t_philo_th));
		philo_th->global = philo;
		philo_th->id = i;
		pthread_create((th + i), NULL, &routine, (void *)philo_th);
		i++;
		 if (i % 2 != 0)
			usleep(10);
	}
	i = 0;
	t_time		current_time;
	long 		a;

	while (philo->game_over)
	{
		// pthread_join(th[i], NULL);
		// i++;
		i = 0;
		while (i < philo->n_philo )
		{
			gettimeofday(&current_time, NULL);
			a = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000) ;
			if (((philo->philos)[i]).time == -1 && (a - philo->start_time) >= philo->time_die)
			{
				//printf("current time %ld\n", a);
				//printf("start time %ld\n", philo->start_time);
				printf(">>>>>>> last time %d eat %ld",i, ((philo->philos)[i]).time);
				printf(">>>>>>> current time %ld and the time to die %d\n", (a - philo->start_time), i);
				exit(1);
			}
			if (((philo->philos)[i]).time != -1 && ( a - ((philo->philos)[i]).time) >= philo->time_die)
			{
				// printf("current time %ld\n", a);
				// printf("start time %ld\n", philo->start_time);
				// printf("last time %d eat %ld",i, ((philo->philos)[i]).time);
				printf(">>>>>>> last time %d eat %ld",i, ((philo->philos)[i]).time);
				printf(">>>>>>> current time %ld and the time to die %d\n", (a - philo->start_time), i);
				printf("time to die%ld phili %d\n", a - philo->start_time, i);
				exit(1);
			}
			i++;
		}
		//usleep(2 * 1000);
	}
	exit(1);
}
int	main(int ac, char **av)
{
	t_global	global;
	int			i;
 	t_time		current_time;
  	gettimeofday(&current_time, NULL);
  	//	printf("seconds : %ld\nmicro seconds : %ld\n",
	  //current_time.tv_sec, current_time.tv_usec);
	if (ac < 5 || ac > 6)
		throw_err("args must be 4 or 5\n");
	if (ac == 5)
		global.n_eat = -1;
	else
		global.n_eat = ft_atoi(av[ac - 1]);
	global.n_philo = ft_atoi(av[1]);
	global.time_die = ft_atoi(av[2]);
	global.time_eat = ft_atoi(av[3]);
	global.time_sleep = ft_atoi(av[4]);
	global.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * global.n_philo);
	global.philos = malloc(sizeof(t_philo) * global.n_philo);
	global.fork_msg = ft_strdup("has taken a fork");
	pthread_mutex_init(&(global.fork_msg_mutex), NULL);
	global.eat_msg = ft_strdup("is eating");
	pthread_mutex_init(&(global.eat_msg_mutex),NULL);
	global.sleep_msg = ft_strdup("is sleeping");
	pthread_mutex_init(&(global.sleep_msg_mutex),NULL);
	global.think_msg = ft_strdup("is thinking");
	pthread_mutex_init(&(global.think_msg_mutex),NULL);

	global.game_over = 1;
	i = 0;
	while (i < global.n_philo)
	{
		pthread_mutex_init((global.forks + i), NULL);
		//(global.philos[i]).last_time_eat = -1;
		//(global.philos[i]).state = -1;
		(global.philos[i]).time = -1;
		
		pthread_mutex_init(&((global.philos[i]).time_mutex), NULL);
		i++;
	}
	pthread_mutex_init(&(global.curr_time), NULL);
	global.start_time = get_current_time();
	printf("start at : %ld\n", global.start_time);
	start_philo(&global);
	i = 0;
	while (i < global.n_philo)
	{
		pthread_mutex_destroy((global.forks + i));
		i++;
	}
	pthread_mutex_destroy(&(global.curr_time));
	printf("end thread\n");
	return (0);
}
