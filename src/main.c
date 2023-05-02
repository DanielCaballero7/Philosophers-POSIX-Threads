#include "../inc/philosopher.h"

void	spaghetti(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->forks[philo->id]);
	pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->tools->numphilo]);
	if (philo->tools->dead)
	{
		philo_log("%dms %d has taken a fork\n",
			gettime() - philo->tools->tv, philo);
		philo_log("%dms %d has taken a fork\n",
			gettime() - philo->tools->tv, philo);
		philo->lstmeal = gettime();
		philo->meals++;
		philo_log("%dms %d is eating\n", gettime() - philo->tools->tv, philo);
	}
	i = gettime();
	while (gettime() - i < philo->tools->te)
		usleep(50);
	if (philo->tools->dead)
	{
		pthread_mutex_unlock(&philo->forks[philo->id]);
		pthread_mutex_unlock(&philo->forks[(philo->id + 1)
			% philo->tools->numphilo]);
	}
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(200);
	while (philo->tools->dead)
	{
		if (philo->tools->dead)
			spaghetti(philo);
		if (philo->tools->dead)
		{
			i = gettime();
			philo_log("%dms %d is sleeping\n",
				gettime() - philo->tools->tv, philo);
			while (gettime() - i < philo->tools->ts
				&& gettime() - i < philo->tools->te)
				usleep(50);
		}
		if (philo->tools->dead)
			philo_log("%dms %d is thinking\n",
				gettime() - philo->tools->tv, philo);
	}
	return (NULL);
}

void	*ft_master(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (philo->tools->dead)
	{
		i = -1;
		while (++i < philo->tools->numphilo)
		{
			if (gettime() - philo[i].lstmeal > philo[i].tools->td)
			{
				philo_log("%dms %i died\n",
					gettime() - philo->tools->tv, &philo[i]);
				philo->tools->dead = 0;
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	checkinput(int argc, char **argv)
{
	int	i;
	int j;

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
	t_tools			tools;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*thread;

	if (argc > 6 || argc < 5 || checkinput(argc, argv))
	{
		printf("Bad args.\n");
		return (1);
	}
	tools = build_tools(argv, tools);
	thread = (pthread_t *)malloc(sizeof(thread) * tools.numphilo);
	philo = (t_philo *)malloc(sizeof(t_philo) * tools.numphilo);
	forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * tools.numphilo);
	initphilo(philo, &tools, forks);
	i = -1;
	while (++i < tools.numphilo)
		pthread_create(&thread[i], NULL, philo_life, &philo[i]);
	pthread_create(&tools.master, NULL, ft_master, philo);
	ft_clean(philo);
}
