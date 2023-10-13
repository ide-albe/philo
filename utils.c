/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:06:48 by ide-albe          #+#    #+#             */
/*   Updated: 2023/10/13 20:05:17 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sig;
	long	sol;

	i = 0;
	sig = 1;
	sol = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
		{
			sig *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sol *= 10;
		sol += str[i] - '0';
		i++;
	}
	return (sol * sig);
}

void	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nphilo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nphilo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->mssg);
	pthread_mutex_destroy(&data->deathcheck_mutex);
	return ;
}

void	print_message(t_philo *philo, char *message)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->mssg);
	if (data->death_check != 1 && data->all_meals != 1)
	{
		printf("\n %ld %i %s", (get_time_in_ms()
				- data->time), philo->philo_pos, message);
	}
	pthread_mutex_unlock(&data->mssg);
	return ;
}

void	is_one(char **argv)
{
	printf("\n 0 1 has taken a fork");
	usleep((ft_atoi(argv[2]) * 1000));
	printf("\n %ld 1 died\n", (ft_atoi(argv[2]) + 1));
}
