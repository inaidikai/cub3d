/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:15:20 by fkuruthl          #+#    #+#             */
/*   Updated: 2025/01/10 01:36:02 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	invisible_yes_no(char c)
{
	if (c == 32 || (c >= 9 && c <= 11))
		return (1);
	return (0);
}

int	val_chk(t_img *img, char *temp)
{
	if (!*temp)
		return (0);
	if (strncmp(temp, "NO", 2) == 0 && !img->no->img)
		return (NO);
	if (strncmp(temp, "SO", 2) == 0 && !img->so->img)
		return (SO);
	if (strncmp(temp, "WE", 2) == 0 && !img->we->img)
		return (WE);
	if (strncmp(temp, "EA", 2) == 0 && !img->ea->img)
		return (EA);
	if (strncmp(temp, "F", 1) == 0 && !img->f)
		return (F);
	if (strncmp(temp, "C", 1) == 0 && !img->c)
		return (C);
	return (0);
}

t_img	*ft_t_img(void)
{
	static t_img		img;
	static t_texture	no;
	static t_texture	so;
	static t_texture	we;
	static t_texture	ea;

	if (!img.init)
	{
		img.no = &no;
		img.so = &so;
		img.we = &we;
		img.ea = &ea;
		img.f = 0;
		img.c = 0;
		img.init = 1;
	}
	return (&img);
}

void	init_texture(t_vars *vars, t_texture *txt, char *element, int val)
{
	if (!vars->mlx)
		exit(perror_cube3d("mlx is not initialized", 0));
	txt->img = mlx_xpm_file_to_image(vars->mlx,
			element, &txt->width, &txt->height);
	if (!txt->img)
	{
		fprintf(stderr, "Error: Failed to load texture file '%s'\n", element);
		exit(perror_cube3d("Failed to load texture", 0));
	}
	txt->addr = mlx_get_data_addr(txt->img,
			&txt->bits_per_pixel, &txt->line_length, &txt->endian);
	txt->pix_y = 0;
	txt->pix_x = 0;
	txt->txt = val;
}

void	init_color(int *color, char *element)
{
	char	**temp;
	int		r;
	int		g;
	int		b;

	temp = ft_split(element, ',');
	if (*temp)
	{
		r = atoi(temp[0]);
		g = atoi(temp[1]);
		b = atoi(temp[2]);
		ft_free_pp((void **)temp);
		if (r <= 255 && r >= 0 && g <= 255 && g >= 0 && b <= 255 && b >= 0)
		{
			*color = 65536 * r + 256 * g + b;
			return ;
		}
	}
	exit (perror_cube3d ("colour invalid", 0));
}
