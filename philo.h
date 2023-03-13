/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:37:34 by juykang           #+#    #+#             */
/*   Updated: 2023/03/13 17:17:59 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> // usleep, gettimeofday
# include <pthread.h> // pthread_, pthread_mutex_
# include <signal.h> // kill
# include <sys/wait.h> // waitpid
# include <stdlib.h>
# include <stdio.h>

enum e_error
{
	ERROR_ARGUMENT_WRONG,
	ERROR_MALLOC,
	ERROR_FREE,
	ERROR_THREAD_CREATE,
	ERROR_THREAD_DETACH,
	ERROR_THREAD_JOIN,
	ERROR_SLEEP,
	ERROR_GET_TIME,
	ERROR_MUTEX_INIT,
	ERROR_MUTEX_DESTROY,
	ERROR_MUTEX_LOCK,
	ERROR_MUTEX_UNLOCK
};

typedef struct s_philo
{
	pthread_t	thread;
	int			idx;
	int			left;
	int			right;
	int			eat_cnt;
	struct		*s_info;
}	t_philo;

typedef struct s_info
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	struct timeval	start_time;
	int				die_time;
	int				eat_time;
	int				think_time;
	int				philo_number;
	int				must_eat_cnt;
}	t_info;

#endif