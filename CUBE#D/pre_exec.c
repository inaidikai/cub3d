/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:18:30 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 02:05:39 by inkahar          ###   ########.fr       */
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



void	ft_reset_values(t_rays *self)
{
	self->distance = 0;
	self->wall_h = 0;
	self->ray_x = self->vars->pos_x;
	self->ray_y = self->vars->pos_y;
	self->ray_cos = cosf(degreetoradian(self->ray_angle)) / 4000;
	self->ray_sin = sinf(degreetoradian(self->ray_angle)) / 4000;
	self->wall = 0;
}
