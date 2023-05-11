int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

static unsigned int	ft_pow(unsigned int nbr, int n)
{
	if (n == 0)
		return (1);
	if (n == 1)
		return (nbr);
	else
		return (nbr * ft_pow(nbr, n - 1));
}

unsigned int	ft_atoi(const char *nptr)
{
	char			*str;
	int				i;
	int				j;
	unsigned int	nbr;

	str = (char *) nptr;
	i = 0;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	j = 0;
	while (str[--i] >= '0' && str[i] <= '9')
		nbr += (str[i] - '0') * ft_pow(10, j++);
	return (nbr);
}