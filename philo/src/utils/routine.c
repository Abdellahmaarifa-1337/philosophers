/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:44:37 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/07 14:12:39 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int take_fork(t_philo *ph)
{
    t_global    *g;

    g = ph->global;
    //pthread_mutex_lock(&g->death_mutex);
    if (!g->death)
    {
       // pthread_mutex_unlock(&g->death_mutex);

        pthread_mutex_lock((g->fork_mutex) + ph->id);
        pthread_mutex_lock(&g->msg_mutex);
        printf("%ld %d has taken right fork\n",get_time() - g->start_time, ph->id + 1);
        pthread_mutex_unlock(&g->msg_mutex);

        pthread_mutex_lock((g->fork_mutex) + ((ph->id + 1) % g->n_philo));
        pthread_mutex_lock(&g->msg_mutex);
        printf("%ld %d has taken left fork\n",get_time() - g->start_time, ph->id + 1);
        pthread_mutex_unlock(&g->msg_mutex);
        return (0);
    }
    return (1);
}

int philo_eat(t_philo *ph)
{
    t_global    *g;

    g = ph->global;
   // pthread_mutex_lock(&g->death_mutex);

    if (!g->death)
    {
      //  pthread_mutex_unlock(&g->death_mutex);
        pthread_mutex_lock(&g->msg_mutex);
        printf("%ld %d is eating\n",get_time() - g->start_time, ph->id + 1);
        pthread_mutex_unlock(&g->msg_mutex);
        ph->last_time_eat = get_time();
        ph->meals += 1;
        ft_sleep(g->time_to_eat);
        pthread_mutex_unlock((g->fork_mutex) + ph->id);
        pthread_mutex_unlock((g->fork_mutex) + ((ph->id + 1) % g->n_philo));
        return (0);
    }
    return (1);
}

int philo_sleep(t_philo *ph)
{
    t_global    *g;

    g = ph->global;
    //pthread_mutex_lock(&g->death_mutex);
    if (!g->death)
    {
        //pthread_mutex_unlock(&g->death_mutex);
        pthread_mutex_lock(&g->msg_mutex);
        printf("%ld %d is sleeping\n",get_time() - g->start_time, ph->id + 1);
        pthread_mutex_unlock(&g->msg_mutex);
        ft_sleep(g->time_to_sleep);
        return (0);
    }
    return (1);
}

int philo_think(t_philo *ph)
{
    t_global    *g;

    g = ph->global;
   // pthread_mutex_lock(&g->death_mutex);
    if (!g->death)
    {
       // pthread_mutex_unlock(&g->death_mutex);
        pthread_mutex_lock(&g->msg_mutex);
        printf("%ld %d is thinking\n",get_time() - g->start_time, ph->id + 1);
        pthread_mutex_unlock(&g->msg_mutex);
        return (0);
    }
    return (1);
}

void *routine (void *philo)
{
    t_philo     *ph;
    t_global    *g;

    ph = (t_philo *)philo;
    g = ph->global;
    if (!g->start_time)
        g->start_time = get_time();
    while (1)
    {
        if (ph->meals == g->meals)
        {
            g->finish_eating += 1;
            free(philo);
            return (0);
        }
        if (take_fork(ph))
            break;
        if (philo_eat(ph))
            break;
        if (philo_sleep(ph))
            break;
        if (philo_think(ph))
            break;
        usleep(10);
    }
    free(philo);
    //pthread_mutex_lock(&g->death_mutex);
    //printf("id == %d end\n", ph->id);
    return 0;
}