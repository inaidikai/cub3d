/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:47:40 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 01:57:31 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_left(t_vars *vars)
{
	double	new_x;
	double	new_y;

	vars->player_cos = (cos(degreetoradian(vars->player_angle - 90)));
	vars->player_sin = (sin(degreetoradian(vars->player_angle - 90)));
	new_x = vars->pos_x + (vars->player_cos / vars->speed);
	new_y = vars->pos_y + (vars->player_sin / vars->speed);
	if ((int)floor(new_y) < vars->map_y - 1 && (int)floor(new_x) < \
		(ft_str_len(ft_t_vars()->map[(int)floor(new_y)])) - 1)
	{
		if ((int) floor(new_x) > 0 && (int) floor(new_y) > 0)
		{
			if (vars->map[(int)floor(new_y + (vars->radius * \
			((vars->player_sin > 0) - (vars->player_sin < 0))))] \
			[(int)floor(new_x + (vars->radius * \
			((vars->player_cos > 0) - (vars->player_cos < 0))))] != '1')
			{
				vars->pos_x = new_x;
				vars->pos_y = new_y;
			}
		}
	}
}

void	ft_down(t_vars *vars)
{
	double	new_x;
	double	new_y;

	new_x = vars->pos_x - (vars->player_cos / vars->speed);
	new_y = vars->pos_y - (vars->player_sin / vars->speed);
	if ((int)floor(new_y) < vars->map_y && (int)(new_x) < \
		(ft_str_len(ft_t_vars()->map[(int)(new_y)])))
	{
		if ((int)floor(new_x) > 0 && (int)floor(new_y) > 0)
		{
			if (vars->map[(int)floor(new_y - (vars->radius * \
			((vars->player_sin > 0) - (vars->player_sin < 0))))] \
			[(int)floor(new_x - (vars->radius * \
			((vars->player_cos > 0) - (vars->player_cos < 0))))] != '1')
			{
				vars->pos_x = new_x;
				vars->pos_y = new_y;
			}
		}
	}
}

void	ft_up(t_vars *vars)
{
	double	new_x;
	double	new_y;

	new_x = vars->pos_x + (vars->player_cos / vars->speed);
	new_y = vars->pos_y + (vars->player_sin / vars->speed);
	if ((int)floor(new_y) < vars->map_y && (int)(new_x) < \
		(ft_str_len(ft_t_vars()->map[(int)(new_y)])))
	{
		if ((int)floor(new_x) > 0 && (int)floor(new_y) > 0)
		{
			if (vars->map[(int)floor(new_y + (vars->radius * \
			((vars->player_sin > 0) - (vars->player_sin < 0))))] \
			[(int)floor(new_x + (vars->radius * \
			((vars->player_cos > 0) - (vars->player_cos < 0))))] != '1')
			{
				vars->pos_x = new_x;
				vars->pos_y = new_y;
			}
		}
	}
}

void	ft_right(t_vars *vars)
{
	double	new_x;
	double	new_y;

	vars->player_cos = (cos(degreetoradian(vars->player_angle + 90)));
	vars->player_sin = (sin(degreetoradian(vars->player_angle + 90)));
	new_x = vars->pos_x + (vars->player_cos / vars->speed);
	new_y = vars->pos_y + (vars->player_sin / vars->speed);
	if ((int)floor(new_y) < vars->map_y - 1 && (int)floor(new_x) < \
		(ft_str_len(ft_t_vars()->map[(int)floor(new_y)])) - 1)
	{
		if ((int) floor(new_x) > 0 && (int) floor(new_y) > 0)
		{
			if (vars->map[(int)floor(new_y + (vars->radius * \
			((vars->player_sin > 0) - (vars->player_sin < 0))))] \
			[(int)floor(new_x + (vars->radius * \
			((vars->player_cos > 0) - (vars->player_cos < 0))))] != '1')
			{
				vars->pos_x = new_x;
				vars->pos_y = new_y;
			}
		}
	}
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