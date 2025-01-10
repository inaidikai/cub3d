/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:58:57 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 02:05:53 by inkahar          ###   ########.fr       */
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

void	ft_hit_wall(t_rays *self)
{
	while (self->wall != '1')
	{
		self->ray_x += self->ray_cos;
		self->ray_y += self->ray_sin;
		int	map_x = (int)floor(self->ray_x);
		int	map_y = (int)floor(self->ray_y);
		self->wall = self->vars->map[map_y][map_x];
	}
}

void	ft_calculate_distance(t_rays *self)
{
	self->distance = sqrt(pow(self->vars->pos_x - self->ray_x, 2) + \
			pow(self->vars->pos_y - self->ray_y, 2));
	self->distance = self->distance * \
			cosf(degreetoradian(self->ray_angle - \
			self->vars->player_angle));
}

void	ft_calculate_wall_height(t_rays *self)
{
	self->wall_h = (floor(self->half_h / self->distance));
}

void	ft_increment_angle(t_rays *self)
{
	self->ray_angle += self->increment_angle;
}

void	free_table(t_rays *self)
{
	free(self->operations);
}

static int	ft_get_pixel(t_rays *self)
{
	char	*dst;

	if (self->pix > 640 && self->texture->pix_y == 0)
		self->texture->pix_y = ((float)self->texture->height / (float)self->pix)
			* (self->pix - 640) / 2;
	else
		self->texture->pix_y += (float)self->texture->height / (float)self->pix;
	dst = self->texture->addr
		+ ((int)self->texture->pix_y * self->texture->line_length)
		+ ((int)self->texture->pix_x * (self->texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
void	ft_print_walls(t_rays *self)
{
	self->pix = self->wall_h;
	if (self->wall_h > 640)
		self->wall_h = 640;
	self->tmp = self->wall_h;
	self->wall_h -= 1;
	while (self->wall_h--)
	{
		put_pixel(self->vars, self->ray_count,
			((640 / 2) - (self->tmp / 2)) + self->wall_h, \
			ft_get_pixel(self));
	}
}

static void	ft_set_sprite(t_rays *self)
{
	self->difx = (self->ray_x - (int)(self->ray_x));
	self->dify = (self->ray_y - (int)(self->ray_y));
	if (self->texture->txt == EA || self->texture->txt == WE)
		self->texture->pix_x = (float)self->texture->width * self->dify;
	else
		self->texture->pix_x = (float)self->texture->width * self->difx;
	self->texture->pix_y = 0 ;
}
void	ft_get_sprite(t_rays *self, float i, float i2)
{
	self->texture = NULL;
	while (!self->texture)
	{
		if (self->ray_y < self->vars->pos_y && self->vars->map[(int) \
			(self->ray_y + i)][(int)(self->ray_x + i2)] != '1')
			self->texture = ft_t_img()->no;
		else if (self->ray_y >= self->vars->pos_y && self->vars->map[\
			(int)(self->ray_y - i)][(int)(self->ray_x - i2)] != '1')
			self->texture = ft_t_img()->so;
		else if (self->ray_x < self->vars->pos_x && self->vars->map[\
			(int)(self->ray_y + i2)][(int)(self->ray_x + i)] != '1')
			self->texture = ft_t_img()->we;
		else if (self->ray_x >= self->vars->pos_x && self->vars->map[\
			(int)(self->ray_y - i2)][(int)(self->ray_x - i)] != '1')
			self->texture = ft_t_img()->ea;
		i += 0.001;
		if (self->ray_y + i < self->vars->map_y \
			&& self->ray_x < self->vars->map_x)
			i2 += 0.001;
	}
	ft_set_sprite(self);
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

static	void	fill_floor_celing(void)
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
static void	put_mini_map(void)
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

void game()
{
	fill_floor_celing ();
	ray_casting(ft_t_vars());
	if (ft_t_vars()->map_on > 0)
		put_mini_map();
	mlx_put_image_to_window(ft_t_vars()->mlx, \
		ft_t_vars()->win, ft_t_vars()->img, 0, 0);
}