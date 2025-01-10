/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:09:25 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 09:27:27 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <ctype.h>

void	size_map(void)
{
	int	i;

	i = 0;
	ft_t_vars()->map_y = ft_len_pp((void **)ft_t_vars()->map) - 1;
	while (i < ft_t_vars()->map_y)
	{
		if (ft_str_len(ft_t_vars()->map[i]) > ft_t_vars()->map_x)
			ft_t_vars()->map_x = ft_str_len(ft_t_vars()->map[i]);
		i++;
	}
}

int	ft_stronlyspaces(const char *line)
{
	while (*line)
	{
		if (!is_pace(*line))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

int	case_chk(char *line, int *height, size_t *width)
{
	int		validity;
	size_t	temp_width;
	int		map_started;

	map_started = 0;
	(void)map_started;
	validity = is_valid_map_line(line);
	if (validity == 1)
	{
		map_started = 1;
		temp_width = ft_strlen(line);
		if (temp_width > *width)
		{
			*width = temp_width;
		}
		(*height)++;
	}
	return (validity);
}

void	free_mover(char **line, int fd)
{
	free(*line);
	*line = get_next_line(fd);
}

int	fill(t_vars *map, char *filename)
{
	int		fd;
	char	*line;
	size_t	width;
	int		height;

	width = 0;
	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(perror_cube3d("Error opening map file", 0));
	line = get_next_line(fd);
	while (line)
	{
		if (ft_stronlyspaces(line))
		{
			free_mover(&line, fd);
			continue ;
		}
		case_chk(line, &height, &width);
		free_mover(&line, fd);
	}
	close(fd);
	map->height = height;
	return (width);
}
