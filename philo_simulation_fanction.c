/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation_fanction.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:11:58 by gnaida            #+#    #+#             */
/*   Updated: 2021/11/26 14:42:41 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_write_philo_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->mtx_msg);
	if (philo->data->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->mtx_msg);
		return ;
	}
	else if (msg[1] == 'd')
	{
		philo->data->death_flag = 1;
		pthread_mutex_unlock(&philo->data->mtx_forks[philo->philo_id % philo->data->philos]);//
		pthread_mutex_unlock(&philo->data->mtx_forks[philo->philo_id - 1]);//
	}
	ft_putnbr_fd((int)ft_get_time_in_millis() \
			- (int)philo->simulation_start, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->philo_id, 1);
	ft_write_msg(msg);
	pthread_mutex_unlock(&philo->data->mtx_msg);
}

static int	ft_take_forks(t_philo *philo, int fork_f, int fork_s)
{
	pthread_mutex_lock(&philo->data->mtx_forks[fork_f]);
	ft_write_philo_msg(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->data->mtx_forks[fork_s]);
	ft_write_philo_msg(philo, " has taken a fork\n");
	return (0);
}

static void	ft_eat(t_philo *philo)
{
	int	fork_f;
	int	fork_s;

	fork_f = philo->philo_id - 1;
	fork_s = philo->philo_id % philo->data->philos;
	if (!(philo->philo_id % 2) && ft_take_forks(philo, fork_f, fork_s))
		return ;
	else if ((philo->philo_id % 2) && ft_take_forks(philo, fork_s, fork_f))
		return ;
	ft_write_philo_msg(philo, " is eating\n");
	//pthread_mutex_lock(&philo->data->mtx_lunch_time);
	philo->last_time_ate = ft_get_time_in_millis();
	//pthread_mutex_unlock(&philo->data->mtx_lunch_time);
	ft_wait_for_time(philo->data->eat_time, philo);
	pthread_mutex_unlock(&philo->data->mtx_forks[fork_f]);
	pthread_mutex_unlock(&philo->data->mtx_forks[fork_s]);
}

void	*thread_death_cheak(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	while (philo->data->death_flag != 1 && philo->lunches_to_eat != 0)
	{
		if (philo->data->death_flag != 1 && \
		(ft_get_time_in_millis() - philo->last_time_ate) \
		> (unsigned long)philo->data->die_time)
		{
			ft_write_philo_msg(philo, " died\n");
			pthread_mutex_unlock(&philo->data->mtx_death);
			return (NULL);
			}
			usleep(10);
	}
	return (NULL);
}

void	*simulation_fanction(void *argument)
{
	t_philo	*philo;
	pthread_t thread_death;

	philo = (t_philo *)argument;
	philo->simulation_start = ft_get_time_in_millis();
	philo->last_time_ate = philo->simulation_start;
	pthread_create(&thread_death, NULL, thread_death_cheak, philo);
	while (philo->data->death_flag != 1)
	{
		if (philo->lunches_to_eat == 0)
			break ;
		ft_eat(philo);
		if (philo->lunches_to_eat > 0)
			philo->lunches_to_eat--;
		ft_write_philo_msg(philo, " is sleeping\n");
		ft_wait_for_time(philo->data->sleep_time, philo);
		ft_write_philo_msg(philo, " is thinking\n");
		if (philo->data->philos % 2)
			ft_wait_for_time(1, philo);
	}
	return (NULL);
}
