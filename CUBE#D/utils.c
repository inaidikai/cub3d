/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:40:30 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 09:26:14 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	close_game(t_vars *vars)
{
	mlx_destroy_image(ft_t_vars()->mlx, ft_t_vars()->img);
	mlx_destroy_image(ft_t_vars()->mlx, ft_t_img()->no->img);
	mlx_destroy_image(ft_t_vars()->mlx, ft_t_img()->so->img);
	mlx_destroy_image(ft_t_vars()->mlx, ft_t_img()->we->img);
	mlx_destroy_image(ft_t_vars()->mlx, ft_t_img()->ea->img);
	mlx_destroy_window(ft_t_vars()->mlx, ft_t_vars()->win);
	free_cube3d(vars);
	exit(EXIT_SUCCESS);
}

int	get_keycode(int keycode)
{
	if (keycode == ESC)
		return (4);
	else if (keycode == UP)
		return (3);
	else if (keycode == LOOK_LEFT)
		return (5);
	else if (keycode == LOOK_RIGHT)
		return (6);
	else if (keycode <= 2 && keycode >= 0)
		return (keycode);
	else
		return (-1);
}

int	read_key(int keycode, t_vars *vars)
{
	void	(*keys[7])(t_vars *);
	int		real_key;

	keys[0] = &ft_left;
	keys[1] = &ft_down;
	keys[2] = &ft_right;
	keys[3] = &ft_up;
	keys[4] = &ft_esc;
	keys[5] = &ft_look_left;
	keys[6] = &ft_look_right;
	if (keycode == MAP)
		vars->map_on *= -1;
	real_key = get_keycode(keycode);
	if (real_key >= 0 && real_key <= 6)
		keys[real_key](vars);
	vars->player_cos = (cos(degreetoradian(vars->player_angle)));
	vars->player_sin = (sin(degreetoradian(vars->player_angle)));
	game();
	return (0);
}

int	ft_mouse(int button, int x, int y, t_vars *vars)
{
	int	i;

	i = 3;
	if (button == ON_MOUSEUP)
		while (i--)
			ft_look_left(vars);
	else if (button == ON_MOUSDOWN)
		while (i--)
			ft_look_right(vars);
	read_key(-1, vars);
	(void)x;
	(void)y;
	return (0);
}

void	call_mlx(t_vars *vars)
{
	vars->win = mlx_new_window(vars->mlx, 640, 640,
			"cub3D");
	vars->img = mlx_new_image(vars->mlx, 640, 640);
	vars->addr = mlx_get_data_addr(vars->img,
			&vars->bits_per_pixel, &vars->line_length,
			&vars->endian);
}
