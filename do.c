/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:17:48 by bsafi             #+#    #+#             */
/*   Updated: 2024/03/23 14:50:33 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (checkdie(philo) == 1)
		return ;
	pthread_mutex_lock(philo->fork);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		return ;
	}
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d has taken a fork\n",
		(get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	pthread_mutex_lock(philo->rfork);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->rfork);
		return ;
	}
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d has taken a fork\n",
		(get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	eating2(philo);
}

void	eating2(t_philo *philo)
{
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->rfork);
		return ;
	}
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d is eating\n",
		(get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	pthread_mutex_lock(&philo->all->nbr);
	philo->nbrmeal++;
	pthread_mutex_unlock(&philo->all->nbr);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->rfork);
		return ;
	}
	ft_usleep(philo->all->time2eat);
	eating3(philo);
}

void	eating3(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->lmeal);
	philo->lasteat = get_current_time();
	pthread_mutex_unlock(&philo->all->lmeal);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->rfork);
	if (checkdie(philo) == 1)
		return ;
}

void	sleeping(t_philo *philo)
{
	if (checkdie(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d ne3essss\n",
		(get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	ft_usleep(philo->all->time2sleep);
}

void	thinking(t_philo *philo)
{
	if (checkdie(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d is thinking\n",
		(get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
}
