/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:08:26 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 10:09:37 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

float	degreetoradian(double degree)
{
	if (degree > 360)
		degree = degree - 360;
	else if (degree < 0)
		degree = degree + 360;
	return (degree * PI / 180);
}

t_rays	*get_raycaster(void)
{
	static t_rays	self;

	self.ray_count = 0;
	self.ray_cos = 0;
	self.ray_sin = 0;
	self.wall = 0;
	self.distance = 0;
	self.wall_h = 0;
	self.difx = 0;
	self.dify = 0;
	self.tmp = 0;
	if (!self.init)
	{
		self.operations = ft_init_vtable();
		self.half_h = (double) 640 / 2;
		self.increment_angle = (double) 60 / (double) 640;
		self.half_fov = (double) 60 / 2;
		self.init = 1;
		self.texture = ft_t_img()->no;
	}
	return (&self);
}

void	ft_look_left(t_vars *vars)
{
	if (vars->player_angle - vars->rotation < 0)
		vars->player_angle = 360 + vars->player_angle - vars->rotation;
	else
		vars->player_angle -= vars->rotation;
}

void	ft_look_right(t_vars *vars)
{
	vars->player_angle += vars->rotation;
	vars->player_angle %= 360;
}
