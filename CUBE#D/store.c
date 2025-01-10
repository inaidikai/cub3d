/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:36:29 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 09:42:04 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	store_helper(t_vars *map, char *line, int *map_line_count)
{
	int	validity;

	validity = is_valid_map_line(line);
	if (validity == 1)
	{
		map->map[*map_line_count] = ft_strdup(line);
		if (!*map->map[*map_line_count])
		{
			free(line);
			ft_free_pp((void **)map->map);
			exit(perror_cube3d("Failed to allocate memory for map line", 0));
		}
		(*map_line_count)++;
	}
}

void	fd_checkerr(t_vars *map, int fd)
{
	if (fd < 0)
	{
		free(map->map);
		exit(perror_cube3d("Error opening map file", 0));
	}
}

static char	*freehelp(char *line, int fd)
{
	if (line)
		free(line);
	line = get_next_line(fd);
	return (line);
}

void	store(t_vars *map, char *filename)
{
	char	*line;
	int		fd;
	int		map_line_count;

	map_line_count = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit(perror_cube3d("Memory allocation failed for map storage", 0));
	fd = open(filename, O_RDONLY);
	fd_checkerr(map, fd);
	line = get_next_line(fd);
	while (line && map_line_count < map->height)
	{
		if (ft_stronlyspaces(line))
		{
			line = freehelp(line, fd);
			continue ;
		}
		store_helper(map, line, &map_line_count);
		line = freehelp(line, fd);
	}
	if (line)
		free(line);
	map->map[map_line_count] = NULL;
	close(fd);
}
