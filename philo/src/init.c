#include "../include/philo.h"

int	philo_init(t_data *data, t_philosophers *philo)
{
	int	i;
	int	size;

	i = -1;
	size = data->size;
	while (++i < data->size)
	{
		philo[i].id = i + 1;
		philo[i].nb_eat = 0;
		philo[i].data = data;
		if (pthread_create(&data->tid[i], NULL, routine, (void *)&philo[i]))
			return (ERR_THREAD);
	}
	i = -1;
	while (++i < size)
		if (pthread_join(data->tid[i], NULL))
			return (ERR_JOIN);
	return (0);
}

int	data_malloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->size);
	if (!data->tid)
		return (ERR_MALLOC);
	data->time_of_death = malloc(sizeof(long) * data->size);
	if (!data->time_of_death)
		return (ERR_MALLOC);
	data->forks = malloc(sizeof(int) * data->size);
	if (!data->forks)
		return (ERR_MALLOC);
	data->lock = malloc(sizeof(pthread_mutex_t) * data->size);
	if (!data->lock)
		return (ERR_MALLOC);
	data->status = malloc(sizeof(int) * data->size);
	if (!data->status)
		return (ERR_MALLOC);
	return (0);
}

int	data_init(t_data *data)
{
	int	i;

	if (data_malloc(data))
		return (ERR_MALLOC);
	pthread_mutex_init(&data->print, NULL);
	i = -1;
	while (++i < data->size)
	{
		pthread_mutex_init(&data->lock[i], NULL);
		data->forks[i] = 0;
		data->time_of_death[i] = current_time() + data->die;
		data->status[i] = 0;
	}
	return (0);
}

int	var_init(t_data *d, char **argv, int argc)
{
	int		i;

	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) == -1)
			return (1);
	d->size = ft_atoi(argv[1]);
	d->die = ft_atoi(argv[2]);
	d->eat = ft_atoi(argv[3]);
	d->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		d->must_eat = ft_atoi(argv[5]);
	else
		d->must_eat = -1;
	d->start = current_time();
	d->shutdown = 0;
	if (d->size < 1)
		return (1);
	return (0);
}
