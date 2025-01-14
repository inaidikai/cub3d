/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:13:49 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 09:43:34 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	cubcheck(char *y)
{
	int	len;

	len = ft_strlen(y);
	if (len < 4)
		return (0);
	if (ft_strncmp(&y[len - 4], ".cub", 4) == 0)
		return (1);
	return (0);
}

void	ft_free_pp(void **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		if (argv[i])
		{
			free(argv[i]);
			argv[i] = NULL;
		}
		i++;
	}
	free(argv);
}

int	ft_str_len(char *s)
{
	unsigned int	count;

	count = 0;
	while (s[count])
	{
		count++;
	}
	return (count);
}

int	is_pace(char c)
{
	return (c == ' ' || c
		== '\t' || c
		== '\n' || c
		== '\v' || c
		== '\f' || c
		== '\r');
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "invalid format", 15);
		return (1);
	}
	if (cubcheck(argv[1]))
		cube3d(argv[1]);
	else
	{
		write(1, "invalid format2", 15);
		return (1);
	}
	return (0);
}
