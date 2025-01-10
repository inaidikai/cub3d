/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:12:54 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 02:08:50 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_vars	*ft_t_vars(void)
{
	static t_vars	vars;

	if (!vars.init)
	{
		vars.map_x = 0;
		vars.map_y = 0;
		vars.init = 1;
		vars.pos = 0;
		vars.player_angle = 0;
		vars.speed = 3.0;
		vars.rotation = 3;
		vars.radius = 0.3;
		vars.map_on = 1;
	}
	return (&vars);
}

void	free_cube3d(t_vars *vars)
{
	if (vars->map)
		ft_free_pp((void **)vars->map);
}

int	perror_cube3d(char *str, int flag)
{
	dprintf(2, "Error ");
	if (flag)
		perror(str);
	else
		dprintf(2, "%s\n", str);
	return (0);
}

void	ft_free_pp(void **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		if (argv[i])
		{
			free(argv[i]);
			argv[i] = NULL;
		}
		i++;
	}
	free(argv);
}

int	ft_str_len(char *s)
{
	unsigned int	count;

	count = 0;
	while (s[count])
	{
		count++;
	}
	return (count);
}

long long	ft_len_pp(void **argv)
{
	long long	i;

	i = 0;
	while (argv && argv[i])
	{
		i++;
	}
	return (i);
}

void	ft_esc(t_vars *vars)
{
	close_game(vars);
}
