/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:58:22 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/07 14:12:07 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
    TO DO:
    1: parse the data and check errors;
    2: init and create threads;
    3: make philo eat and sleep and think;
    4: kill the philos in time
*/


void watcher(t_philo *philos)
{
    int         i;
    int         n;
    long      last_time_eat;
    t_global    *g;

    g = (philos[0].global);
    n = philos[0].global->n_philo;
    while (g->finish_eating != n)
    {
        i = 0;
        while (i < n)
        {
            last_time_eat = (get_time() - (philos[i]).last_time_eat);
            if (g->meals == -1 && last_time_eat >= g->time_to_die)
            {
                g->death = 1;
                pthread_mutex_lock(&g->death_mutex);
                pthread_mutex_lock(&g->msg_mutex);
                printf("%ld %d died\n", get_time() - g->start_time ,i);
                return ;
            }
            i++;
        }
        usleep(30);
    }
}

void    lanch_philo(t_philo *philos)
{
    int i;
    int n;
    i = 0;
    n = philos[0].global->n_philo;
    while (i < n)
    {
        pthread_create(&(philos[i].th), NULL, &routine, (void *)(philos + i));
		usleep(60);
        i++;
    }
    // wait for threads
    watcher(philos);
    return ;
}

int main(int ac, char **av)
{
    t_global    global;
    t_philo     *philos;
    int         i;


    if (parse_data(ac, av, &global))
        return (1);
    global.death = 0;
    global.start_time = 0;
    global.finish_eating = 0;
    global.fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * global.n_philo);
    philos = (t_philo *)malloc(sizeof(t_philo) * global.n_philo);
    pthread_mutex_init(&global.msg_mutex, NULL);
    pthread_mutex_init(&global.death_mutex, NULL);
    i = 0;
    while (i < global.n_philo)
    {
        pthread_mutex_init(global.fork_mutex + i, NULL);
        i++;
    }
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
    // printf("number of philosoper : %d\n", global.n_philo);
    // printf("time to die : %d\n", global.time_to_die);
    // printf("time to eat : %d\n", global.time_to_eat);
    // printf("tiem to sleep : %d\n", global.time_to_sleep);
    // printf("meals : %d\n", global.meals);
    return (0);
}