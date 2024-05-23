/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:04:07 by fgori             #+#    #+#             */
/*   Updated: 2024/05/13 18:06:01 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_error(void)
{
	printf("ERROR\n");
	exit(1);
}

int	ft_isdigit(int i)
{
	if (i <= '9' && i >= '0')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

long long	ft_atoi(const char *nptr)
{
	int			a;
	long long	b;
	int			c;

	a = 0;
	b = 0;
	c = 1;
	while (nptr[a] == ' ' || ((nptr[a] >= 9) && (nptr[a] <= 13)))
		a++;
	if (nptr[a] == '+' || nptr[a] == '-')
	{
		if (nptr[a] == '-')
			make_error();
		a++;
	}
	while ((nptr[a] != '\0'))
	{
		if (!(ft_isdigit(nptr[a])))
			make_error();
		b = (b * 10) + ((nptr[a] + 2) % 10);
		a++;
	}
	b *= c;
	return (b);
}
/*
#include<stdlib.h>
#include<stdio.h>

int	main(void)
{
	char *f= "   12434567890ad3";
	printf("%i\n | %i ", ft_atoi(f), atoi(f));


}*/
