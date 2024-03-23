/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:54:53 by bsafi             #+#    #+#             */
/*   Updated: 2024/03/23 14:55:11 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lockd(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->checkdeath);
	philo->all->token = 1;
	pthread_mutex_unlock(&philo->all->checkdeath);
}
