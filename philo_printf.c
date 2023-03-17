/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:37:36 by juykang           #+#    #+#             */
/*   Updated: 2023/03/17 12:51:28 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_print(int num, long time, char *comment, t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->print));
	if (philo->state != DIED)
		printf("%ld %d %s\n", time, num, comment);
	pthread_mutex_unlock(&(philo->mutex->print));
	return (0);
}
