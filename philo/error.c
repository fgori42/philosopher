/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:36:35 by fgori             #+#    #+#             */
/*   Updated: 2024/05/10 10:54:12 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_node(t_philo **philo, int max)
{
	int		i;
	t_philo	*temp;

	i = 0;
	while (i < max)
	{
		temp = (*philo)->next;
		free((*philo));
		(*philo) = temp;
		i++;
	}
}

void	free_table(t_data *data)
{
	pthread_mutex_lock(&data->write);
	pthread_mutex_unlock(&data->write);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->stilleaten);
	pthread_mutex_lock(&data->moment);
	pthread_mutex_unlock(&data->moment);
	pthread_mutex_destroy(&data->moment);
}

void	put_error(char *str, t_philo *philo, t_data *data)
{
	if (philo)
	{
		clean_node(&philo, philo->data->n_philo);
		free(philo);
	}
	if (data)
	{
		free_table(data);
	}
	printf("%s", str);
	exit(1);
}

void	join_close(t_philo **philo, size_t i)
{
	while (i > 0)
	{
		pthread_join((*philo)->eat_, NULL);
		(*philo) = (*philo)->next;
		i--;
	}
	while (i < (*philo)->data->n_philo)
	{
		(*philo) = (*philo)->next;
		pthread_mutex_destroy(&(*philo)->fork);
		i++;
	}
	clean_node(philo, (*philo)->data->n_philo);
}
