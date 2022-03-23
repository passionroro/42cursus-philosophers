#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philosophers	*philo;

	if (argc < 5 || argc > 6)
		return (write(2, "Error: 5 or 6 arguments please\n", 31));
	if (var_init(&data, argv, argc) == 1)
		return (write(2, "Error: invalid arguments\n", 25));
	philo = malloc(sizeof(t_philosophers) * data.size);
	if (!philo)
		return (ERR_MALLOC);
	if (!data_init(&data, philo))
		return (1);
		//return (exit_function(&philo));
	free(data.tid);
	free(data.forks);
	free(data.lock);
	free(philo);
	return (0);
}
