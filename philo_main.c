/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:42:09 by juykang           #+#    #+#             */
/*   Updated: 2023/03/17 00:50:15 by juykang          ###   ########seoul.kr  */
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
	while (philo->state != DIED)
	{
		if (philo->idx % 2 == 0)
			usleep(info->eat_time * 1000);
		ft_eat_philo(philo, info, mutex_struct);
		philo->state = SLEEP;
		ft_philo_print(philo->idx, info->start_time, "is sleeping", philo);
		philo->state = THINKING;
		if (info->finish)
			break ;
		ft_check_time(philo, info);
		ft_philo_print(philo->idx, info->start_time, "is thinking", philo);
	}
	return (0);
}

void	ft_monitor(t_philo *philo, t_info *info, t_mutex_struct *mutex)
{
	int			i;
	long		now;

	while (!info->finish)
	{
		i = 0;
		while (i < info->philo_number && philo->state != DIED)
		{
			pthread_mutex_lock(&(mutex->monitor));
			now = ft_get_time();
			if (now - philo[i].last_time > info->die_time)
			{
				philo->state = DIED;
				ft_philo_print(philo->idx, info->start_time, "is died", philo);
			}
			pthread_mutex_unlock(&(mutex->monitor));
		}
		if (philo->state == DIED)
			break ;
		if ((philo->eat_cnt != 0) && (philo->eat_cnt == info->must_eat_cnt))
		{
			philo->state = DIED;
			break ;
		}
	}
}

void	ft_seat_philo(t_philo *philo, t_info *info, t_mutex_struct *mutex)
{
	int	i;

	i = 0;
	while (i < info->philo_number)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_make_thread, (&philo[i])))
			ft_print_error(3);
		i++;
	}
	ft_monitor(philo, info, mutex);
	i = 0;
	while (i < info->philo_number)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	//ft_free_thread(philo, info);
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
	if (info.philo_number <= 1)
		return (ft_print_error(1));
	if (ft_set_philo(&philo, &info, &mutex_struct))
		return (ft_print_error(1));
	ft_mutex_init(&mutex_struct, &info);
	ft_seat_philo(philo, &info, &mutex_struct);
}
