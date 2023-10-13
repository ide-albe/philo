/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:04:49 by ide-albe          #+#    #+#             */
/*   Updated: 2023/10/13 20:45:29 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulation(t_data *data)
{
	int	i;

	data->time = get_time_in_ms();
	i = 0;
	pthread_mutex_lock(&data->mssg);
	pthread_mutex_lock(&data->eat_lock);
	while (i < data->nphilo)
	{
		pthread_mutex_unlock(&data->mssg);
		pthread_mutex_unlock(&data->eat_lock);
		data->philo[i].last_meal = data->time;
		pthread_create(&data->philo[i].thread, NULL, philo, &data->philo[i]);
		i++;
	}
	death_check(data->philo);
}

void	*philo(void *data)
{
	t_philo	*philo;
	t_data	*param;

	philo = (t_philo *) data;
	param = philo->data;
	(void)param;
	while (philo->data->death_check != 1 && philo->data->all_meals != 1)
	{
		if ((philo->philo_pos % 2) == 0)
			left_has_taken_fork(philo);
		else
			right_has_taken_fork(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (0);
}

void	line_redu1(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_lock(&data->mssg);
	printf("\n %ld %i died", (get_time_in_ms()
			- data->time), philo[i].philo_pos);
	pthread_mutex_unlock(&data->mssg);
	pthread_mutex_lock(&data->deathcheck_mutex);
	data->death_check = 1;
	pthread_mutex_unlock(&data->deathcheck_mutex);
	pthread_mutex_unlock(&philo[i].last_meal_mutex);
}

void	line_redu2(t_data *data, t_philo *philo)
{
	int		i;
	int		tme_cpy;
	int		*data_cpy;

	i = 0;
	data = philo->data;
	tme_cpy = data->times_must_eat;
	data_cpy = malloc(sizeof(int) * data->nphilo);
	pthread_mutex_lock(&philo[i].meal_mutex);
	data_cpy[i] = philo[i].meals;
	pthread_mutex_unlock(&philo[i].meal_mutex);
	while (tme_cpy != -1 && i < data->nphilo
		&& data_cpy[i] >= tme_cpy)
	{
		i++;
		pthread_mutex_lock(&philo[i].meal_mutex);
		data_cpy[i] = philo[i].meals;
		pthread_mutex_unlock(&philo[i].meal_mutex);
	}
	if (i == data->nphilo)
		data->all_meals = 1;
	free(data_cpy);
}

void	death_check(t_philo *philo)
{
	int		i;
	t_data	*data;

	i = 0;
	data = philo->data;
	while (data->all_meals != 1)
	{
		i = -1;
		while (++i < data->nphilo && data->death_check != 1)
		{
			pthread_mutex_lock(&philo[i].last_meal_mutex);
			if ((get_time_in_ms() - philo[i].last_meal) > data->time_to_die)
			{
				line_redu1(data, philo, i);
				return ;
			}
			pthread_mutex_unlock(&philo[i].last_meal_mutex);
			usleep(100);
		}
		line_redu2(data, philo);
	}
}
