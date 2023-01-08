unsigned int sqrt(unsigned int x)
{
	unsigned int i = 0;

	while (i * i < x)
	{
		i++;
	}

	if (i * i == x)
	{
		return i;
	}

	if (((i * i) < x) && (((i + 1) * (i + 1)) > x))
	{
		return i;
	}

	if (((i * i) > x) && (((i - 1) * (i - 1)) < x))
	{
		return i - 1;
	}

	return 0;
}