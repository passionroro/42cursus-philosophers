#include "../include/philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (ft_isascii(s1[i]) == 0 || ft_isascii(s2[i]) == 0)
			return (1);
		if (s1[i] - s2[i] == 0)
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
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
			return (-1);
		if (nb > 2147483647 || nb < -2147483648)
			return (-1);
	}
//	if (nb >= 2147483640)
//		return (214748364);
	return ((int)nb);
}


