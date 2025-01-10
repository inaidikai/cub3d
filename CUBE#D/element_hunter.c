/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_hunter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:36:29 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 09:28:50 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <ctype.h>

int	init_element(char *element, int val)
{
	if (element && val == NO)
		init_texture(ft_t_vars(), ft_t_img()->no, element, val);
	else if (element && val == SO)
		init_texture(ft_t_vars(), ft_t_img()->so, element, val);
	else if (element && val == WE)
		init_texture(ft_t_vars(), ft_t_img()->we, element, val);
	else if (element && val == EA)
		init_texture(ft_t_vars(), ft_t_img()->ea, element, val);
	else if (element && val == F)
		init_color(&ft_t_img()->f, element);
	else if (element && val == C)
		init_color(&ft_t_img()->c, element);
	else
		return (perror_cube3d("whattttt", 0));
	return (1);
}

int	find_element(char *element, int fd)
{
	int	val;
	int	i;

	val = 0;
	i = 0;
	while (*element && invisible_yes_no(*element))
		element++;
	val = val_chk(ft_t_img(), element);
	if (val > 0)
	{
		element++;
		if (val < 5)
			element++;
		while (invisible_yes_no(*element))
			element++;
		i = 0;
		while (element[i] && !invisible_yes_no(element[i]))
			i++;
		element[i] = '\0';
		if (init_element(element, val))
			return (1);
		close(fd);
		exit(perror_cube3d("Element initialization failed", 0));
	}
	return (0);
}

void	element_hunter(char *filename)
{
	char	*temp;
	int		fd;
	int		config_count;

	config_count = 6;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror_cube3d("Failed to open map file", 1);
	}
	temp = get_next_line(fd);
	while (temp && config_count > 0)
	{
		if (find_element(temp, fd))
			config_count--;
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	if (config_count != 0)
	{
		close(fd);
		exit(perror_cube3d("Missing configuration elements", 0));
	}
	close(fd);
}

void	frey(t_vars *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		i++;
	}
	while (j < i)
	{
		free(map->map[j]);
		j++;
	}
	free(map->map);
}

int	check_map(void)
{
	int	y;
	int	x;
	int	i;
	int	ok;

	y = -1;
	ok = 0;
	while (++y < ft_len_pp((void **)ft_t_vars()->map))
	{
		x = -1;
		while (++x < ft_str_len(ft_t_vars()->map[y]))
		{
			i = 1;
			if (ok != 1)
				ft_t_vars()->pos = 0;
			if (ft_t_vars()->map[y][x] != '1' && ft_t_vars()->map[y][x] != 'x'
				&& ft_t_vars()->map[y][x] != 'P')
			{
				check_fill(ft_t_vars(), y, x, &i);
				if (i == 1 && ft_t_vars()->pos != 0)
					ok = 1;
			}
		}
	}
	return (ok);
}
