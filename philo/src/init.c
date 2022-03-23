#include "../include/philo.h"

int	philo_init(t_data *data, t_philosophers *philo)
{
	int	i;

	i = -1;
	while (++i < data->size)
	{
		philo[i].id = i + 1;
		philo[i].nb_eat = 0;
		philo[i].data = data;
		if (pthread_create(&data->tid[i], NULL, routine, (void *)&philo[i]))
			return (ERR_THREAD);
	}
	i = -1;
	while (++i < data->size)
		if (pthread_join(data->tid[i], NULL))
			return (ERR_JOIN);
	return (0);
}

int	data_init(t_data *data, t_philosophers *philo)
{
	int	i;

	data->tid = malloc(sizeof(pthread_t) * data->size);
	if (!data->tid)
		return (ERR_MALLOC);
	data->forks = malloc(sizeof(int) * data->size);
	if (!data->forks)
		return (ERR_MALLOC);
	data->lock = malloc(sizeof(pthread_mutex_t) * data->size);
	if (!data->lock)
		return (ERR_MALLOC);
	i = -1;
	while (++i < data->size)
	{
		pthread_mutex_init(&data->lock[i], NULL);
		data->forks[i] = 0;
	}
	return (philo_init(data, philo));
}

int	var_init(t_data *d, char **argv, int argc)
{
	int		i;
	struct timeval	tv;

	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) == 0)
			return (1);
	d->size = ft_atoi(argv[1]);
	d->die = ft_atoi(argv[2]);
	d->eat = ft_atoi(argv[3]);
	d->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		d->must_eat = ft_atoi(argv[5]);
	gettimeofday(&tv, NULL);
	d->start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (0);
}
