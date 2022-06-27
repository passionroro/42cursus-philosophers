#include "../include/philo.h"

void	clean_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->size)
		pthread_mutex_destroy(&data->lock[i]);
	pthread_mutex_destroy(&data->print);
}

void	detach_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->size)
		pthread_detach(data->tid[i]);
}

int	monitor_meals(t_philosophers *philo, t_data *data, int id)
{
	(void)philo;
	if (data->meals[id - 1] < data->must_eat)
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
//		detach_threads(data);
		clean_threads(data);
		usleep(500);
		return (1);
	}
	if (data->must_eat != -1)
		if (monitor_meals(philo, data, id))
			return (2);
	return (0);
}
