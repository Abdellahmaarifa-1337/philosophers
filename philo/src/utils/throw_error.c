/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:55:18 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/06 14:29:09 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int throw_error(char *error)
{
    printf("%s%s%s%s%s\n", "\e[1;34musage\t: philo [n_ph] [t_eat] [t_sleep] [meals]\n",
            "\tn_ph\t: number of philosophers\n",
            "\tt_eat\t: time to eat\n",
            "\tt_sleep\t: time to sleep\n",
            "\tmeals:\t: number of times each philosopher must eat\n");
    if (error)
        printf("%s\n", error);
    return (1);
}