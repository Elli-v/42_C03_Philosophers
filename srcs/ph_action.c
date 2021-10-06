/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 00:45:34 by soooh             #+#    #+#             */
/*   Updated: 2021/10/06 23:11:18 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_eat(t_philo *philo)
{
	int i;
	int	cnt;

	i = -1;
	cnt = 0;
	//왜 philo->info->philo[i].eating 을 써야 하는지 모르겠다.. ㅜ
	//./philo 5 800 200 200 7 했을 때 '7' == 식사 조건 충족 시 실행 종료 == 모든 철학자의 7 번의 식사가 끝나면 종료
	//
	while (++i < philo->info->num_philo)
	{
		if (philo->info->philo[i].eating < philo->info->must_eat)
			return (0);
	}
	philo->info->end = 1;
	
	return (0);
}

void	eat(t_philo *philo)
{
	if (philo->info->num_philo == 1)
	{
		pthread_mutex_lock(&philo->info->fork[philo->f_right]);
		print_situation(philo, FORK);
		while (!philo->info->end)
			usleep(1000);
		pthread_mutex_unlock(&philo->info->fork[philo->f_right]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->fork[philo->f_right]);
		print_situation(philo, FORK);
		pthread_mutex_lock(&philo->info->fork[philo->f_left]);
		print_situation(philo, FORK);
		pthread_mutex_lock(&philo->critical);
		print_situation(philo, EATING);
		philo->start_time = get_time();
		pthread_mutex_unlock(&philo->critical);
		while (get_time() - philo->start_time <= philo->info->time_to_eat && !philo->info->end)
			usleep(1000);
		philo->eating++;
		pthread_mutex_unlock(&philo->info->fork[philo->f_left]);
		pthread_mutex_unlock(&philo->info->fork[philo->f_right]);
	}
}

void	sleeping(t_philo *philo)
{
	int	sleep_time;

	sleep_time = get_time();
	print_situation(philo, SLEEPING);
	while (get_time() - sleep_time <= philo->info->time_to_sleep && !philo->info->end)
		usleep(1000);
}

void	thinking(t_philo *phlio)
{
	print_situation(phlio, THINKING);
}
