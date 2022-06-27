#include "../include/philo.h"

void	free_data(t_philosophers *philo, t_data *data)
{
	free(data->status);
	free(data->meals);
	free(data->lock);
	free(data->forks);
	free(data->tid);
	free(data->time_of_death);
	free(philo);
}

void	clean_threads(t_data *data)
{
	int			i;
	
	pthread_mutex_destroy(&data->print);
	i = -1;
	while (++i < data->size)
	{
		pthread_mutex_destroy(&data->lock[i]);
		if (pthread_join(data->tid[i], NULL))
			return ;
	}
}

int	monitor_meals(t_data *data, int i)
{
	if (data->meals[i] <= data->must_eat)
		return (0);
	data->shutdown = 1;
	usleep(500);
	clean_threads(data);
	return (0);
}

int	death_check(t_philosophers *philo, t_data *data, int id)
{
	(void)philo;
	(void)id;
	int		i;
	long	time;

	i = -1;
	while (++i < data->size)
	{
		time = current_time();
		if (data->time_of_death[i] < time)
		{
			print_action(i + 1, DIED, data);
			data->shutdown = 1;
			usleep(100);
			clean_threads(data);
			usleep(500);
			return (1);
		}
		if (data->must_eat != -1)
			if (monitor_meals(data, i))
				return (2);
	}
	return (0);
}
