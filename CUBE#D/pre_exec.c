/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:18:30 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 10:08:42 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_pixel(t_vars *data, int x, int y, int color)
{
	char	*dst;

	if (color)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	fill_floor_celing(void)
{
	int	x;
	int	y;

	y = -1;
	while (y++ < 640 / 2)
	{
		x = -1;
		while (x++ < 640)
		{
			put_pixel(ft_t_vars(), x, y, ft_t_img()->f);
		}
	}
	y--;
	while (y++ < 640 - 2)
	{
		x = -1;
		while (x++ < 640)
		{
			put_pixel(ft_t_vars(), x, y, ft_t_img()->c);
		}
	}
}

static void	put_multipix(int x, int y, int color, int size)
{
	int	i;
	int	i2;

	i = -1;
	while (i++ < size)
	{
		i2 = -1;
		while (i2++ < size)
			put_pixel(ft_t_vars(), x * 8 + i, y * 8 + i2, color);
	}
}

void	put_mini_map(void)
{
	int	x;
	int	y;
	int	size;

	size = 6;
	y = -1;
	while (y++ < ft_t_vars()->map_y)
	{
		x = -1;
		while (x++ < ft_t_vars()->map_x)
		{
			if (x < ft_str_len(ft_t_vars()->map[y])
				&& y < ft_len_pp((void **)ft_t_vars()->map)
				&& ft_t_vars()->map[y][x] == '1')
				put_multipix(x, y, 255, size);
			else
				put_multipix(x, y, 000000, size);
		}
	}
	put_multipix(ft_t_vars()->pos_x, ft_t_vars()->pos_y, 16711680, size);
}
