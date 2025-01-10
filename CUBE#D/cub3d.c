/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:36:29 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 14:42:34 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	check_fill_2(t_vars *vars, int y, int x, int *i)
{
	if (is_pace(vars->map[y][x])
		|| vars->map[y][x] == '0')
		vars->map[y][x] = 'x';
	else if ((vars->map[y][x] == 'N' || vars->map[y][x] == 'S'
		|| vars->map[y][x] == 'E' || vars->map[y][x] == 'W')
		&& !vars->pos)
	{
		vars->pos = vars->map[y][x];
		vars->pos_y = y + 0.5;
		vars->pos_x = x + 0.5;
		vars->map[y][x] = 'x';
	}
	else if (vars->map[y][x] != '1' && vars->map[y][x] != 'x')
		exit(perror_cube3d("Map invalide caracter!!", 0));
	else
		return ;
	check_fill(vars, y + 1, x, i);
	check_fill(vars, y, x + 1, i);
	check_fill(vars, y - 1, x, i);
	check_fill(vars, y, x - 1, i);
	check_fill(vars, y + 1, x - 1, i);
	check_fill(vars, y - 1, x + 1, i);
	check_fill(vars, y - 1, x - 1, i);
	check_fill(vars, y + 1, x + 1, i);
}

void	check_fill(t_vars *vars, int y, int x, int *i)
{
	if (y >= 0 && x >= 0 && y < ft_len_pp((void **)vars->map))
	{
		if (x >= ft_str_len(vars->map[y]))
			*i = 0;
		else if ((y == 0 || x == 0 || y >= ft_len_pp((void **)vars->map) - 1)
			&& vars->map[y][x] != '1')
			*i = 0;
		if (y < ft_len_pp((void **)vars->map) && x < ft_str_len(vars->map[y]))
			check_fill_2(vars, y, x, i);
	}
}

int	is_valid_map_line(const char *line)
{
	while (*line && is_pace(*line))
	{
		line++;
	}
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) \
	|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) \
	|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		return (0);
	}
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == 'N' || *line == 'E'
			|| *line == 'W' || *line == 'S')
		{
			return (1);
		}
		if (!is_pace(*line))
		{
			return (0);
		}
		line++;
	}
	return (0);
}

static void	ft_set_pos(t_vars *vars)
{
	if (vars->pos == 'N')
		vars->player_angle = 269;
	else if (vars->pos == 'S')
		vars->player_angle = 89;
	else if (vars->pos == 'E')
		vars->player_angle = 1;
	else
		vars->player_angle = 179;
}

char	cube3d(char *filename)
{
	t_vars	*vars;

	vars = ft_t_vars();
	validate_file_format(filename);
	vars->mlx = mlx_init();
	ft_set_pos(vars);
	element_hunter(filename);
	vars->width = fill(vars, filename);
	store(vars, filename);
	if (!check_map())
		exit(perror_cube3d("Map invalide !!", 0));
	if (!path_struct(vars))
		exit(perror_cube3d("map invalid", 0));
	size_map();
	call_mlx(vars);
	game();
	mlx_put_image_to_window(ft_t_vars()->mlx, ft_t_vars()->win, ft_t_vars()->img, 0, 0);
	mlx_hook(vars->win, ON_DESTROY, 0, close_game, (void *)vars);
	mlx_hook(vars->win, ON_KEYDOWN,
		1L << 0, read_key, (void *)vars);
	mlx_mouse_hook(vars->win, &ft_mouse, (void *)vars);
	mlx_loop(vars->mlx);
	frey(vars);
	return (0);
}
