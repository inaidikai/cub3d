/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:58:57 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 10:08:32 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_table(t_rays *self)
{
	free(self->operations);
}

void	ft_reset_sprite(void)
{
	ft_t_img()->no->pix_x = 0;
	ft_t_img()->no->pix_y = 0;
	ft_t_img()->so->pix_x = 0;
	ft_t_img()->so->pix_y = 0;
	ft_t_img()->we->pix_x = 0;
	ft_t_img()->we->pix_y = 0;
	ft_t_img()->ea->pix_x = 0;
	ft_t_img()->ea->pix_y = 0;
}

void	ray_casting(t_vars *vars)
{
	t_rays	*self;

	self = get_raycaster();
	self->vars = vars;
	self->vars->rays = self;
	self->ray_angle = self->vars->player_angle - self->half_fov;
	ft_reset_sprite();
	while (self->ray_count < 640)
	{
		self->operations->reset_values(self);
		self->operations->wall_collision(self);
		self->operations->get_distance(self);
		self->operations->get_wall_height(self);
		self->operations->select_sprite(self, 0.001, 0.0);
		self->operations->print(self);
		self->operations->increment_angle(self);
		self->ray_count += 1;
	}
}

void	game(void)
{
	fill_floor_celing ();
	ray_casting(ft_t_vars());
	if (ft_t_vars()->map_on > 0)
		put_mini_map();
	mlx_put_image_to_window(ft_t_vars()->mlx, \
		ft_t_vars()->win, ft_t_vars()->img, 0, 0);
}
