/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:09:25 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 01:30:57 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_closed(t_vars *map, int i, size_t j)
{
	if (map->map[i][j] == ' ')
		return (1);
	if (map->map[i][j] == '0')
	{
		if (i == 0 || ft_strlen(map->map[i - 1]) <= j || map->map[i - 1][j]
			== ' ' || map->map[i - 1][j] == '\n')
		{
			printf("Error at (%d, %zu): Top boundary or invalid above cell\n",
				i, j);
			return (0);
		}
		if (!map->map[i + 1] || ft_strlen(map->map[i + 1]) <= j
			|| map->map[i + 1][j] == ' ' || map->map[i + 1][j] == '\n')
		{
			printf("Error at (%d, %zu): Bottom boundary or invalid below cell\n", i, j);
			return (0);
		}
		if (j == 0 || map->map[i][j - 1] == ' ' || map->map[i][j - 1] == '\n')
		{
			printf("Error at (%d, %zu): Left boundary or invalid left cell\n",
				i, j);
			return (0);
		}
		if (j + 1 >= ft_strlen(map->map[i]) || map->map[i][j + 1] == ' ' || map->map[i][j + 1] == '\n')
		{
			printf("Error at (%d, %zu): Right boundary or invalid right cell\n", i, j);
			return (0);
		}
	}
	return (1);
}

int	check_isclosed(int i, t_vars *map)
{
	size_t	j;
	int		ok;
	int		p;

	ok = 0;
	j = 0;
	while (map->map[i][j])
	{
		p = 1;
		if (ok != 1)
			ft_t_vars()->pos = 0;
		if (ft_t_vars()->map[i][j] != '1' && ft_t_vars()->map[i][j] != 'x'
				&& ft_t_vars()->map[i][j] != 'P')
		{
			check_fill(ft_t_vars(), i, j, &p);
			if (p == 1 && ft_t_vars()->pos != 0)
				ok = 1;
		}
		printf("%c", map->map[i][j]);
		j++;
	}
	return (ok);
}
