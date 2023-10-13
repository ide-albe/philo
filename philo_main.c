/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:04:49 by ide-albe          #+#    #+#             */
/*   Updated: 2023/10/13 20:45:46 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	check_every_argv(char **argv)
{
	int	i;

	i = 1;
	while (i <= 4)
	{
		if (check_argv_num(argv[i]) == -1)
			return (-1);
		if (ft_atoi(argv[i]) > 2147483647 || ft_atoi(argv[i]) < -2147483648)
			return (-1);
		i++;
	}
	if (argv[5])
	{
		if (ft_atoi(argv[5]) == 0)
			return (-1);
		if (check_argv_num(argv[5]) == -1)
			return (-1);
	}
	return (0);
}

void	free_philos_data(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->nphilo)
	{
		pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
	}
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6 || check_every_argv(argv) == -1)
	{
		printf("error de argumentos o valores numerico incorrectos\n");
		return (0);
	}
	if (ft_atoi(argv[1]) == 0)
		return (0);
	if (ft_atoi(argv[1]) == 1)
	{
		is_one(argv);
		return (0);
	}
	data = init_data(argv);
	data.all_meals = 0;
	data.death_check = 0;
	mutex_init(&data);
	assign_philos_data(&data);
	simulation(&data);
	ft_join(&data);
	ft_destroy(&data);
	free_philos_data(&data);
	return (0);
}
