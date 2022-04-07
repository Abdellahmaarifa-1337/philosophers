/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:56:03 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/07 00:43:57 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct timeval t_time;

typedef struct s_global {
    int             n_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals;
    int             death;
    int             finish_eating;
    long          start_time;
    pthread_mutex_t *fork_mutex;
    pthread_mutex_t msg_mutex;
    pthread_mutex_t death_mutex;
} t_global;

typedef struct s_philo {
    t_global        *global;   
    int             id;
    int             meals;
    long          last_time_eat;
    pthread_t       th;
} t_philo;

/* UTILS */
int throw_error(char *error);
int parse_data(int ac,char **av, t_global *global);
void *routine (void *philo);
size_t get_time(void);
void	ft_sleep(long n);

/* HELPERS */
int	ft_atoi(const char	*str);
int	ft_isdigit(int c);
#endif