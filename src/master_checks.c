/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:58:50 by dcaballe          #+#    #+#             */
/*   Updated: 2023/05/08 01:03:11 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	check_args(int argc, char **argv)
{
	if (argc > 6 || argc < 5 || checkinput(argc, argv))
	{
		printf("Bad args.\n");
		return (1);
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->tools->numphilo)
	{
		if (philo[i].meals < philo->tools->meals || philo->tools->meals == -1)
			return (0);
		i++;
	}
	philo->tools->dead = 0;
	return (1);
}

void	philo_alone(t_philo *philo)
{
	philo_log("%d %d has taken a fork\n", philo);
	while (philo->tools->dead)
		usleep(20);
}

void	philo_loop(t_philo *philo)
{
	int	i;

	while (philo->tools->dead)
	{
		if (philo->tools->dead)
			spaghetti(philo);
		if (philo->tools->dead)
		{
			i = gettime();
			philo_log("%d %d is sleeping\n", philo);
			while (philo->tools->dead && gettime() - i < philo->tools->ts)
				usleep(50);
		}
		if (philo->tools->dead)
			philo_log("%d %d is thinking\n", philo);
	}
}


