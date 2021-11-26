/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:35 by soooh             #+#    #+#             */
/*   Updated: 2021/10/22 20:33:00 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *parameter)
{
	t_philo	*philo;

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
	return (NULL);
}

void	*philosopher(void *parameter)
{
	t_philo	*philo;

	philo = parameter;
	if (philo->sequence % 2 == 0 && philo->info->num_philo != 1)
		usleep(100 * philo->info->time_to_eat);
	while (!philo->info->end)
	{
		eat(philo);
		if (philo->info->must_eat != -1 && check_eat(philo))
			break ;
		if (philo->info->end)
			break ;
		sleeping(philo);
		if (philo->info->end)
			break ;
		thinking(philo);
		if (philo->info->end)
			break ;
	}
	return (NULL);
}

int	dining_table(t_info *info)
{
	int	i;

	info->base_time = get_time();
	i = -1;
	while (++i < info->num_philo)
	{
		info->philo[i].start_time = get_time();
		if (pthread_create(&info->philo[i].phlio_id, NULL,
				philosopher, &info->philo[i]))
			return (ph_err("Error: Failed to create pthread.\n"));
		if (pthread_create(&info->philo[i].print_id, NULL,
				monitor, &info->philo[i]))
			return (ph_err("Error: Failed to create pthread.\n"));
	}
	i = -1;
	while (++i < info->num_philo)
	{
		if (pthread_join(info->philo[i].phlio_id, NULL))
			return (ph_err("Error: Failed to join pthread.\n"));
		if (pthread_join(info->philo[i].print_id, NULL))
			return (ph_err("Error: Failed to join pthread.\n"));
	}
	return (0);
}
