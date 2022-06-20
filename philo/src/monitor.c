#include "../include/philo.h"

void	clean_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->size)
	{
		pthread_mutex_destroy(&data->death[i]);
		pthread_mutex_destroy(&data->lock[i]);
	}
	pthread_mutex_destroy(&data->print);
}

int	monitor_meals(t_philosophers *philo, t_data *data, int id)
{
	if (philo[id - 1].nb_eat < data->must_eat)
		return (0);
	data->shutdown = 1;
	usleep(500);
	clean_threads(data);
	return (0);
}

int	death_check(t_philosophers *philo, t_data *data, int id)
{
	long	time;

	time = current_time();
	if (data->time_of_death[id - 1] < time)
	{
		print_action(id, DIED, data);
		data->shutdown = 1;
		usleep(100);
		clean_threads(data);
		return (1);
	}
	if (data->must_eat != -1)
		if (monitor_meals(philo, data, id))
			return (2);
	return (0);
}
