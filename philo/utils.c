/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:32:12 by fgori             #+#    #+#             */
/*   Updated: 2024/05/17 11:24:54 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_moment(char *str, t_philo *philos, int philo, int color)
{
	struct timeval	time;
	size_t			current;

	pthread_mutex_lock(&philos->data->write);
	if (philos->data->alive)
	{
		gettimeofday(&time, NULL);
		current = ((time.tv_sec * 1000)
				+ (time.tv_usec / 1000)) - philos->data->time;
		printf("%ld \033[0;%dm%d %s\033[0m\n", current,
			color, philo, str);
	}
	pthread_mutex_unlock(&philos->data->write);
}

void	get_time(t_philo *philo)
{
	gettimeofday(&philo->last_eat, NULL);
	philo->time_of_eat = ((philo->last_eat.tv_sec * 1000)
			+ (philo->last_eat.tv_usec / 1000));
}
