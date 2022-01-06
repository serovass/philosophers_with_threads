/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:23:39 by gnaida            #+#    #+#             */
/*   Updated: 2021/11/26 14:40:59 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_get_mem(t_philo **philo, pthread_t **thread, int philos_num)
{
	*philo = (t_philo *)malloc(sizeof(t_philo) * philos_num);
	if (*philo == NULL)
		return (1);
	*thread = (pthread_t *)malloc(sizeof(pthread_t) * philos_num);
	if (*thread == NULL)
	{
		free(philo);
		return (1);
	}
	return (0);
}

void	ft_philo_threads(t_data *data)
{
	int			i;
	t_philo		*philo;
	pthread_t	*thread;

	if (ft_get_mem(&philo, &thread, data->philos))
		return ;
	i = 0;
	while (i < data->philos)
	{
		philo[i].philo_id = i + 1;
		philo[i].lunches_to_eat = data->lunches;
		philo[i].data = data;
		pthread_create(&thread[i], NULL, simulation_fanction, &philo[i]);
		i++;
		usleep(10);
	}
	i = 0;
	while (i < data->philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	free(philo);
	free(thread);
}
