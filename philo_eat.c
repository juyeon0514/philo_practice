/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:37:43 by juykang           #+#    #+#             */
/*   Updated: 2023/03/17 13:46:24 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep_or_think(t_philo *philo, t_info *info)
{
	philo->last_sleep = ft_get_time();
	ft_philo_print(philo->idx, philo->last_sleep - info->start_time, \
"is sleeping", philo);
	while (ft_get_time() < philo->last_sleep + info->sleep_time)
		;
	ft_philo_print(philo->idx, ft_get_time() - info->start_time, \
"is thinking", philo);
	usleep(100);
}

void	ft_fork_pick(t_philo *philo, t_info *info, t_mutex_struct *mutex)
{
	if (philo->idx % 2 != 0)
		pthread_mutex_lock(&(mutex->fork[philo->left]));
	else
		pthread_mutex_lock(&(mutex->fork[philo->right]));
	ft_philo_print(philo->idx, ft_get_time() - info->start_time, \
"has taken a fork", philo);
	if (philo->idx % 2 != 0)
		pthread_mutex_lock(&(mutex->fork[philo->right]));
	else
		pthread_mutex_lock(&(mutex->fork[philo->left]));
	ft_philo_print(philo->idx, ft_get_time() - info->start_time, \
"has taken an another fork", philo);
}

void	ft_eat_philo(t_philo *philo, t_info *info, t_mutex_struct *mutex)
{
	pthread_mutex_lock(&(mutex->meal));
	philo->last_time = ft_get_time();
	ft_philo_print(philo->idx, philo->last_time - info->start_time, \
"is eating", philo);
	pthread_mutex_unlock(&(mutex->meal));
	while (ft_get_time() < philo->last_time + info->eat_time)
		;
	philo->eat_cnt++;
	pthread_mutex_unlock(&(mutex->fork[philo->right]));
	pthread_mutex_unlock(&(mutex->fork[philo->left]));
}
