/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:04:00 by soooh             #+#    #+#             */
/*   Updated: 2021/09/22 01:47:20 by soooh            ###   ########.fr       */
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

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct	s_info
{
	int				num_philo; //철학자 수
	int				time_to_die; //죽을 조건 시간
	int				time_to_eat; //식사 시간
	int				time_to_sleep; //자는 시간
	int				must_eat; //식사를 할 최소한의 인원
	int				start_time; //프로그램 시작 시간
	int				end; //프로그램 종료 유무
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
};

struct	s_philo
{
	int				sequence; //상태
	int				f_left; //포크 잡은 왼쪽 손
	int				f_right; //포크 잡은 오른쪽 손
	int				last_eat; //마지막으로 식사한 시간
	int				eat_cnt; //먹은 횟수
	int				eating; //먹는 중인지 아닌지
	pthread_t		philo_th;
	pthread_t		monitor;
	t_info			*info;
};


int	ph_atoi(char *str);
int	ph_err(char *str);

#endif