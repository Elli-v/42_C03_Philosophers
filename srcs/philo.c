/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:51:58 by soooh             #+#    #+#             */
/*   Updated: 2021/10/05 00:28:12 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_fork(t_info *info)
{
	int	i;

	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
	* info->num_philo);
	if (!info->fork)
		return (ph_err("malloc 실패함. 유감.\n"));
	i = -1;
	while (++i < info->num_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (ph_err("초기화 실패. 유감.\n"));
	}
	if (pthread_mutex_init(&info->print, NULL))
		return (ph_err("초기화 실패. 유감.\n"));
	return (0);
}

int		init_info(t_info *info, char **argv, int argc)
{
	info->num_philo = ph_atoi(argv[1]);
	if (info->num_philo <= 0)
		return(ph_err("Error: 철학자는 1 명 이상이어야 함"));
	else if (info->num_philo >= 200)
		return(ph_err("Error: 철학자는 200 명을 넘을 수 없다"));
	info->time_to_die = ph_atoi(argv[2]);
	info->time_to_eat = ph_atoi(argv[3]);
	info->time_to_sleep = ph_atoi(argv[4]);
	if (info->time_to_die < 60 || info->time_to_eat < 60 || info->time_to_sleep < 60)
		return (ph_err("60ms 미만은 테스트 ㄴㄴ임\n"));
	if (argc ==6)
	{
		info->must_eat = ph_atoi(argv[5]);
		if (info->must_eat <= 0)
			return (ph_err("적어도 1 명 이상의 철학자가 식사를 해야 한다\n"));
	}
	else
		info->must_eat = -1;
	info->end = 0;
	info->base_time = 0;
	if (init_fork(info))
		return (1);
	return (0);
}

int		init_philo(t_info *info)
{
	int	i;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philo)
		return (ph_err("malloc 실패함. 유감.\n"));
	i = -1;
	while (++i < info->num_philo)
	{
		info->philo[i].sequence = i;
		info->philo[i].f_left = i;
		info->philo[i].f_right = (i + 1) % info->num_philo;
		info->philo[i].last_eat = 0;
		info->philo[i].eat_cnt = 0;
		info->philo[i].eating = 0;
		info->philo[i].info = info;
		if (pthread_mutex_init(&info->philo[i].critical, NULL))
			return (ph_err("초기화 실패. 유감.\n"));
	}
	return (0);
}

void	ph_free(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&info->philo[i].critical);
	}
	pthread_mutex_destroy(&info->print);
	free(info->philo);
	free(info->fork);
}

int		main(int argc, char *argv[])
{
	t_info info;

	if (argc < 5 || argc > 6)
		return(ph_err("Error: 올바른 인자 갯수가 아니셈"));
	if (init_info(&info, argv, argc))
		return (1);
	if (init_philo(&info))
		return (1);
	if (dining_table(&info))
	{
		ph_free(&info);
		return (1);
	}
	ph_free(&info);{
		return (0);
	}
	
}