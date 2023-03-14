/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:42:09 by juykang           #+#    #+#             */
/*   Updated: 2023/03/14 15:33:57 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_make_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	//printf("i'm %dth philosopher\n", philo->idx);
	/*while (!philo->state)
	{
		
	}*/
	return (0);
}

void	ft_seat_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_number)
	{
		printf("3 i'm %dth philosopher\n", philo[i].idx);
		if (pthread_create(&philo[i].thread, NULL, ft_make_thread, (&philo[i])))
			ft_print_error(3);
		i++;
	}
	//ft_is_philo_finish(philo, info);
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
	int				i;

	if (argc != 5 && argc != 6)
		return (ft_print_error(0));
	memset(&info, 0, sizeof(info));
	if (ft_info_init(&info, argc, argv))
		return (ft_print_error(0));
	//philo = malloc(sizeof(philo) * info.philo_number);
	ft_set_philo(&philo, &info);
	i = 0;
	if (pthread_mutex_init(&(mutex_struct.print), NULL))
		ft_print_error(9);
	if (pthread_mutex_init(&(mutex_struct.meal), NULL))
		ft_print_error(9);
	mutex_struct.fork = malloc(sizeof(pthread_mutex_t) * info.philo_number);
	if (!mutex_struct.fork)
		ft_print_error(1);
	for (int j = 0; j < info.philo_number; j++)
		printf("1 i'm %dth philosopher\n", philo[j].idx);
	i = 0;
	while (i < info.philo_number)
	{
		for (int j = 0; j < info.philo_number; j++)
			printf("4 %d i'm %dth philosopher\n", j, philo[j].idx);
		if (pthread_mutex_init(&(mutex_struct.fork[i]), NULL))
			ft_print_error(9);
		i++;
	}
	for (int j = 0; j < info.philo_number; j++)
		printf("2 %d i'm %dth philosopher\n", j, philo[j].idx);
	//ft_mutex_init(mutex_struct, &info);
	ft_seat_philo(philo, &info);
}
