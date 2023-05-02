#include "../inc/philosopher.h"

t_tools	build_tools(char **argv, t_tools tools)
{
	tools.numphilo = ft_atoi(argv[1]);
	tools.td = ft_atoi(argv[2]);
	tools.te = ft_atoi(argv[3]);
	tools.ts = ft_atoi(argv[4]);
	tools.dead = 1;
	return (tools);
}

void	philo_log(char *str, int time, t_philo *philo)
{
	pthread_mutex_lock(&philo->tools->log);
	printf(str, time, philo->id);
	pthread_mutex_unlock(&philo->tools->log);
}

void	ft_clean(t_philo *philo)
{
	int	i;

	pthread_join(philo->tools->master, NULL);
	i = -1;
	while (++i < philo->tools->numphilo)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&philo->tools->log);
	free(philo->forks);
	free(philo);
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
