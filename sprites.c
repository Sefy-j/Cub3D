/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:58:58 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/17 18:19:38 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stripe_painting(t_paint	p, t_ray *ray, t_sprite *sprites, t_data tex)
{
	int	no_paint;

	no_paint = my_pixel_get(&tex, 1, 1);
	p.stripe = p.start_drawx;
	while (p.stripe < p.end_drawx)
	{
		p.tex_x = ((int)(256 * (p.stripe - (-p.sp_width / 2 + p.sp_posx))
					* sprites->w / p.sp_width)) / 256;
		if (sprites->sp_z > 0 && sprites->sp_z < ray->distance[p.stripe])
		{
			p.y = p.start_drawy;
			while (p.y < p.end_drawy)
			{
				p.tex_y = (p.y * 256 - HEIGHT * 128 + p.sp_height * 128)
					* sprites->h / p.sp_height / 256;
				p.color = my_pixel_get(&tex, p.tex_x, p.tex_y);
				if (p.color != no_paint)
					my_mlx_pixel_put(&ray->img, p.stripe, p.y, p.color);
				p.y++;
			}
		}
		p.stripe++;
	}
}

void	paint_sprites(t_sprite	*sprites, t_ray *ray)
{
	t_paint	p;

	p.sp_posx = (int)(WIDTH / 2 * (1 + sprites->sp_x / sprites->sp_z));
	p.sp_height = abs((int)(HEIGHT / sprites->sp_z));
	p.start_drawy = -p.sp_height / 2 + HEIGHT / 2;
	if (p.start_drawy < 0)
		p.start_drawy = 0;
	p.end_drawy = p.sp_height / 2 + HEIGHT / 2;
	if (p.end_drawy >= HEIGHT)
		p.end_drawy = HEIGHT - 1;
	p.sp_width = abs((int)(HEIGHT / sprites->sp_z));
	p.start_drawx = -p.sp_width / 2 + p.sp_posx;
	if (p.start_drawx < 0)
		p.start_drawx = 0;
	p.end_drawx = p.sp_width / 2 + p.sp_posx;
	if (p.end_drawx >= WIDTH)
		p.end_drawx = WIDTH - 1;
	if (c_time(0) % 1000 > 500)
		stripe_painting(p, ray, sprites, sprites->tex);
	else
		stripe_painting(p, ray, sprites, sprites->tex2);
}

int	is_painted(t_sprite *list)
{
	while (list)
	{
		if (list->distance > 0)
			return (1);
		list = list->next;
	}
	return (0);
}

t_sprite	*sort_list(t_sprite *list, t_ray *ray)
{
	t_sprite	*temp;
	t_sprite	*paint;

	if (!list)
		return (NULL);
	if (!list->next)
	{
		paint_sprites(list, ray);
		return (list);
	}
	while (is_painted(list) == 1)
	{
		temp = list->next;
		paint = list;
		while (temp)
		{
			if (temp->distance > paint->distance)
				paint = temp;
			temp = temp->next;
		}
		paint_sprites(paint, ray);
		paint->distance = -1;
	}
	return (list);
}

void	calc_sprites(t_ray *ray)
{
	t_sprite	*temp;
	double		det;

	det = ray->plane_x * ray->dir_y - ray->dir_x * ray->plane_y;
	temp = ray->sprites;
	while (temp)
	{
		temp->rel_x = temp->x - ray->play_x;
		temp->rel_y = temp->y - ray->play_y;
		temp->distance = temp->rel_x * temp->rel_x + temp->rel_y * temp->rel_y;
		temp->sp_x = (temp->rel_x * ray->dir_y + temp->rel_y * (-ray->dir_x))
			/ det;
		temp->sp_z = ((-ray->plane_y) * temp->rel_x + ray->plane_x
				* temp->rel_y) / det;
		temp = temp->next;
	}
	ray->sprites = sort_list(ray->sprites, ray);
}
