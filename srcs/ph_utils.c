/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:30:32 by soooh             #+#    #+#             */
/*   Updated: 2021/10/11 23:03:23 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_situation(t_philo *philo, int situation)
{
	pthread_mutex_lock(&philo->info->print);
	if (philo->info->end)
	{
		pthread_mutex_unlock(&philo->info->print);
		return ;
	}
	printf("%d\t", get_time() - philo->info->base_time);
	printf("philo no.%d ", philo->sequence + 1);
	if (situation == FORK)
		printf("has taken a fork\n");
	else if (situation == EATING)
		printf("is eating\n");
	else if (situation == SLEEPING)
		printf("is sleeping\n");
	else if (situation == THINKING)
		printf("is thinking\n");
	else if (situation == DIED)
		printf("died\n");
	pthread_mutex_unlock(&philo->info->print);
}

static int	ph_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ph_err(char *str)
{
	write(2, str, ph_strlen(str));
	return (1);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
