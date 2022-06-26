/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:25:07 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/17 18:40:13 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_vector(t_data *img, double print[2],
		double xo, double yo)
{
	double	i;
	double	xprint;
	double	yprint;

	i = 0;
	while (i < 20)
	{
		xprint = print[0] * i + xo;
		yprint = print[1] * i + yo;
		my_mlx_pixel_put(img, (int)xprint + 20, (int)yprint + 20, 0x88FFFF00);
		i++;
	}
}

void	print_vision(t_ray *ray, double xo, double yo)
{
	double	ang;
	double	dirx;
	double	diry;
	double	print[2];

	dirx = ray->dir_x;
	diry = ray->dir_y;
	ang = -PI / 6;
	while (ang < PI / 6)
	{
		print[0] = dirx;
		print[1] = diry;
		rotate_vector(&print[0], &print[1], ang);
		print_vector(&ray->img, print, xo, yo);
		ang += 0.05;
	}
}

void	paint_hero(t_ray *ray)
{
	int	i;
	int	j;

	i = MINIMAP / 2 - 4;
	while (++i < MINIMAP / 2 + 4)
	{
		j = MINIMAP / 2 - 4;
		while (++j < MINIMAP / 2 + 4)
		{
			my_mlx_pixel_put(&ray->img, i + 20, j + 20, 0x00FF0000);
		}
	}
	print_vision(ray, (double)(MINIMAP / 2), (double)(MINIMAP / 2));
}

int	check_minmap(t_ray *ray, int x, int y)
{
	double	new_x;
	double	new_y;
	int		i;
	int		j;

	new_x = (x - 127.5) / SQMIN;
	new_y = (y - 127.5) / SQMIN;
	i = (int)(new_y + ray->play_y);
	j = (int)(new_x + ray->play_x);
	if (i < 0 || j < 0)
		return (0);
	else if (count_strs(ray->map->map) <= i
		|| (int)ft_strlen(ray->map->map[i]) <= j)
		return (0);
	else if (ray->map->map[i][j] != '1' && ray->map->map[i][j] != 'D'
		&& ray->map->map[i][j] != 'O')
		return (0);
	if (ray->map->map[i][j] == 'D' || ray->map->map[i][j] == 'O')
		return (2);
	return (1);
}
