/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:04:00 by soooh             #+#    #+#             */
/*   Updated: 2021/10/11 23:06:39 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct	s_info
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				base_time;
	int				end;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
};

struct	s_philo
{
	int				sequence;
	int				f_left;
	int				f_right;
	int				start_time;
	int				last_eat;
	int				eat_cnt;
	int				eating;
	pthread_t		phlio_id;
	pthread_t		print_id;
	pthread_mutex_t	critical;
	t_info			*info;
};

void	print_situation(t_philo *philo, int situation);
int		chk_arg_length(char *arg);
int		ft_isdigit(int c);
int		is_numeric(char *arg);
int		check_arg(char *arg);
void	atoi_utils(char *str, int negative);
int		ph_atoi(char *str);
int		ph_err(char *str);
int		get_time(void);

void	*monitor(void *parameter);
void	*philosopher(void *parameter);
int		dining_table(t_info *info);

int		check_eat(t_philo *philo);
void	eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *phlio);

int		init_fork(t_info *info);
int		init_info(t_info *info, char **argv, int argc);
int		init_philo(t_info *info);
void	ph_free(t_info *info);
int		main(int argc, char *argv[]);

#endif
