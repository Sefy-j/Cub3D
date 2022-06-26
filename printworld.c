/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printworld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:31:53 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/06/17 18:40:28 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_tex(t_ray ray, t_wall p, int x)
{
	if (ray.hit == 2)
		my_mlx_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.texs.door, p.xwall, p.ywall));
	else if (ray.side == NORTH)
		my_mlx_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.texs.wn, p.xwall, p.ywall));
	else if (ray.side == EAST)
		my_mlx_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.texs.we, p.xwall, p.ywall));
	else if (ray.side == SOUTH)
		my_mlx_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.texs.ws, p.xwall, p.ywall));
	else if (ray.side == WEST)
		my_mlx_pixel_put(&ray.img, x, p.y,
			my_pixel_get(&ray.texs.ww, p.xwall, p.ywall));
}

void	paint_wall(t_ray ray, int x, t_wall p)
{
	while (p.y < ray.height)
	{
		if (p.y < p.startdraw)
			my_mlx_pixel_put(&ray.img, x, p.y, create_trgb(0,
					ray.map->c_color[0], ray.map->c_color[1],
					ray.map->c_color[2]));
		else if (p.y >= p.startdraw && p.y <= p.enddraw)
		{
			p.ywall = (int)p.exacthit & (ray.texs.height - 1);
			p.exacthit += p.stepy;
			choose_tex(ray, p, x);
		}
		else
			my_mlx_pixel_put(&ray.img, x, p.y, create_trgb(0,
					ray.map->f_color[0], ray.map->f_color[1],
					ray.map->f_color[2]));
		p.y++;
	}
}

t_ray	print_wall(t_ray ray, int x)
{
	t_wall	p;

	p.wallheight = (int)(ray.height / ray.distperpwall);
	p.startdraw = -p.wallheight / 2 + ray.height / 2;
	if (p.startdraw < 0)
		p.startdraw = 0;
	p.enddraw = p.wallheight / 2 + ray.height / 2;
	if (p.enddraw >= ray.height)
		p.enddraw = ray.height - 1;
	p.y = 0;
	if (ray.side == EAST || ray.side == WEST)
		p.exacthit = ray.play_y + ray.distperpwall * ray.ray_y;
	else
		p.exacthit = ray.play_x + ray.distperpwall * ray.ray_x;
	p.exacthit -= floor((p.exacthit));
	p.xwall = (int)(p.exacthit * (double)ray.texs.width);
	if (ray.side == EAST && ray.ray_x > 0)
		p.xwall = ray.texs.width - p.xwall - 1;
	if (ray.side == SOUTH && ray.ray_y < 0)
		p.xwall = ray.texs.width - p.xwall - 1;
	p.stepy = (double)ray.texs.height / (double)p.wallheight;
	p.exacthit = (p.startdraw - ray.height / 2 + p.wallheight / 2) * p.stepy;
	paint_wall(ray, x, p);
	return (ray);
}
