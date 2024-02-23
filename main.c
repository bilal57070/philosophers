/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:43:33 by bsafi             #+#    #+#             */
/*   Updated: 2024/02/20 19:39:09 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_all		all;
	//pthread_t	tid;

	if (ac > 6 || ac < 5)
	{
		printf("error nbr args\n");
		exit(1);
	}
	all.token = 0;
	all.time2die = (ft_atoi(av[2]) * 1000);
	checkarg(av);
	getnphilo(&all, av);
	//tid = pthread_self();
	//printf("ALORS %ld\n", tid);
	makethread(&all);
	//printf("ALORS %ld\n", tid);
	//pthread_join(tid, NULL);
	/*int	i;

	i = 0;
	while (i < all.nphilo)
	{
		printf("test\n");
		pthread_create(&all.philo[i].thread, NULL, thread_routine, &all);
	}*/
	return (0);
}
