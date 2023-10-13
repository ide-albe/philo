/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:04:49 by ide-albe          #+#    #+#             */
/*   Updated: 2023/10/13 19:47:14 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(char **argv)
{
	t_data	data;

	data.nphilo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		data.times_must_eat = ft_atoi(argv[5]);
	}
	else
		data.times_must_eat = -1;
	return (data);
}

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nphilo);
	while (i < data->nphilo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mssg, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
}

void	assign_philos_data(t_data *data)
{
	int			i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nphilo);
	while (i < data->nphilo)
	{
		if (i == (data->nphilo - 1))
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = 0;
		}
		else
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = i + 1;
		}
		data->philo[i].data = data;
		data->philo[i].philo_pos = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].meals = 0;
		pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		pthread_mutex_init(&data->deathcheck_mutex, NULL);
		i++;
	}
}
