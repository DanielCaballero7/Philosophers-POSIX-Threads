/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:16:55 by dcaballe          #+#    #+#             */
/*   Updated: 2023/05/09 10:16:55 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_tools
{
	int				numphilo;
	int				td;
	int				te;
	int				ts;
	int				tv;
	int				meals;
	int				dead;
	int				end;
	pthread_mutex_t	log;
	pthread_t		master;
}	t_tools;

typedef struct s_philosopher
{
	int				id;
	int				lstmeal;
	int				meals;
	t_tools			*tools;
	pthread_mutex_t	*forks;
}	t_philo;

int		gettime(void);
void	ft_clean(t_philo *philo, pthread_t *threads, t_tools *tools);
void	philo_log(char *str, t_philo *philo);
t_tools	*build_tools(char **argv, int argc);
void	initphilo(t_philo *philo, t_tools *tools, pthread_mutex_t *forks);
int		checkinput(int argc, char **argv);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		check_meals(t_philo *philo);
void	philo_alone(t_philo *philo);
int		check_args(int argc, char **argv);
void	spaghetti(t_philo *philo);
void	philo_loop(t_philo *philo);

#endif