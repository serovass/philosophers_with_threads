/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:20:40 by gnaida            #+#    #+#             */
/*   Updated: 2021/11/26 14:40:16 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse_argc(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		data->death_flag = 0;
		data->philos = ft_atoi(argv[1]);
		data->die_time = ft_atoi(argv[2]);
		data->eat_time = ft_atoi(argv[3]);
		data->sleep_time = ft_atoi(argv[4]);
		if (argc == 6)
			data->lunches = ft_atoi(argv[5]);
		else
			data->lunches = -1;
		if (data->philos <= 0 || data->philos > 200)
			;
		else if (data->die_time < 60)
			;
		else if (data->eat_time < 60)
			;
		else if (data->sleep_time < 60)
			;
		else if (data->lunches > 0 || data->lunches == -1)
			return (0);
	}
	ft_write_msg("wrong usage!!!\n");
	return (-1);
}

int	ft_mutex_init(t_data *data)
{
	int	i;

	data->mtx_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
			* data->philos);
	if (data->mtx_forks == NULL)
	{
		ft_write_msg("Error! =(\n");
		return (-1);
	}
	i = 0;
	while (i < data->philos)
	{
		pthread_mutex_init(&data->mtx_forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mtx_msg, NULL);
	pthread_mutex_init(&data->mtx_lunch_time, NULL);
	pthread_mutex_init(&data->mtx_death, NULL);
	return (0);
}

void	ft_mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		pthread_mutex_destroy(&data->mtx_forks[i]);
		i++;
	}
	free(data->mtx_forks);
	pthread_mutex_destroy(&data->mtx_msg);
	pthread_mutex_destroy(&data->mtx_lunch_time);
	pthread_mutex_destroy(&data->mtx_death);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_parse_argc(argc, argv, &data) < 0)
		return (0);
	if (ft_mutex_init(&data) < 0)
		return (0);
	ft_philo_threads(&data);
	ft_mutex_destroy(&data);
	return (0);
}
