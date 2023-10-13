/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:04:49 by ide-albe          #+#    #+#             */
/*   Updated: 2023/10/13 18:31:53 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_message(philo, "is thinking");
	(void)data;
}

void	is_sleeping(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_message(philo, "is sleeping");
	ft_sleep(data, philo->data->time_to_sleep);
}

void	left_has_taken_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	print_message(philo, "has taken fork");
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	print_message(philo, "has taken fork");
	pthread_mutex_lock(&data->eat_lock);
	print_message(philo, "is eating");
	pthread_mutex_unlock(&data->eat_lock);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	ft_sleep(data, data->time_to_eat);
}

void	right_has_taken_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	print_message(philo, "has taken fork");
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	print_message(philo, "has taken fork");
	pthread_mutex_lock(&data->eat_lock);
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&data->eat_lock);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	ft_sleep(data, data->time_to_eat);
}
