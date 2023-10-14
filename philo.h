/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:08 by ide-albe          #+#    #+#             */
/*   Updated: 2023/10/14 18:23:32 by ide-albe         ###   ########.fr       */
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
	int					philo_pos;
	pthread_t			thread;
	int					left_fork;
	int					right_fork;
	struct s_data		*data;
	int					meals;
	time_t				last_meal;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		meal_mutex;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t		mssg;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		*fork;
	pthread_mutex_t		deathcheck_mutex;
	long				nphilo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				times_must_eat;
	int					death_check;
	int					all_meals;
	time_t				time;
	t_philo				*philo;
}	t_data;

t_data	init_data(char **argv);
void	death_check(t_philo *philo);
void	mutex_init(t_data *data);
void	assign_philos_data(t_data *data);
void	is_thinking(t_philo *philo);
void	is_sleeping(t_philo *philo);
void	left_has_taken_fork(t_philo *philo);
void	right_has_taken_fork(t_philo *philo);
void	line_redu1(t_data *data, t_philo *philo, int i);
void	line_redu2(t_data *data, t_philo *philo);
void	ft_exit(t_data *data);
void	ft_join(t_data *data);
void	ft_destroy(t_data *data);
time_t	get_time(void);
time_t	ft_time_diff(time_t past, time_t pre);
void	ft_sleep(t_data *data, time_t sleep);
time_t	get_time_in_ms(void);
void	print_message(t_philo *philo, char *message);
long	ft_atoi(const char *str);
void	simulation(t_data *data);
void	*philo(void *data);
int		check_argv_num(char *str);
int		check_every_argv(char **argv);
void	is_one(char **argv);
#endif