/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:37:10 by bsafi             #+#    #+#             */
/*   Updated: 2024/03/23 14:54:19 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ryuk(void *data)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)data;
	i = 0;
	while (1)
	{
		if (i == philo->all->nphilo)
			i = 0;
		if (death(&philo[i]) == 1)
		{
			lockd(philo);
			break ;
		}
		if (philo->all->nbreat > 0)
		{
			if (bienmanger(philo) == 1)
			{
				lockd(philo);
				break ;
			}
		}
		i++;
	}
	return (NULL);
}

int	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->lmeal);
	if ((get_current_time() - philo->lasteat) >= philo->all->time2die)
	{
		pthread_mutex_lock(&philo->all->print);
		printf("%lld %d died\n",
			(get_current_time() - philo->all->time), philo->id);
		pthread_mutex_unlock(&philo->all->print);
		pthread_mutex_unlock(&philo->all->lmeal);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->lmeal);
	return (0);
}

void	end(t_all *all)
{
	int	i;

	i = -1;
	if (all->nphilo > 1)
	{
		while (++i < all->nphilo)
			pthread_join(all->philo[i].thread, NULL);
		i = -1;
	}
	while (++i < all->nphilo)
	{
		pthread_mutex_unlock(all->philo[i].fork);
		pthread_mutex_unlock(all->philo[i].rfork);
	}
	pthread_mutex_unlock(all->fork);
	pthread_mutex_unlock(&all->print);
	pthread_mutex_unlock(&all->checkdeath);
	pthread_mutex_unlock(&all->lmeal);
	pthread_mutex_unlock(&all->nbr);
}

int	bienmanger(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->all->nphilo)
	{
		pthread_mutex_lock(&philo->all->nbr);
		if (philo[i].nbrmeal >= philo->all->nbreat)
			philo[i].fini = 1;
		pthread_mutex_unlock(&philo->all->nbr);
		if (philo[i].fini != 1)
		{
			return (0);
		}
	}
	return (1);
}

int	checkdie(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->checkdeath);
	if (philo->all->token == 1)
	{
		pthread_mutex_unlock(&philo->all->checkdeath);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->checkdeath);
	return (0);
}
