/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:48:31 by fgori             #+#    #+#             */
/*   Updated: 2024/04/22 14:25:06 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int content)
{
	t_philo	*new;

	new = (void *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->index_phi = content;
	if (pthread_mutex_init(&new->fork, NULL) < 0)
		return (NULL);
	new->num_of_eat = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst && lst-> next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
