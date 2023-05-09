/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:50:04 by dcaballe          #+#    #+#             */
/*   Updated: 2023/05/08 23:50:04 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

t_tools	*build_tools(char **argv, int argc)
{
	t_tools	*tools;

	tools = (t_tools *) malloc(sizeof (t_tools));
	tools->numphilo = ft_atoi(argv[1]);
	tools->td = ft_atoi(argv[2]);
	tools->te = ft_atoi(argv[3]);
	tools->ts = ft_atoi(argv[4]);
	tools->end = 0;
	if (argc == 6)
		tools->meals = ft_atoi(argv[5]);
	else
		tools->meals = -1;
	tools->dead = 1;
	return (tools);
}

void	philo_log(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->tools->log);
	time = gettime() - philo->tools->tv;
	printf(str, time, (philo->id + 1));
	pthread_mutex_unlock(&philo->tools->log);
}

void	ft_clean(t_philo *philo, pthread_t *thread, t_tools *tools)
{
	int	i;

	i = 0;
	while (i < philo->tools->numphilo)
		pthread_join(thread[i++], NULL);
	philo->tools->end = 1;
	pthread_join(philo->tools->master, NULL);
	i = -1;
	while (++i < philo->tools->numphilo)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&philo->tools->log);
	free(thread);
	free(philo->forks);
	free(philo);
	free(tools);
}

int	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	initphilo(t_philo *philo, t_tools *tools, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_init(&(tools->log), NULL);
	tools->tv = gettime();
	i = -1;
	while (++i < tools->numphilo)
		pthread_mutex_init(&forks[i], NULL);
	i = 0;
	while (i < tools->numphilo)
	{
		philo[i].id = i;
		philo[i].tools = tools;
		philo[i].meals = 0;
		philo[i].forks = forks;
		philo[i].lstmeal = tools->tv;
		i++;
	}
}
