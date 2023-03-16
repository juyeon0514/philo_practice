/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:37:43 by juykang           #+#    #+#             */
/*   Updated: 2023/03/17 00:41:07 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_time(t_philo *philo, t_info *info)
{
	long	start;
	long	now;

	start = ft_get_time();
	while (philo->state != DIED)
	{
		now = ft_get_time();
		if ((now - start) >= info->die_time)
		{
			philo->state = DIED;
			break ;
			usleep(100);
		}
	}
}

void	ft_eat_philo(t_philo *philo, t_info *info, t_mutex_struct *mutex)
{
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_lock(&(mutex->fork[philo->right]));
		ft_philo_print(philo->idx, info->start_time, "has taken a fork", philo);
		pthread_mutex_lock(&(mutex->fork[philo->left]));
		ft_philo_print(philo->idx, info->start_time, \
		"has taken an another fork", philo);
		philo->last_time = ft_get_time();
		philo->state = EAT;
		ft_philo_print(philo->idx, info->start_time, "is eating", philo);
		philo->eat_cnt++;
		while (ft_get_time() < philo->last_time + info->eat_time)
			;
		pthread_mutex_unlock(&(mutex->fork[philo->left]));
		pthread_mutex_unlock(&(mutex->fork[philo->right]));
	}
	else if (philo->idx % 2 == 1)
	{
		pthread_mutex_lock(&(mutex->fork[philo->left]));
		ft_philo_print(philo->idx, info->start_time, "has taken a fork", philo);
		pthread_mutex_lock(&(mutex->fork[philo->right]));
		ft_philo_print(philo->idx, info->start_time, \
		"has taken an another fork", philo);
		philo->last_time = ft_get_time();
		philo->state = EAT;
		ft_philo_print(philo->idx, info->start_time, "is eating", philo);
		philo->eat_cnt++;
		while (ft_get_time() < philo->last_time + info->eat_time)
			;
		pthread_mutex_unlock(&(mutex->fork[philo->right]));
		pthread_mutex_unlock(&(mutex->fork[philo->left]));
	}
}
