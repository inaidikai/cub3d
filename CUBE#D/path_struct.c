/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:34:21 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 01:24:14 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

static int	is_map_empty(t_vars *map)
{
	return (!map->map);
}

int	path_struct(t_vars *map)
{
	int	i;

	i = 0;
	if (is_map_empty(map))
		exit(perror_cube3d("Map is empty", 0));
	if (ft_array_length(map->map) < 3)
		exit(perror_cube3d("Invalid map structure or player count", 0));
	printf("path checker LOOOKING DONE\n");
	return (1);
}
