/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:26:27 by fgori             #+#    #+#             */
/*   Updated: 2024/05/17 11:17:50 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philocreate(t_philo **philo, int n_philo, t_data *data)
{
	int		i;
	t_philo	*new;

	i = 0;
	while (i < n_philo)
	{
		new = ft_lstnew(n_philo - i);
		if (new == NULL)
			put_error("ERROR in allocation", (*philo), data);
		if (i == 0)
		{
			(*philo) = new;
		}
		else
		{
			new->next = (*philo);
			(*philo)->prev = new;
			(*philo) = new;
		}
		i++;
	}
	(*philo)->prev = ft_lstlast((*philo));
	(*philo)->prev->next = (*philo);
}

void	table_create(t_data *table, char **av, int ac)
{
	struct timeval	first_time;

	gettimeofday(&first_time, NULL);
	table->time = (first_time.tv_sec * 1000) + (first_time.tv_usec / 1000);
	table->alive = 1;
	table->eating = 1;
	table->n_philo = ft_atoi(av[1]);
	table->fork = table->n_philo;
	table->dead_t_philo = ft_atoi(av[2]);
	table->eat_t_philo = ft_atoi(av[3]);
	table->sleep_t_philo = ft_atoi(av[4]);
	if (table->n_philo == 1)
	{
		usleep(table->dead_t_philo * 1000);
		printf("%s \033[0;31m philo: 1 is dead \033[0m\n", av[2]);
		exit(0);
	}
	if (pthread_mutex_init(&table->moment, NULL) < 0
		|| pthread_mutex_init(&table->write, NULL) < 0
		|| pthread_mutex_init(&table->stilleaten, NULL) < 0)
		put_error("ERROR!\n", NULL, NULL);
	if (ac == 6)
		table->n_loop = ft_atoi(av[5]);
	else
		table->n_loop = -1;
}
