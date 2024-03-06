/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:17:48 by bsafi             #+#    #+#             */
/*   Updated: 2024/03/06 21:48:40 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	if (philo->all->token == 1)
		return ;
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d has taken a fork\n", (get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	pthread_mutex_lock(philo->rfork);
	if (philo->all->token == 1)
		return ;	
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d has taken a fork\n", (get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d is eating\n", (get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	ft_usleep(philo->all->time2eat);
	//pthread_mutex_lock(&philo->all->gct);
	philo->lasteat = get_current_time(); // data race avec get_current_time
	//pthread_mutex_unlock(&philo->all->gct);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->rfork);
	philo->nbrmeal++;
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d ne3essss\n", (get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	ft_usleep(philo->all->time2sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d is thinking\n", (get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
}

void	*ryuk(void *data)
{
	int		i;
	t_philo *philo;

	philo = (t_philo *)data;
	i = 0;
	while (1)
	{
		if (i == philo->all->nphilo)
			i = 0;
		death(&philo[i]);
		if (philo->all->nbreat > 0)
		{
			if (bienmanger(philo) == 1)
				philo->all->token = 1;
		}
		if (philo->all->token == 1)
			unlock(philo);
		i++;
	}
	return NULL;
}

int		death(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->checkdeath);
	if ((get_current_time() - philo->lasteat) >= philo->all->time2die)
	{
		philo->all->token = 1;
		pthread_mutex_lock(&philo->all->print);
		printf("%lld %d died\n", (get_current_time() - philo->all->time), philo->id);
		return (1);
		pthread_mutex_unlock(&philo->all->print);
	}
	pthread_mutex_unlock(&philo->all->checkdeath);
	return (0);
}

void	unlock(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->all->nphilo)
		pthread_mutex_unlock(philo[i].fork);
}

int		bienmanger(t_philo *philo)
{
	int	i;

	i = -1;
	//philo->all->alleat = 1;
	while (++i < philo->all->nphilo)
	{
		if (philo[i].nbrmeal >= philo->all->nbreat)
			philo[i].fini = 1;
		if (philo[i].fini != 1)
		{
			//philo->all->alleat = 0;
			return (0);
		}
	}
	return (1);
}