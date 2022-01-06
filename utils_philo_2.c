/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:34:59 by gnaida            #+#    #+#             */
/*   Updated: 2021/10/20 16:38:30 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time_in_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_wait_for_time(unsigned long wait_time, t_philo *philo)
{
	unsigned long	begin_time;

	begin_time = ft_get_time_in_millis();
	while ((ft_get_time_in_millis() - begin_time) < wait_time)
	{
		if (philo->data->death_flag)
			break ;
		usleep(10);
	}
}

unsigned long	ft_if_min(int n, int fd)
{
	long int	longn;

	longn = n;
	if (longn < 0)
	{
		write(fd, "-", 1);
		return (-1 * longn);
	}
	return (longn);
}

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long int	longn;
	long int	rank;

	longn = ft_if_min(n, fd);
	rank = 1;
	while (longn >= 10)
	{
		longn = longn / 10;
		rank = rank * 10;
	}
	longn = n;
	if (longn < 0)
		longn = -1 * longn;
	while (rank >= 10)
	{
		c = longn / rank + '0';
		write(fd, &c, 1);
		longn = longn - rank * (longn / rank);
		rank = rank / 10;
	}
	c = longn + '0';
	write(fd, &c, 1);
}
