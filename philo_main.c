/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:42:09 by juykang           #+#    #+#             */
/*   Updated: 2023/03/13 17:40:31 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_mutex_fork(t_info *info, int *err)
{
	int	i;

	if (pthread_mutex_init(&(info->print), NULL))
		err = 1;
	info->fork = malloc(sizeof(pthread_mutex_t) * info->philo_number);
	while (i < info->philo_number)
	{
		if (pthread_mutex_init(&(info->fork), NULL))
			err = 1;
		i++;
	}
}

void	ft_info_init(t_info	*info, int argc, char **argv, int *err)
{
	info->philo_number = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->think_time = ft_atoi(argv[4]);
	info->start_time = gettimeofday(&start_time, NULL);
	if (philo_number <= 0 || die_time < 0 || eat_time < 0 || think_time < 0 \
	|| start_time < 0)
		print_error(0);
	if (argc == 6)
	{
		info->must_eat_cnt = ft_atoi(argv[5]);
		if (must_eat_cnt < 0)
			print_error(0);
	}
	ft_init_mutex(info, err);
}

void	ft_set_philo(t_philo **philo, t_info *info)
{
	int	i;

	*philo = malloc(sizeof(philo) * info->philo_number);
	i = 0;
	while (i < info->philo_number)
	{
		(*philo)[i].idx = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % info->philo_number;
		(*philo)[i].eat_cnt = 0;
		(*philo)[i].s_info = info;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_info	info;
	int		err;

	if (argc != 5 || argc != 6)
	{
		print_error(0);
		return (1);
	}
	err = 0;
	memset(&info, 0, sizeof(t_info));
	ft_info_init(info, argc, argv, &err);
	if (err)
		return (1);
	ft_set_philo(&philo, info);
	ft_seat_philo(philo, info);
}
