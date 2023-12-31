/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:04:49 by ide-albe          #+#    #+#             */
/*   Updated: 2023/10/14 17:20:35 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	ft_time_diff(time_t past, time_t pre)
{
	return (pre - past);
}

void	ft_sleep(t_data *data, time_t sleep)
{
	time_t	wake_up;

	wake_up = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->deathcheck_mutex);
		if (data->death_check)
		{
			pthread_mutex_unlock(&data->deathcheck_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->deathcheck_mutex);
		if (ft_time_diff(wake_up, get_time()) >= sleep)
			break ;
		usleep(50);
	}
}
