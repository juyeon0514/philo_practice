/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:37:34 by juykang           #+#    #+#             */
/*   Updated: 2023/03/14 15:35:49 by juykang          ###   ########seoul.kr  */
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
# include <string.h>
# include <sys/time.h>

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

enum e_state
{
	EAT,
	SLEEP,
	THINKING,
	DIED	
};

typedef struct s_philo
{
	pthread_t				thread;
	int						idx;
	int						left;
	int						right;
	int						eat_cnt;
	struct timeval			last_time;
	struct s_info			*info;
	strcut s_mutex_struct	*mutex;
	int						state;
}	t_philo;

typedef struct s_info
{
	struct timeval	start_time;
	int				die_time;
	int				eat_time;
	int				think_time;
	int				philo_number;
	int				must_eat_cnt;
}	t_info;

typedef struct s_mutex_struct
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
}	t_mutex_struct;

int			ft_print_error(int a);
int				ft_atoi(const char *str);
struct timeval	ft_get_time(void);
void	ft_set_philo(t_philo **philo, t_info *info);
void	ft_mutex_init(t_mutex_struct *mutex_struct, t_info *info);
int	ft_info_init(t_info	*info, int argc, char **argv);
#endif