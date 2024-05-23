/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:24:25 by fgori             #+#    #+#             */
/*   Updated: 2024/05/17 11:17:55 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	size_t			index_phi;
	size_t			num_of_eat;
	struct timeval	last_eat;
	size_t			time_of_eat;
	pthread_t		eat_;
	pthread_t		still_live;
	pthread_mutex_t	fork;
	struct s_data	*data;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

typedef struct s_data
{
	size_t				time;
	short				alive;
	short				eating;
	pthread_mutex_t		moment;
	pthread_mutex_t		stilleaten;
	pthread_mutex_t		write;
	size_t				fork;
	int					n_loop;
	size_t				dead_t_philo;
	size_t				eat_t_philo;
	size_t				sleep_t_philo;
	size_t				n_philo;
}	t_data;

void		put_error(char *str, t_philo *philo, t_data *data);
t_philo		*ft_lstnew(int content);
t_philo		*ft_lstlast(t_philo *lst);
long long	ft_atoi(const char *nptr);
void		join_close(t_philo **philo, size_t i);
void		table_create(t_data *table, char **av, int ac);
void		philocreate(t_philo **philo, int n_philo, t_data *data);
void		print_moment(char *str, t_philo *philos, int philo, int color);
void		get_time(t_philo *philo);
void		clean_node(t_philo **philo, int max);
void		free_table(t_data *data);
void		*still_alives(void *arg);
int			still_eat(t_philo *philo);
int			check(t_philo *philo);

#endif
