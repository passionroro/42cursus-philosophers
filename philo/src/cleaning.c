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

void	mutex_destroy(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->size)
		pthread_mutex_destroy(&data->lock[i]);
	pthread_mutex_destroy(&data->print);
}

int	philo_join(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->size)
		pthread_join(data->tid[i], NULL);
	return (0);
}
