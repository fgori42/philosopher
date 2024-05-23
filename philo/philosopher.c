/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:29:23 by fgori             #+#    #+#             */
/*   Updated: 2024/05/17 11:15:32 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_fork(t_philo *philo)
{
	if (philo->index_phi == philo->data->n_philo)
	{
		pthread_mutex_lock(&philo->next->fork);
		print_moment("has taken a fork", philo, philo->index_phi, 33);
		pthread_mutex_lock(&philo->fork);
		print_moment("has taken a fork", philo, philo->index_phi, 33);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		print_moment("has taken a fork", philo, philo->index_phi, 33);
		pthread_mutex_lock(&philo->next->fork);
		print_moment("has taken a fork", philo, philo->index_phi, 33);
	}
	return ;
}

static void	make_the_move(t_philo *philo)
{
	lock_fork(philo);
	print_moment("is eating", philo, philo->index_phi, 32);
	philo->num_of_eat++;
	still_eat(philo);
	pthread_mutex_lock(&philo->data->moment);
	get_time(philo);
	pthread_mutex_unlock(&philo->data->moment);
	usleep(philo->data->eat_t_philo * 1000);
	if (philo->index_phi == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
	usleep(10);
	print_moment("is sleeping", philo, philo->index_phi, 35);
	usleep(philo->data->sleep_t_philo * 1000);
	print_moment("is thinking", philo, philo->index_phi, 36);
}

static void	*launch(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo)
		exit (-1);
	usleep(1);
	pthread_mutex_lock(&philo->data->moment);
	get_time(philo);
	pthread_mutex_unlock(&philo->data->moment);
	pthread_create(&(philo->still_live), NULL, still_alives, (void *)(philo));
	pthread_detach((philo->still_live));
	if (philo->index_phi % 2 == 0 || (philo->index_phi == philo->data->n_philo
			&& philo->data->n_philo % 2 != 0))
	{
		print_moment("is thinking", philo, philo->index_phi, 36);
		usleep(200);
	}
	while (1)
	{
		if (!check(philo))
			break ;
		make_the_move(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	table;
	t_philo	**philo;
	size_t	i;

	i = 0;
	if (ac < 5 || (ac == 6 && ft_atoi(av[5]) == 0) || ac > 6)
		put_error("ERROR\n", NULL, NULL);
	table_create(&table, av, ac);
	philo = malloc(sizeof(t_philo *));
	if (!philo)
		put_error("ERROR!\n", NULL, NULL);
	philocreate(philo, table.n_philo, &table);
	while (i++ < table.n_philo)
	{
		(*philo)->data = &table;
		if (pthread_create(&((*philo)->eat_), NULL,
				launch, (void *)(*philo)) < 0 && printf("errore\n"))
			break ;
		(*philo) = (*philo)->next;
	}
	join_close(philo, i - 1);
	free(philo);
	free_table(&table);
	usleep((table.eat_t_philo + table.sleep_t_philo));
	return (0);
}
