/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:03:46 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/16 18:26:21 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	rayhit_2(t_ray *ray)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->delta_x;
		ray->map_x += ray->step_x;
		if (ray->ray_x > 0)
			ray->side = EAST;
		else
			ray->side = WEST;
	}
	else
	{
		ray->sidedist_y += ray->delta_y;
		ray->map_y += ray->step_y;
		if (ray->ray_y > 0)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
	return (*ray);
}

static t_ray	rayhit(t_ray ray, char **map)
{
	while (ray.hit == 0)
	{
		ray = rayhit_2(&ray);
		if (map[ray.map_y][ray.map_x] == '1')
			ray.hit = 1;
		else if (map[ray.map_y][ray.map_x] == 'D')
			ray.hit = 2;
	}
	if (ray.side == EAST || ray.side == WEST)
		ray.distperpwall = ray.sidedist_x - ray.delta_x;
	else
		ray.distperpwall = ray.sidedist_y - ray.delta_y;
	return (ray);
}

static t_ray	set_ray(t_ray ray, int xsweep)
{
	ray.camera_x = 2 * xsweep / (double)ray.width - 1;
	ray.ray_x = ray.dir_x + ray.plane_x * ray.camera_x;
	ray.ray_y = ray.dir_y + ray.plane_y * ray.camera_x;
	ray.map_x = (int)ray.play_x;
	ray.map_y = (int)ray.play_y;
	ray.hit = 0;
	if (ray.ray_x == 0)
		ray.delta_x = 1e30;
	else
		ray.delta_x = fabs(1 / ray.ray_x);
	if (ray.ray_y == 0)
		ray.delta_y = 1e30;
	else
		ray.delta_y = fabs(1 / ray.ray_y);
	if (ray.ray_x < 0)
	{
		ray.step_x = -1;
		ray.sidedist_x = (ray.play_x - ray.map_x) * ray.delta_x;
	}
	else
	{
		ray.step_x = 1;
		ray.sidedist_x = (ray.map_x + 1.0 - ray.play_x) * ray.delta_x;
	}
	return (ray);
}

t_ray	single_ray(t_ray ray, char **map, int xsweep)
{
	ray = set_ray(ray, xsweep);
	if (ray.ray_y < 0)
	{
		ray.step_y = -1;
		ray.sidedist_y = (ray.play_y - ray.map_y) * ray.delta_y;
	}
	else
	{
		ray.step_y = 1;
		ray.sidedist_y = (ray.map_y + 1.0 - ray.play_y) * ray.delta_y;
	}
	ray = rayhit(ray, map);
	return (ray);
}

void	set_player(t_ray *ray, int i, int j)
{
	if (ray->map->map[i][j] == 'N')
	{
		ray->play_x = j + 0.5;
		ray->play_y = i + 0.5;
		ray->dir_x = 0;
		ray->dir_y = -1;
	}
	if (ray->map->map[i][j] == 'S')
	{
		ray->play_x = j + 0.5;
		ray->play_y = i + 0.5;
		ray->dir_x = 0;
		ray->dir_y = 1;
	}
	if (ray->map->map[i][j] == 'E')
	{
		ray->play_x = j + 0.5;
		ray->play_y = i + 0.5;
		ray->dir_x = 1;
		ray->dir_y = 0;
	}
}
