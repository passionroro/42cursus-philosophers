#include "../include/philo.h"

void	print_action(int num, int status, unsigned long start)
{
	char			*str;
	struct timeval	tv;

	if (status == THINK)
		str = "is thinking";
	if (status == FORK)
		str = "has taken a fork";
	if (status == EAT)
		str = "is eating";
	if (status == DEAD)
		str = "died";
	if (status == SLEEP)
		str = "is sleeping";
	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start, num, str);
}

int	ft_atoi(const char *str)
{
	long	nb;
	int	i;

	i = -1;
	nb = 0;
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + str[i] - '0';
		else
			return (0);
		if (nb > 2147483647 || nb < -2147483648)
			return (0);
	}
	return ((int)nb);
}
