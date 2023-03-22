/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:00:57 by juykang           #+#    #+#             */
/*   Updated: 2023/03/22 18:25:51 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_error(int error)
{
	if (error == ERROR_ARGUMENT_WRONG)
		printf("%s\n", "ERROR_ARGUMENT_WRONG");
	else if (error == ERROR_MALLOC)
		printf("%s\n", "ERROR_MALLOC");
	else if (error == ERROR_FREE)
		printf("%s\n", "ERROR_FREE");
	else if (error == ERROR_THREAD_CREATE)
		printf("%s\n", "ERROR_THREAD_CREATE");
	else if (error == ERROR_THREAD_JOIN)
		printf("%s\n", "ERROR_THREAD_JOIN");
	else if (error == ERROR_SLEEP)
		printf("%s\n", "ERROR_SLEEP");
	else if (error == ERROR_GET_TIME)
		printf("%s\n", "ERROR_GET_TIME");
	else if (error == ERROR_MUTEX_INIT)
		printf("%s\n", "ERROR_MUTEX_INIT");
	else if (error == ERROR_MUTEX_DESTROY)
		printf("%s\n", "ERROR_MUTEX_DESTROY");
	else if (error == ERROR_MUTEX_LOCK)
		printf("%s\n", "ERROR_MUTEX_LOCK");
	else
		printf("%s\n", "ERROR_MUTEX_UNLOCK");
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	num;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (sign * num);
}

long	ft_get_time(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return ((cur.tv_sec * 1000) + (cur.tv_usec / 1000));
}

int	ft_isnum(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] >= '0' && argv[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_msleep(long time)
{
	long	end;

	end = ft_get_time() + time;
	while (ft_get_time() < end)
		usleep(100);
	return (0);
}
