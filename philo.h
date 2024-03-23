/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:14:28 by bsafi             #+#    #+#             */
/*   Updated: 2024/03/23 14:53:58 by bsafi            ###   ########.fr       */
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
# include <sys/time.h>

long int	ft_atoi(const char *str);
void		check(int a);
void		checkarg(char **av);

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*rfork;
	int				id;
	int				nbrmeal;
	int				fini;
	long long		lasteat;
	struct s_all	*all;
}			t_philo;

typedef struct s_all
{
	int				token;
	int				nphilo;
	int				nbreat;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	long long		time;
	pthread_t		death;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	lmeal;
	pthread_mutex_t	nbr;
	pthread_mutex_t	checkdeath;
	t_philo			*philo;
}			t_all;

void		initall(t_all *all, char **av);
void		makethread(t_all *all);
void		*thread_routine(void *data);
void		initstruc(t_all *all);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		initmut(t_all *all);
long long	get_current_time(void);
void		*ryuk(void *data);
int			death(t_philo *philo);
void		unlock(t_philo *philo);
int			bienmanger(t_philo *philo);
int			ft_usleep(long long milliseconds);
int			checkdie(t_philo *philo);
void		end(t_all *all);
int			checkeat(t_philo *philo);
void		theone(t_all *all);
void		eating2(t_philo *philo);
void		eating3(t_philo *philo);
void		lockd(t_philo *philo);

#endif