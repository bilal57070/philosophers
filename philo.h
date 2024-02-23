/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:14:28 by bsafi             #+#    #+#             */
/*   Updated: 2024/02/22 00:16:22 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>

long int	ft_atoi(const char *str);
void		check(int a);
void		checkarg(char **av);

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*fork;
	//pthread_mutex_t	*rfork;
	int				id;
	int				eat;
	int				rfork;
	struct	s_all	*all;
	//int				rfork; beely avait mis qu'un mutex pour plus de vitess
}			t_philo;

typedef struct s_all
{
	int				token;
	int				nphilo;
	int				nbreat;
	int				time2die;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}			t_all;

void		getnphilo(t_all *all, char **av);
void		makethread(t_all *all, t_philo *philo);
void		*thread_routine(void *data);
void		eating(char **av);
void		sleeping(char **av);

#endif
//defef