/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:18:30 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 10:15:31 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_calculate_wall_height(t_rays *self)
{
	self->wall_h = (floor(self->half_h / self->distance));
}

void	ft_calculate_distance(t_rays *self)
{
	self->distance = sqrt(pow(self->vars->pos_x - self->ray_x, 2) + \
			pow(self->vars->pos_y - self->ray_y, 2));
	self->distance = self->distance * \
			cosf(degreetoradian(self->ray_angle - \
			self->vars->player_angle));
}

void	ft_hit_wall(t_rays *self)
{
	int		map_y;
	int		map_x;

	map_x = 0;
	map_y = 0;
	while (self->wall != '1')
	{
		self->ray_x += self->ray_cos;
		self->ray_y += self->ray_sin;
		map_x = (int)floor(self->ray_x);
		map_y = (int)floor(self->ray_y);
		self->wall = self->vars->map[map_y][map_x];
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

t_vtable_rays	*ft_init_vtable(void)
{
	static t_vtable_rays	vtable;

	vtable.reset_values = &ft_reset_values;
	vtable.wall_collision = &ft_hit_wall;
	vtable.get_distance = &ft_calculate_distance;
	vtable.get_wall_height = &ft_calculate_wall_height;
	vtable.select_sprite = &ft_get_sprite;
	vtable.print = &ft_print_walls;
	vtable.increment_angle = &ft_increment_angle;
	vtable.free = &free_table;
	return (&vtable);
}
