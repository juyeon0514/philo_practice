/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:21:49 by juykang           #+#    #+#             */
/*   Updated: 2023/03/14 15:33:19 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_init(t_mutex_struct *mutex_struct, t_info *info)
{
	int	i;

	if (pthread_mutex_init(&(mutex_struct->print), NULL))
		ft_print_error(9);
	if (pthread_mutex_init(&(mutex_struct->meal), NULL))
		ft_print_error(9);
	mutex_struct->fork = malloc(sizeof(pthread_mutex_t) * info->philo_number);
	if (!mutex_struct->fork)
		ft_print_error(1);
	i = 0;
	while (i < info->philo_number)
	{
		if (pthread_mutex_init(&(mutex_struct->fork[i]), NULL))
			ft_print_error(9);
		i++;
	}
}

void	ft_set_philo(t_philo **philo, t_info *info)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * info->philo_number);
	if (!philo)
		ft_print_error(1);
	i = 0;
	while (i < info->philo_number)
	{
		(*philo)[i].idx = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % info->philo_number;
		(*philo)[i].eat_cnt = 0;
		(*philo)[i].last_time = ft_get_time();
		(*philo)[i].info = info;
		//printf("%d %d\n", i, philo[i].idx);
		i++;
	}
}

// int	ft_is_correct_arg(int argc, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (i < argc)
// 	{
// 		if (!ft_isnum(argv[i]))
// 			return (1);
// 		if (ft_atoi(argv[i]) < 0)
// 			return (1);
// 	}
// 	return (0);
// }

int	ft_info_init(t_info	*info, int argc, char **argv)
{
	//if (ft_is_correct_arg(argc, argv))
		//return (1);
	info->philo_number = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->think_time = ft_atoi(argv[4]);
	info->start_time = ft_get_time();
	if (info->philo_number <= 0 || info->die_time < 0 || info->eat_time < 0 || info->think_time < 0)
		return (1);
	if (argc == 6)
	{
		info->must_eat_cnt = ft_atoi(argv[5]);
		if (info->must_eat_cnt < 0)
			return (1);
	}
	return (0);
}
