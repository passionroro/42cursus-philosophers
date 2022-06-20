#include "../include/philo.h"

void	clean_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->size)
		pthread_mutex_destroy(&data->lock[i]);
	pthread_mutex_destroy(&data->print);
}

int	monitor_meals(t_philosophers *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->size)
		if (philo[i].nb_eat < data->must_eat)
			return (0);
	data->shutdown = 1;
	usleep(500);
	clean_threads(data);
	return (0);
}

int	death_monitor(t_philosophers *philo, t_data *data)
{
	int		i;
	long	time;

	while (1)
	{
		time = current_time();
		i = -1;
		while (++i < data->size)
		{
			if (philo[i].time_of_death < time)
			{
				print_action(i + 1, DIED, data);
				data->shutdown = 1;
				usleep(100);
				clean_threads(data);
				return (1);
			}
		}
		if (data->must_eat != -1)
			if (monitor_meals(philo, data))
				return (2);
	}
	usleep(500);
	return (0);
}
