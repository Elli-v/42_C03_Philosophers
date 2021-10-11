/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:41:10 by soooh             #+#    #+#             */
/*   Updated: 2021/10/11 22:48:34 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_atoi(char *str)
{
	int	res;
	int	negative;
	int	count;

	if (!check_arg(str))
		return (-1);
	count = 0;
	negative = 1;
	res = 0;
	atoi_utils(str, negative);
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
		count++;
	}
	res = res * negative;
	if (count >= 19 && negative == 1)
		return (-1);
	else if (count >= 19 && negative == -1)
		return (0);
	return (res);
}
