/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:03:05 by gnaida            #+#    #+#             */
/*   Updated: 2021/10/20 21:34:33 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_data
{
	int				philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				lunches;
	int				death_flag;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_msg;
	pthread_mutex_t	mtx_death;//
	pthread_mutex_t	mtx_lunch_time;
}	t_data;

typedef struct s_philo
{
	int				philo_id;
	unsigned long	simulation_start;
	unsigned long	last_time_ate;
	int				lunches_to_eat;
	t_data			*data;
}	t_philo;

int				ft_atoi(const char *str);
void			ft_write_msg(char *msg);
unsigned long	ft_get_time_in_millis(void);
void			ft_wait_for_time(unsigned long wait_time, t_philo *philo);
int				ft_check_if_death(t_philo *philo);
void			ft_philo_threads(t_data *data);
void			*simulation_fanction(void *argument);
void			ft_putnbr_fd(int n, int fd);

#endif
