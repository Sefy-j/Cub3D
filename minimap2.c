/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:33:35 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/17 17:37:05 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_transparency(t_ray *ray)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	while (++i < MINIMAP)
	{
		j = -1;
		while (++j < MINIMAP)
		{
			color = my_pixel_get(&ray->img, i + 20, j + 20);
			color = color >> 1 & 8355711;
			my_mlx_pixel_put(&ray->img, i + 20, j + 20, color);
		}
	}
}

static void	paint_walls(t_ray *ray)
{
	int	pixel_x;
	int	pixel_y;
	int	contrast;

	pixel_y = -1;
	while (++pixel_y < MINIMAP)
	{
		pixel_x = -1;
		while (++pixel_x < MINIMAP)
		{
			contrast = check_minmap(ray, pixel_x, pixel_y);
			if (contrast == 1)
				my_mlx_pixel_put(&ray->img, pixel_x + 20,
					pixel_y + 20, 0x88AAAAAA);
			else if (contrast == 2)
				my_mlx_pixel_put(&ray->img, pixel_x + 20,
					pixel_y + 20, 0x88CD853F);
		}
	}
}

void	create_minimap(t_ray *ray)
{
	minimap_transparency(ray);
	paint_hero(ray);
	paint_walls(ray);
}
