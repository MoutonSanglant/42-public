int		ft_pow(int b, int e)
{
	if (e > 0)
		return (b * ft_pow(b, e - 1));
	else
		return (1);
}
