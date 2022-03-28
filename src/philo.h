/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 08:10:17 by amaarifa          #+#    #+#             */
/*   Updated: 2022/03/26 19:03:15 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct timeval t_time;

typedef struct s_ph {
	long last_time_eat;
	int	meals;
} t_ph;

typedef struct s_global
{
	int					n_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					n_eat;
	int					death;
	long				start_time;
	int					set_start_time;
	int					finish_philo;
	pthread_mutex_t		finish;
	pthread_mutex_t		*forks;
	t_ph				*ph;
	pthread_mutex_t		msg;
} t_global;

typedef struct s_philo
{
	int		id;
	int		meals;
	t_global *gloabl;
} t_philo;

/* ----------- HELPERS ------------*/
int		ft_atoi(const char	*str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char	*src);

/* ---------- UTILS -------------- */
void	throw_err(char *err);

#endif