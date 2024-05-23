/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:29:46 by fgori             #+#    #+#             */
/*   Updated: 2024/05/17 10:50:26 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_eat(t_philo *philo)
{
	static size_t	eat;

	pthread_mutex_lock(&philo->data->moment);
	if (philo->data->n_loop == -1)
	{
		pthread_mutex_unlock(&philo->data->moment);
		return (1);
	}
	if ((int)philo->num_of_eat <= philo->data->n_loop)
	{
		eat++;
	}
	if (eat >= (size_t)philo->data->n_loop * philo->data->n_philo)
	{
		philo->data->eating = 0;
		pthread_mutex_unlock(&philo->data->moment);
		return (0);
	}
	else
		pthread_mutex_unlock(&philo->data->moment);
	return (1);
}

static void	check_dead(size_t j, t_philo *philo)
{
	if (j > (size_t)philo->data->dead_t_philo && philo->data->eating == 1)
	{
		print_moment("died", philo, philo->index_phi, 31);
		pthread_mutex_lock(&philo->data->write);
		philo->data->alive = 0;
		pthread_mutex_unlock(&philo->data->write);
	}
}

static void	bi_lock(t_philo *philo, int i)
{
	if (i == 1)
	{
		pthread_mutex_lock(&philo->data->moment);
		pthread_mutex_lock(&philo->data->write);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->moment);
		pthread_mutex_unlock(&philo->data->write);
	}
}

void	*still_alives(void *arg)
{
	t_philo			*philo;
	struct timeval	now;
	long			j;

	j = 1;
	philo = (t_philo *)arg;
	while (1)
	{
		bi_lock(philo, 1);
		if (!philo->data->eating || !philo->data->alive)
		{
			bi_lock(philo, 0);
			break ;
		}
		else
			bi_lock(philo, 0);
		usleep(1);
		pthread_mutex_lock(&philo->data->moment);
		gettimeofday(&now, NULL);
		j = ((now.tv_sec * 1000) + (now.tv_usec / 1000)
				- philo->time_of_eat);
		check_dead(j, philo);
		pthread_mutex_unlock(&philo->data->moment);
	}
	return (NULL);
}

int	check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->moment);
	if (!philo->data->eating || !philo->data->alive)
	{
		pthread_mutex_unlock(&philo->data->moment);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->moment);
		return (1);
	}
}
