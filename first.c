/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:34 by bsafi             #+#    #+#             */
/*   Updated: 2024/02/15 22:04:05 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	getnphilo(t_all *all, char **av)
{
	all->nphilo = 0;
	all->nphilo = ft_atoi(av[1]);
	if (av[5])
		all->nbreat = ft_atoi(av[5]);
}

void	makethread(t_all *all)
{
	int	i;

	i = 0;
	all->philo = malloc(sizeof(t_all) * all->nphilo);
	while (i < all->nphilo)
	{
		printf("test %d\n", i);
		pthread_create(&all->philo[i].thread, NULL, thread_routine, all);
		i++;
	}
}

void	*thread_routine(void *data)
{
	t_all		*all;
	pthread_t	tid;
	//int			i;

	tid = pthread_self();
	all = (t_all *)data;
	printf("test%ld  %d\n", tid, all->nphilo);
	//while ()
	return NULL;
}