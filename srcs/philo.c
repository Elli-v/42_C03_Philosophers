/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:51:58 by soooh             #+#    #+#             */
/*   Updated: 2021/09/18 22:48:02 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	err(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int		init_info(t_info *info, char **argv, int argc)
{
	info->num_philo = ft_atoi(argv[1]);
	if (info->num_philo <= 0)
		return(err("Error: 철학자는 1 명 이상이어야 함"));
	else if (info->num_philo >= 200)
		return(err("Error: 철학자는 200 명을 넘을 수 없다"));
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->time_to_die < 60 || info->time_to_eat < 60 || info->time_to_sleep < 60)
		return (err("60ms 미만은 테스트 ㄴㄴ임\n"));
	if (argc ==6)
	{
		info->must_eat = ft_atoi(argv[5]);
		if (info->must_eat <= 0)
			return (err("적어도 1 명 이상의 철학자가 식사를 해야 한다\n"));
	}
	else
		info->must_eat = -1;
	info->end = 0;
	info->start_time = 0;
	return (0);
}

int		main(int argc, char *argv[])
{
	t_info info;

	if (argc < 5 || argc > 6)
		return(err("Error: 올바른 인자 갯수가 아니셈"));
	init_info(&info, argv, argc);
	
}