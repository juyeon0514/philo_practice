/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:37:34 by juykang           #+#    #+#             */
/*   Updated: 2023/03/17 00:23:33 by juykang          ###   ########seoul.kr  */
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
	long					last_time;
	struct s_info			*info;
	struct s_mutex_struct	*mutex;
	enum e_state			state;
}	t_philo;

typedef struct s_info
{
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				philo_number;
	int				must_eat_cnt;
	int				finish;
	long			start_time;
}	t_info;

typedef struct s_mutex_struct
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	monitor;
}	t_mutex_struct;

int				ft_print_error(int a);
int				ft_atoi(const char *str);
long long		ft_get_time(void);
int				ft_set_philo(t_philo **philo, t_info *info, \
t_mutex_struct *mutex);
void			ft_mutex_init(t_mutex_struct *mutex_struct, t_info *info);
int				ft_info_init(t_info	*info, int argc, char **argv);
int				ft_isnum(char *argv);
void			ft_eat_philo(t_philo *philo, t_info *info, \
t_mutex_struct *mutex);
void			ft_check_time(t_philo *philo, t_info *info);
int				ft_philo_print(int num, long start_time, char *comment, \
t_philo *philo);
#endif