/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:51:10 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/06 15:06:18 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"
int checker(int ac, char **av)
{
  int i;
  
  i = 1;
  while (i < ac)
  {
    if (ft_atoi(av[i]) == -1)
      return (throw_error("[args] must be a positive numbers"));
    else if (ft_atoi(av[i]) == -2)
      return (throw_error("[args] must be not more than INT_MAX"));
    else if (ft_atoi(av[i]) == -3)
      return (throw_error("[args] must be digits only"));
    else if (ft_atoi(av[i]) == 0 && i == 1)
      return (throw_error("[n_ph] there must be at least one philosopher"));
    i++;
  }
  return (0);
}

int parse_data(int ac,char **av, t_global *global)
{
  // PARSE THE DATA 
  if (ac != 5 && ac != 6)
    return (throw_error(NULL));
  if (checker(ac,av))
    return (1);
  global->n_philo = ft_atoi(av[1]);
  global->time_to_die = ft_atoi(av[2]);
  global->time_to_eat = ft_atoi(av[3]);
  global->time_to_sleep = ft_atoi(av[4]);
  if (ac == 6)
    global->meals = ft_atoi(av[5]);
  else 
    global->meals = -1;
  return (0);  
}
