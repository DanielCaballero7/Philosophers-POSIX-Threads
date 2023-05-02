#ifndef PHILOSOPHERS
# define PHILOSOPHERS
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_tools
{
	int numphilo;
	int	td;
	int	te;
	int	ts;
	int	tv;
	int	dead;
	pthread_mutex_t log;
	pthread_t master;
}	t_tools;

typedef struct s_philosopher
{
	int	id;
	int	lstmeal;
	int meals;
	t_tools *tools;
	pthread_mutex_t *forks;
}	t_philo;

int gettime(void);
void	ft_clean(t_philo *philo);
void	philo_log(char *str, int time,  t_philo *philo);
t_tools	build_tools(char **argv, t_tools tools);
void	initphilo(t_philo *philo, t_tools *tools, pthread_mutex_t *forks);
int	checkinput(int argc, char **argv);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif