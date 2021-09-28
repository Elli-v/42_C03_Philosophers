/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:04:00 by soooh             #+#    #+#             */
/*   Updated: 2021/09/29 00:47:32 by soooh            ###   ########.fr       */
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
	int				num_philo; //철학자 수
	int				time_to_die; //죽을 조건 시간
	int				time_to_eat; //식사 시간
	int				time_to_sleep; //자는 시간
	int				must_eat; //식사를 할 최소한의 인원
	int				base_time; //프로그램 시작 시간 == 기준 시간
	int				end; //프로그램 종료 유무
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
};

struct	s_philo
{
	int				sequence; //순서
	int				f_left; //포크 잡은 왼쪽 손
	int				f_right; //포크 잡은 오른쪽 손
	int				start_time; // 해당 순서 철학자가 시작한 시간
	int				last_eat; //마지막으로 식사한 시간
	int				eat_cnt; //먹은 횟수
	int				eating; //먹는 중인지 아닌지
	pthread_t		phlio_id; //스레드 ID받음
	pthread_t		print_id;
	pthread_mutex_t	critical;//출력 순서 꼬이면 오류 발생 -> 꼬임 방지 mutex 선언
	t_info			*info;
};

void	print_situation(t_philo *philo, int situation);
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