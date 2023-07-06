/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:08 by ide-albe          #+#    #+#             */
/*   Updated: 2023/06/19 16:47:59 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo
{
	int				philo_pos;
	int				left_fork;
	int				right_fork;
	int				is_dead;
	struct s_data	*data;
	pthread_t		thread;
	time_t			last_meal;
}	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	time_t			time;
	int				time_to__die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_data;

void		assign_philos_data(t_data *data);
t_data		init_data(char **argv);
int			ft_atoi(char *str);
void		*simulation(void *philo);
void	right_has_taken_fork(t_philo *philo);
void	left_has_taken_fork(t_philo *philo);
void		mutex_init(t_data *data);
void		pthread_init(t_data *data);
time_t  get_time(void);
void	is_sleeping(t_philo *philo);
void    ft_sleep(t_data *data, time_t sleep);
void	is_thinking(t_philo *philo);
void	death_check(t_philo *philo);
#endif