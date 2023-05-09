/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:15:18 by dcaballe          #+#    #+#             */
/*   Updated: 2023/05/09 10:15:18 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	spaghetti(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->forks[philo->id]);
	if (philo->tools->dead)
		pthread_mutex_lock(&philo->forks[(philo->id + 1)
			% philo->tools->numphilo]);
	if (philo->tools->dead)
	{
		philo_log("%d %d has taken a fork\n", philo);
		if (philo->tools->dead)
			philo_log("%d %d has taken a fork\n", philo);
		philo->lstmeal = gettime();
		if (philo->tools->dead)
			philo_log("%d %d is eating\n", philo);
	}
	if (philo->tools->dead)
		i = gettime();
	while (philo->tools->dead && gettime() - i < philo->tools->te)
		usleep(10);
	if (philo->tools->dead)
		philo->meals++;
	pthread_mutex_unlock(&philo->forks[philo->id]);
	pthread_mutex_unlock(&philo->forks[(philo->id + 1)
		% philo->tools->numphilo]);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->tools->numphilo == 1)
	{
		philo_alone(philo);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		usleep(200);
	philo_loop(philo);
	return (NULL);
}

void	*ft_master(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (philo->tools->dead)
	{
		if (philo->tools->meals != -1 && check_meals(philo) == 1)
			return (NULL);
		i = -1;
		while (++i < philo->tools->numphilo)
		{
			if (gettime() - philo[i].lstmeal > philo[i].tools->td)
			{
				philo->tools->dead = 0;
				while (philo->tools->end != 1)
					usleep(20);
				philo_log("%d %i died\n", &philo[i]);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	checkinput(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i] && argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) || (argv[i][j] == ' '
				&& ft_isdigit(argv[i][j + 1])))
				j++;
			else
				return (1);
		}
		if (!argv[i])
			return (1);
		i++;
		j = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int				i;
	t_tools			*tools;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*thread;

	if (check_args(argc, argv))
		return (0);
	tools = build_tools(argv, argc);
	thread = (pthread_t *)malloc(sizeof(thread) * tools->numphilo);
	philo = (t_philo *)malloc(sizeof(t_philo) * tools->numphilo);
	forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * tools->numphilo);
	if (!thread || !philo || !forks)
	{
		printf("Malloc error.\n");
		return (0);
	}
	initphilo(philo, tools, forks);
	i = -1;
	while (++i < tools->numphilo)
		pthread_create(&thread[i], NULL, philo_life, &philo[i]);
	pthread_create(&tools->master, NULL, ft_master, philo);
	ft_clean(philo, thread, tools);
}
