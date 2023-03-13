/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:30:05 by juykang           #+#    #+#             */
/*   Updated: 2023/03/13 14:43:51 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				g_cnt;
pthread_mutex_t	g_mutex;

void	*count(void *arg)
{
	char	*name;
	int		i;

	name = (char *)arg;
	pthread_mutex_lock(&g_mutex);
	g_cnt = 0;
	i = 0;
	while (i < 13)
	{
		printf("%s cnt %d\n", name, g_cnt);
		g_cnt++;
		usleep(1);
		i++;
	}
	pthread_mutex_unlock(&g_mutex);
	return ((void *)arg);
}

int	main(void)
{
	pthread_t	p1;
	pthread_t	p2;
	pthread_t	p3;

	pthread_mutex_init(&g_mutex, NULL);
	pthread_create(&p1, NULL, count, (void *)"thread1");
	pthread_create(&p2, NULL, count, (void *)"thread2");
	pthread_create(&p3, NULL, count, (void *)"thread3");
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_mutex_destroy(&g_mutex);
	return (0);
}
