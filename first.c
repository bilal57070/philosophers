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

/*void	init(t_all *all)
{
	pthread_mutex_init(all->fork, NULL);
}*/

void	initstruc(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nphilo)
	{
		all->philo[i].id = i;
		all->philo[i].eat = 0; 
		all->philo[i].all = all;
		i++;
	}
}

void	makethread(t_all *all, t_philo *philo)
{
	int i = 0;
	philo->all = malloc(sizeof(t_all));
	all->philo = malloc(sizeof(t_philo) * all->nphilo);
	all->philo->rfork = 1;
	while (i < (all->nphilo))
	{
		//printf("test %d\n", all->i);
		//all->philo->idphilo = all->i;
		philo[i].id = i;
		//printf("id : %d\n", philo->id);
		pthread_create(&philo[i].thread, NULL, thread_routine, philo);
		i++;
		all->philo->rfork++;
	}
	int n;
	n = 0;
	while (n < all->nphilo)
	{
		pthread_join(philo[n].thread, NULL);
		n++;
	}
}

void	*thread_routine(void *data)
{
	t_philo		*philo;
	int			r;
	
	philo = (t_philo *)data;
	r = 0;
	printf("all : %d\n", philo->id);
	printf("peut etre \n");
	while (r < philo->all->nphilo) // faire qvqnt lq routine
	{
		//printf("nani\n");
		pthread_mutex_init(philo->fork, NULL);
		//printf("nani2\n");
		//pthread_join(all->philo[r].thread, NULL);
		//printf("nani3\n");
		r++;
	}
	//printf("all 2: %d\n", all->tid);
	//printf("ici\n");
	while (philo->all->token != 1) //2e condition qu'il est manger suffisemment de fois
	{
		//if ((philo->tid) == (all->nphilo - 1)) //|| all->philo->rfork > all->nphilo)
		//	all->philo[all->tid].rfork = 1;
		//printf("id : %d\n", philo->id);
		//pthread_mutex_lock(&all->philo[all->tid].fork);
		//printf("  Philo %d has taken a fork\n", all->i);
		//pthread_mutex_lock(&all->philo[all->philo[all->tid].rfork].fork);
		//printf("  Philo %d has taken a fork\n", all->i);
		usleep(20000);
		//printf("  Philo %d mange chacal\n", all->i);
		//pthread_mutex_unlock(&all->philo[all->tid].fork);
		//pthread_mutex_unlock(&all->philo[all->philo[all->tid].rfork].fork);
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