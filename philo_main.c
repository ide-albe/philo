/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:04:49 by ide-albe          #+#    #+#             */
/*   Updated: 2023/06/19 17:12:50 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(char **argv)
{
	t_data	data;

	data.num_of_philos = ft_atoi(argv[1]);
	data.time_to__die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]) * 1000;
	data.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
	{
		data.times_must_eat = ft_atoi(argv[5]);
	}
	else
		data.times_must_eat = -1;
	return (data);
}

void	death_check(t_philo *philo)
{
	t_data	*data;
	int		i;

	data = philo->data;
	while (1)
	{
		i = -1;
		while (++i)
		{
			if ((get_time() - data->time) - philo[i].last_meal >= data->time_to__die)
			{
				philo->is_dead = 1;
				printf("%li %i is dead\n", (get_time() - data->time), philo[i].philo_pos);
				exit ;
			}
		}
		
	}
}

void	*simulation(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (philo->philo_pos % 2 != 0)
			left_has_taken_fork(philo);
		else
			right_has_taken_fork(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
}

void	is_thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	printf("%li %i is thinking\n", get_time() - data->time, philo->philo_pos);
}

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

void	assign_philos_data(t_data *data)
{
	int			i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_of_philos);
	while (i < data->num_of_philos)
	{
		if (i == (data->num_of_philos - 1))
		{
			data->philo[i].right_fork = 0;
			data->philo[i].left_fork = i;
			data->philo[i].philo_pos = i + 1;
			data->philo[i].is_dead = 0;
			data->philo[i].data = data;
		}
		else
		{
		data->philo[i].philo_pos = i + 1;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = i + 1;
		data->philo[i].is_dead = 0;
		data->philo[i].data = data;
		}
		printf("philo %i, left: %i, right: %i\n", data->philo[i].philo_pos, data->philo[i].left_fork, data->philo[i].right_fork);
		i++;
	}
	i = 0;
	data->time = get_time();
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, simulation, &(data->philo[i]));
		i++;
	}
	death_check(data->philo);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	// sleep(50);
}

void	left_has_taken_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	printf("%li %i has taken a fork\n", get_time() - data->time, philo->philo_pos);
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	printf("%li %i has taken a fork\n", get_time() - data->time, philo->philo_pos);
	printf("%li %i is eating\n",get_time() - data->time, philo->philo_pos);
	usleep(data->time_to_eat);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
}

void	right_has_taken_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	printf("%li %i has taken a fork\n", get_time() - data->time, philo->philo_pos);
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	printf("%li %i has taken a fork\n", get_time() - data->time, philo->philo_pos);
	printf("%li %i is eating\n",get_time() - data->time, philo->philo_pos);
	usleep(data->time_to_eat);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
}

void	is_sleeping(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	data->philo->last_meal = get_time() - data->time;
	printf("%li %i is sleeping\n", get_time() - data->time, philo->philo_pos);
	usleep(philo->data->time_to_sleep);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	philo->is_dead = 0;
	(void)argc;
	data = init_data(argv);
	mutex_init(&data);
	assign_philos_data(&data);
	// sleep(50);
	// printf("hola");
}
