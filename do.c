/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:17:48 by bsafi             #+#    #+#             */
/*   Updated: 2024/03/07 22:02:45 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		return ;
	}
	pthread_mutex_lock(&philo->all->print);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(&philo->all->print);
		return ;
	}
	printf("%lld %d has taken a fork\n", (get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	pthread_mutex_lock(philo->rfork);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->rfork);
		return ;
	}
	pthread_mutex_lock(&philo->all->print);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(&philo->all->print);
		return ;
	}
	printf("%lld %d has taken a fork\n", (get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->rfork);
		return ;
	}
	pthread_mutex_lock(&philo->all->print);
	printf("%lld %d is eating\n", (get_current_time() - philo->all->time), philo->id);
	ft_usleep(philo->all->time2eat);
	pthread_mutex_unlock(&philo->all->print);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->rfork);
		return ;
	}
	//if (checkdie(philo) == 1)
	//	return ;
	pthread_mutex_lock(&philo->all->lmeal);
	philo->lasteat = get_current_time(); // data race avec get_current_time
	pthread_mutex_unlock(&philo->all->lmeal);
	//if (checkdie(philo) == 1)
	//	return ;
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_lock(&philo->all->nbr);
	philo->nbrmeal++;
	pthread_mutex_unlock(&philo->all->nbr);
	if (checkdie(philo) == 1)
		return ;
}

void	sleeping(t_philo *philo)
{
	if (checkdie(philo) == 1)
	{
		return ;
	}
	pthread_mutex_lock(&philo->all->print);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(&philo->all->print);
		return ;
	}
	printf("%lld %d ne3essss\n", (get_current_time() - philo->all->time), philo->id);
	pthread_mutex_unlock(&philo->all->print);
	ft_usleep(philo->all->time2sleep);
}

void	thinking(t_philo *philo)
{
	if (checkdie(philo) == 1)
	{
		return ;
	}
	pthread_mutex_lock(&philo->all->print);
	if (checkdie(philo) == 1)
	{
		pthread_mutex_unlock(&philo->all->print);
		return ;
	}
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
		if (death(&philo[i]) == 1)
		{
			//unlock(philo);
			pthread_mutex_lock(&philo->all->checkdeath);
			philo->all->token = 1;
			pthread_mutex_unlock(&philo->all->checkdeath);
			break;
		}
		if (philo->all->nbreat > 0)
		{
			if (bienmanger(philo) == 1)
			{
				//unlock(philo);
				pthread_mutex_lock(&philo->all->checkdeath);
				philo->all->token = 1;
				pthread_mutex_unlock(&philo->all->checkdeath);
				break;
			}
		}
		//if (philo->all->token == 1)
		//	unlock(philo);
		i++;
	}
	return NULL;
}

int		death(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->lmeal);
	if ((get_current_time() - philo->lasteat) >= philo->all->time2die)
	{
		//philo->all->token = 1;
		pthread_mutex_lock(&philo->all->print);
		printf("%lld %d died\n", (get_current_time() - philo->all->time), philo->id);
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
	//exit(1);
	while (++i < all->nphilo)
		pthread_join(all->philo[i].thread, NULL);
	/*i = -1;
	while (++i < all->nphilo)
	{
		pthread_mutex_destroy(all->philo[i].fork);
		pthread_mutex_destroy(all->philo[i].rfork);
	}
	printf("er\n");
	pthread_mutex_destroy(all->fork);
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->checkdeath);
	pthread_mutex_destroy(&all->lmeal);
	pthread_mutex_destroy(&all->nbr);*/
}

int		bienmanger(t_philo *philo)
{
	int	i;

	i = -1;
	//philo->all->alleat = 1;
	while (++i < philo->all->nphilo)
	{
		pthread_mutex_lock(&philo->all->nbr);
		if (philo[i].nbrmeal >= philo->all->nbreat)
			philo[i].fini = 1;
		pthread_mutex_unlock(&philo->all->nbr);
		if (philo[i].fini != 1)
		{
			//philo->all->alleat = 0;
			return (0);
		}
	}
	return (1);
}

int		checkdie(t_philo *philo)
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
