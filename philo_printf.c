/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:37:36 by juykang           #+#    #+#             */
/*   Updated: 2023/03/16 23:28:30 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_print(int num, long start_time, char *comment, t_philo *philo)
{
	long long	now;

	now = ft_get_time();
	if (now == -1)
		return (-1);
	pthread_mutex_lock(&(philo->mutex->print));
	printf("%lld %d %s\n", now - start_time, num, comment);
	pthread_mutex_unlock(&(philo->mutex->print));
	return (0);
}
