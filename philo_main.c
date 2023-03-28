/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:42:09 by juykang           #+#    #+#             */
/*   Updated: 2023/03/27 18:38:47 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_make_thread(void *arg)
{
	t_philo			*philo;
	t_info			*info;
	t_mutex_struct	*mutex_struct;

	philo = (t_philo *)arg;
	info = philo->info;
	mutex_struct = philo->mutex;
	if (philo->idx % 2 == 0)
		usleep(500);
	while (!info->dead)
	{
		ft_fork_pick(philo, info, mutex_struct);
		ft_eat_philo(philo, info, mutex_struct);
		if (info->finish)
			break ;
		ft_sleep_or_think(philo, info);
		usleep(200);
	}
	return (0);
}

void	ft_free_thread(t_philo *philo, t_info *info, t_mutex_struct *mutex)
{
	int	i;

	i = 0;
	if (info->philo_number == 1)
		pthread_detach(philo[i].thread);
	else
	{
		while (i < info->philo_number)
		{
			if (pthread_mutex_destroy(&(mutex->fork[i])))
				ft_print_error(8);
			i++;
		}
	}
	pthread_mutex_destroy(&(mutex->print));
	pthread_mutex_destroy(&(mutex->meal));
	pthread_mutex_destroy(&(mutex->monitor));
	free(philo);
	free(mutex->fork);
}

void	ft_monitor(t_philo *philo, t_info *info, t_mutex_struct *mutex)
{
	int			i;

	while (!info->finish)
	{
		i = 0;
		pthread_mutex_lock(&(mutex->monitor));
		while (i < info->philo_number && info->dead != 1)
		{
			if (ft_get_time() - philo[i].last_time >= info->die_time)
			{
				ft_philo_print(philo[i].idx, \
				ft_get_time() - info->start_time, "died", philo);
				info->dead = 1;
			}
			if (philo[i].eat_cnt != 0 && philo[i].eat_cnt == info->must_eat_cnt)
			{
				info->finish = 1;
				break ;
			}
			i++;
		}
		pthread_mutex_unlock(&(mutex->monitor));
		if (info->dead)
			break ;
	}
}

void	ft_seat_philo(t_philo *philo, t_info *info, t_mutex_struct *mutex)
{
	int	i;

	i = 0;
	info->start_time = ft_get_time();
	while (i < info->philo_number)
	{
		philo[i].last_time = info->start_time;
		philo[i].last_sleep = info->start_time;
		if (pthread_create(&(philo[i].thread), NULL, \
		ft_make_thread, (&philo[i])))
			ft_print_error(3);
		i++;
	}
	ft_monitor(philo, info, mutex);
	i = 0;
	while (info->philo_number != 1 && i < info->philo_number)
	{
		if (pthread_join(philo[i].thread, NULL))
			ft_print_error(4);
		i++;
	}
	ft_free_thread(philo, info, mutex);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_mutex_struct	mutex_struct;
	t_info			info;

	if (argc != 5 && argc != 6)
		return (ft_print_error(0));
	memset(&info, 0, sizeof(info));
	if (ft_info_init(&info, argc, argv))
		return (ft_print_error(0));
	ft_mutex_init(&mutex_struct, &info);
	if (ft_set_philo(&philo, &info, &mutex_struct))
		return (ft_print_error(1));
	ft_seat_philo(philo, &info, &mutex_struct);
}
