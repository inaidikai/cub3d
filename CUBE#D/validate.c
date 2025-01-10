/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:36:29 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 00:16:27 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	content_checker(char *trimmed_line, int *config_lines)
{
	int	map_started;

	map_started = 0;
	while (*trimmed_line && is_pace(*trimmed_line))
		trimmed_line++;
	if (*trimmed_line == '\0')
		return (1);
	if (is_valid_config_line(trimmed_line))
	{
		if (map_started)
		{
			return (1);
		}
		(*config_lines)++;
	}
	else if (is_valid_map_line(trimmed_line))
		map_started = 1;
	else if (map_started)
		return (1);
	else
		return (0);
	return (1);
}

int	is_valid_config_line(const char *line)
{
	while (*line && is_pace(*line))
	{
		line++;
	}
	return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || \
	!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) || \
	!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1));
}

void	closer(int fd)
{
	close(fd);
	exit(perror_cube3d("Missing or invalid configuration lines", 0));
}

void	validate_file_format(char *filename)
{
	char	*line;
	int		fd;
	int		config_lines;
	char	*trimmed_line;

	config_lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(perror_cube3d("Error opening file for format validation", 0));
	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = line;
		if (!content_checker(trimmed_line, &config_lines))
		{
			free(line);
			closer(fd);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (config_lines != 6)
		closer(fd);
	close(fd);
}
