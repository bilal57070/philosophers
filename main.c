/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:43:33 by bsafi             #+#    #+#             */
/*   Updated: 2024/03/05 22:01:10 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_all		*all;

	if (ac > 6 || ac < 5)
	{
		printf("error nbr args\n");
		exit(1);
	}
	all = malloc(sizeof(t_all));
	philo = NULL;
	//all.token = 0;
	//all.time2die = (ft_atoi(av[2]) * 1000);
	checkarg(av);
	initall(all, av);
	all->philo = malloc(sizeof(t_philo) * all->nphilo);
	initmut(all);
	initstruc(all);
	makethread(all); //, philo);
	(void)philo;
	return (0);
}
