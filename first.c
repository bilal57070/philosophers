/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:34 by bsafi             #+#    #+#             */
/*   Updated: 2024/02/22 00:35:05 by bsafi            ###   ########.fr       */
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
	all->tid = 0;
	all->philo = malloc(sizeof(t_philo) * all->nphilo);
	all->philo->rfork = 1;
	while (all->tid < (all->nphilo))
	{
		//printf("test %d\n", all->i);
		//all->philo->idphilo = all->i;
		pthread_create(&all->philo[all->tid].thread, NULL, thread_routine, all);
		all->tid++;
		all->philo->rfork++;
	}
	int n;
	n = 0;
	while (n < all->nphilo)
	{
		pthread_join(all->philo[n].thread, NULL);
		n++;
	}
}

void	*thread_routine(void *data)
{
	t_all		*all;
	int			r;
	
	all = (t_all *)data;
	r = 0;
	printf("all : %d\n", all->tid);
	printf("peut etre \n");
	while (r < all->nphilo)
	{
		//printf("nani\n");
		pthread_mutex_init(&all->philo[r].fork, NULL);
		//printf("nani2\n");
		//pthread_join(all->philo[r].thread, NULL);
		//printf("nani3\n");
		r++;
	}
	//printf("all 2: %d\n", all->tid);
	//printf("ici\n");
	while (all->token != 1) //2e condition qu'il est manger suffisemment de fois
	{
		if ((all->tid) == (all->nphilo - 1)) //|| all->philo->rfork > all->nphilo)
			all->philo[all->tid].rfork = 1;
		//printf("all : %d\n", all->tid);
		pthread_mutex_lock(&all->philo[all->tid].fork);
		//printf("  Philo %d has taken a fork\n", all->i);
		pthread_mutex_lock(&all->philo[all->philo[all->tid].rfork].fork);
		//printf("  Philo %d has taken a fork\n", all->i);
		usleep(20000);
		//printf("  Philo %d mange chacal\n", all->i);
		pthread_mutex_unlock(&all->philo[all->tid].fork);
		pthread_mutex_unlock(&all->philo[all->philo[all->tid].rfork].fork);
	}
	//pthread_t	tid;
	//int			i;

	//tid = pthread_self();
	//printf("test%ld  %d\n", tid, all->nphilo);
	//while ()
	return NULL;
}

// ZBI PK LE ALL->TID PART PAS DE 0 QUAND JE PRINT CA PART DE 1


//pour le dernier thread manger
//if le i de all->philo[i] == all->nphilo dans ce cas all->philo[i].rfork == 1 (le premier philo)