/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:32:18 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/06/16 17:04:51 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*start_dir(t_ray *ray)
{
	int	i;
	int	j;

	i = 0;
	while (ray->map->map[i])
	{
		j = 0;
		while (ray->map->map[i][j])
		{
			set_player(ray, i, j);
			if (ray->map->map[i][j] == 'W')
			{
				ray->play_x = j + 0.5;
				ray->play_y = i + 0.5;
				ray->dir_x = -1;
				ray->dir_y = 0;
			}
			j++;
		}
		i++;
	}
	return (ray);
}

t_ray	*init_ray(t_map *map)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->map = map;
	ray->height = HEIGHT;
	ray->width = WIDTH;
	ray = start_dir(ray);
	ray->plane_x = -ray->dir_y;
	ray->plane_y = ray->dir_x * 0.66;
	ray->vel = 0;
	ray->velstraf = 0;
	ray->velgiro = 0;
	ray->mouse = 1;
	ray->mlx = mlx_init();
	ray->distance = malloc(sizeof(double) * WIDTH);
	ray->mlx_win = mlx_new_window(ray->mlx,
			ray->width, ray->height, "weaboo segfault");
	ray->img.img = mlx_new_image(ray->mlx, ray->width, ray->height);
	ray->img.addr = mlx_get_data_addr(ray->img.img, &ray->img.bits_per_pixel,
			&ray->img.line_length, &ray->img.endian);
	return (ray);
}

void	collisions(t_ray *ray)
{
	if (ft_strchr(COLLIS, ray->map->map[(int)ray->play_y]
			[(int)(ray->play_x + ray->dir_x * ray->vel * 2)]) == NULL)
			ray->play_x += ray->dir_x * ray->vel;
	if (ft_strchr(COLLIS,
			ray->map->map[(int)(ray->play_y + ray->dir_y * ray->vel * 2)]
		[(int)ray->play_x]) == NULL)
			ray->play_y += ray->dir_y * ray->vel;
	if (ft_strchr(COLLIS,
			ray->map->map[(int)ray->play_y]
			[(int)(ray->play_x + (-ray->dir_y * ray->velstraf * 2))]) == NULL)
			ray->play_x += -ray->dir_y * ray->velstraf;
	if (ft_strchr(COLLIS,
			ray->map->map[(int)(ray->play_y + ray->dir_x * ray->velstraf * 2)]
		[(int)ray->play_x]) == NULL)
			ray->play_y += ray->dir_x * ray->velstraf;
}

int	calculate_raycasting(t_ray *ray)
{
	int	xsweep;

	ray->plane_x = -ray->dir_y;
	ray->plane_y = ray->dir_x * 0.66;
	collisions(ray);
	get_mouse_pos(ray);
	rotate_vector(&ray->dir_x, &ray->dir_y, ray->velgiro);
	mlx_clear_window(ray->mlx, ray->mlx_win);
	xsweep = 0;
	while (xsweep < ray->width)
	{
		*ray = single_ray(*ray, ray->map->map, xsweep);
		*ray = print_wall(*ray, xsweep);
		ray->distance[xsweep] = ray->distperpwall;
		xsweep++;
	}
	calc_sprites(ray);
	create_minimap(ray);
	mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img.img, 0, 0);
	return (0);
}

void	cub3d(t_map *map)
{
	t_ray	*ray;

	ray = init_ray(map);
	ray->sprites = init_sprites(ray->map->map);
	ray = load_textures(ray);
	load_sprite_textures(ray);
	mlx_mouse_hide();
	mlx_mouse_move(ray->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(ray->mlx_win, ON_KEYDOWN, 1L << 0, key_hooks, ray);
	mlx_hook(ray->mlx_win, ON_KEYUP, 1L << 1, key_release, ray);
	mlx_hook(ray->mlx_win, ON_DESTROY, 0L, ft_destroywindow, ray);
	mlx_hook(ray->mlx_win, ON_EXPOSE, 1L << 15, stop_automove, ray);
	mlx_loop_hook(ray->mlx, calculate_raycasting, ray);
	mlx_loop(ray->mlx);
}
