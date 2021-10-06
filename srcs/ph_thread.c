/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:35 by soooh             #+#    #+#             */
/*   Updated: 2021/10/06 23:05:05 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *parameter)
{
	t_philo *philo;

	philo = parameter;
	while (!philo->info->end)
	{
		pthread_mutex_lock(&philo->critical);
		if (get_time() - philo->start_time >= philo->info->time_to_die)
		{
			print_situation(philo, DIED);
			philo->info->end = 1;
			pthread_mutex_unlock(&philo->critical);
			break ;
		}
		pthread_mutex_unlock(&philo->critical);
		usleep(100);
	}
	return(NULL);
}

void	*philosopher(void *parameter)
{
	t_philo *philo;

	philo = parameter;
	if (philo->sequence % 2 == 0 && philo->info->num_philo != 1)
		usleep(1000 * philo->info->time_to_eat);
	while (!philo->info->end)
	{
		eat(philo);
		if (philo->info->must_eat != -1 && check_eat(philo))
			break;
		//먹었는지 체크
		if (philo->info->end)
			break ;
		sleeping(philo);
		//잔다
		if (philo->info->end)
			break ;
		//생각한다
		thinking(philo);
		if (philo->info->end)
			break ;
	}
	return (NULL);
}

int	dining_table(t_info *info)
{
	int i;

	info->base_time = get_time();//시간 지정 함수 
	// printf("%d\n", info->base_time);
	i = -1;
	while (++i < info->num_philo)
	{
		info->philo[i].start_time = get_time();//시간 지정 함수;
		if (pthread_create(&info->philo[i].phlio_id, NULL, philosopher/*행동함수*/, &info->philo[i]))
			return(ph_err("스레드 생성 실패함.\n"));
		if (pthread_create(&info->philo[i].print_id, NULL, monitor/*출력함수*/, &info->philo[i]))
			return(ph_err("스레드 생성 실패함.\n"));
	}
	i = -1;
	while (++i < info->num_philo)
	{
		if (pthread_join(info->philo[i].phlio_id, NULL))
			return(ph_err("스레드 생성 실패함.\n"));
		if (pthread_join(info->philo[i].print_id, NULL))
			return(ph_err("스레드 생성 실패함.\n"));
	}
	return (0);
}