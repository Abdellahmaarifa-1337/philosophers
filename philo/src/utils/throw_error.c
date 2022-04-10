/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:55:18 by amaarifa          #+#    #+#             */
/*   Updated: 2022/04/10 15:09:36 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	throw_error(char *error)
{
	printf("%s%s%s%s%s\n", "\e[1;34musage\t: philo [n] [e] [s] [m]\n",
		"\tn\t: number of philosophers\n",
		"\te\t: time to eat\n",
		"\ts\t: time to sleep\n",
		"\tm:\t: number of times each philosopher must eat\n");
	if (error)
		printf("%s\n", error);
	return (1);
}
