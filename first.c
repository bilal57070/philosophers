/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:34 by bsafi             #+#    #+#             */
/*   Updated: 2024/03/07 23:19:28 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initall(t_all *all, char **av)
{
	all->time = get_current_time();
	all->nphilo = ft_atoi(av[1]);
	all->token = 0;
	//all->alleat = 0;
	all->time2die = (ft_atoi(av[2]));
	all->time2eat = (ft_atoi(av[3]));
	all->time2sleep = (ft_atoi(av[4]));
	if (av[5])
		all->nbreat = ft_atoi(av[5]);
	else
		all->nbreat = 0;
	pthread_mutex_init(&all->print, NULL);
	pthread_mutex_init(&all->checkdeath, NULL);
	pthread_mutex_init(&all->lmeal, NULL);
	pthread_mutex_init(&all->nbr, NULL);
}

void	initmut(t_all *all)
{
	int	i;

	i = -1;
	all->fork = malloc(sizeof(pthread_mutex_t) * all->nphilo);
	while (++i < all->nphilo)
		pthread_mutex_init(&all->fork[i], NULL);
	i = -1;
	while (++i < (all->nphilo - 1))
	{
		all->philo[i].fork = &all->fork[i];
		all->philo[i].rfork = &all->fork[i + 1];
	}
	//printf("%d\n", i);
	all->philo[i].fork = &all->fork[i];
	all->philo[i].rfork = &all->fork[0];
}

void	initstruc(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nphilo)
	{
		all->philo[i].id = (i + 1);
		all->philo[i].nbrmeal = 0;
		all->philo[i].fini = 0;
		all->philo[i].lasteat = all->time;
		all->philo[i].all = all;
		i++;
	}
}

void	makethread(t_all *all)//, t_philo *philo)
{
	int i = 0;
	pthread_create(&all->death, NULL, ryuk, &all->philo[i]);
	while (i < (all->nphilo))
	{
		//printf("test %d\n", all->i);
		//all->philo->idphilo = all->i;
		//philo[i].id = i;
		//printf("id : %d\n", philo->id);
		ft_usleep(5);
		pthread_create(&all->philo[i].thread, NULL, thread_routine, &all->philo[i]);
		i++;
		//all->philo->rfork++;
	}
	end(all);
}

void	*thread_routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->all->lmeal);
	philo->lasteat = get_current_time();
	pthread_mutex_unlock(&philo->all->lmeal);
	//printf("all : %d\n", philo->id);
	if (philo->id % 2 != 0)
		usleep(15000);
	while (checkdie(philo) != 1) //2e condition qu'il est manger suffisemment de fois
	{
		if (checkdie(philo) == 1)
			break;
		eating(philo);
		if (checkdie(philo) == 1)
			break;
		sleeping(philo);
		if (checkdie(philo) == 1)
			break;
		thinking(philo);
		if (checkdie(philo) == 1)
			break;
	}
	return NULL;
}
 /*faire une fonction qui print mais qui securise d'abord avec mutex*/

//pour le dernier thread manger
//if le i de all->philo[i] == all->nphilo dans ce cas all->philo[i].rfork == 1 (le premier philo)