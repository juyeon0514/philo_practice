/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:37:34 by juykang           #+#    #+#             */
/*   Updated: 2023/03/28 15:49:38 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> // msleep, gettimeofday
# include <pthread.h> // pthread_, pthread_mutex_
# include <signal.h> // kill
# include <sys/wait.h> // waitpid
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

# define ERROR_ARGUMENT_WRONG 0
# define ERROR_MALLOC 1
# define ERROR_FREE 2
# define ERROR_THREAD_CREATE 3
# define ERROR_THREAD_JOIN 4
# define ERROR_SLEEP 5
# define ERROR_GET_TIME 6
# define ERROR_MUTEX_INIT 7
# define ERROR_MUTEX_DESTROY 8
# define ERROR_MUTEX_LOCK 9
# define ERROR_MUTEX_UNLOCK 10

typedef struct s_philo
{
	pthread_t				thread;
	int						idx;
	int						left;
	int						right;
	int						eat_cnt;
	long					last_time;
	long					last_sleep;
	struct s_info			*info;
	struct s_state			*state;
	struct s_mutex_struct	*mutex;
}	t_philo;

typedef struct s_share_data
{
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				philo_number;
	int				must_eat_cnt;
	int				finish;
	int				dead;
	long			start_time;
	struct s_philo	*philo;
}	t_share_data;

typedef struct s_mutex_struct
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	monitor;
	pthread_mutex_t	meal;
}	t_mutex_struct;

int				ft_print_error(int a);
int				ft_atoi(const char *str);
long			ft_get_time(void);
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
void			ft_fork_pick(t_philo *philo, t_info *info, \
t_mutex_struct *mutex);
void			ft_sleep_or_think(t_philo *philo, t_info *info);
int				ft_msleep(long time, int num);
#endif