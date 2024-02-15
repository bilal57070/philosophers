/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:43:33 by bsafi             #+#    #+#             */
/*   Updated: 2024/02/15 22:06:30 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_all		all;
	pthread_t	tid;

	if (ac > 6 || ac < 5)
	{
		printf("error nbr args\n");
		exit(1);
	}
	checkarg(av);
	getnphilo(&all, av);
	makethread(&all);
	tid = pthread_self();
	printf("ALORS %ld\n", tid);
	pthread_join(tid, NULL);
	/*int	i;

	i = 0;
	while (i < all.nphilo)
	{
		printf("test\n");
		pthread_create(&all.philo[i].thread, NULL, thread_routine, &all);
	}*/
	return (0);
}
